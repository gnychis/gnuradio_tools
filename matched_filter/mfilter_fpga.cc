#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <fstream>

typedef std::complex<float> gr_complex;

std::vector<gr_complex> read_coeffs(std::string filename)
{
  std::string line;
  std::ifstream coeffs(filename.c_str());
  std::vector<gr_complex> complex_coeffs;

  if(!coeffs.is_open()) {
    std::cout << "coeffs missing\n";
    exit(-1);
  }

  while(!coeffs.eof()) {
    getline(coeffs,line);
    if(line=="") break;
    std::istringstream in(line);
    std::vector<std::string> tokens;
    for(std::string each; std::getline(in,each,' '); tokens.push_back(each));
    std::istringstream sreal(tokens[0]), simag(tokens[1]);
    float real, imag;
    sreal >> real;
    simag >> imag;
    complex_coeffs.push_back(gr_complex(real, -imag));
  }

  coeffs.close();

  return complex_coeffs;
}

void rotate_coeffs(std::vector<gr_complex> &coeffs)
{
  std::ofstream rcoeff_fh;
  rcoeff_fh.open("coeffs_rotated");
  for(int i=0; i < coeffs.size(); i++) {

    float real = coeffs[i].real();
    float imag = coeffs[i].imag();

    int opt_real, opt_imag;

    if(real>0 && imag>=0) {         // Shift Q1 to (0,1) = 1 = 0b01
      opt_real = 0;
      opt_imag = 1;
      rcoeff_fh << "0 1\n";
    }
    else if(real<=0 && imag>0) {    // Shift Q2 to (-1,0) = 3 = 0b11
      opt_real = 1;
      opt_imag = 1;
      rcoeff_fh << "-1 0\n";
    }
    else if(real<0 && imag<=0) {    // Shift Q3 to (0,-1) = 2 = 0b10
      opt_real = 1;
      opt_imag = 0;
      rcoeff_fh << "0 -1\n";
    }
    else if(real>=0 && imag<0) {    // Shift Q4 to (1,0) = 0 = 0b00
      opt_real = 0;
      opt_imag = 0;
      rcoeff_fh << "1 0\n";
    }
    
    coeffs[i] = gr_complex(opt_real, opt_imag);
  }
  rcoeff_fh.close();
}

gr_complex compute(std::vector<gr_complex> &coeffs, std::vector<gr_complex> &stream)
{
  int real_result=0, imag_result=0;

  // Compute the results
  for(int i=0; i<coeffs.size(); i++) {

    // Not quite inuitive, but its what the FPGA is doing...
    // In binary form, bit 0 is imag, bit 1 is real
    // Binary 0 means addition of the respective component, 1 means subtraction
    // 
    // (1,0)  = a+bi  = 0 = 0b00 
    // (0,1)  = -b+ai = 1 = 0b01 
    // (0,-1) = b-ai  = 2 = 0b10
    // (-1,0) = -a-bi = 3 = 0b11
    int computation = 0;
    computation |= (int)coeffs[i].real()<<1;
    computation |= (int)coeffs[i].imag();

    switch(computation) {

      case 0:
        real_result += (int)stream[i].real();
        imag_result += (int)stream[i].imag();
        break;
      
      case 1:
        real_result -= (int)stream[i].imag();
        imag_result += (int)stream[i].real();
        break;

      case 2:
        real_result += (int)stream[i].imag();
        imag_result -= (int)stream[i].real();
        break;

      case 3:
        real_result -= (int)stream[i].real();
        imag_result -= (int)stream[i].imag();
        break;

      default:
        std::cerr << "wth coefficient is this?" << computation << std::endl;
        exit(-1);
    }

  }

  return gr_complex(real_result,imag_result);
}

int main(int argc, char *argv[])
{
  if(argc!=3) {
    std::cerr << "Usage: ./mfilter_fpga <coeffs> <data>\n";
    return -1;
  }

  // Read coeffs and rotate them
  std::string coeff_filename(argv[1]);
  std::vector<gr_complex> coeffs = read_coeffs(coeff_filename);
  rotate_coeffs(coeffs);

  // Read in short complex data from USRP dump
  std::string data_filename(argv[2]);
  std::ifstream dfile;
  dfile.open(data_filename.c_str(), std::ios::binary|std::ios::in);
  if(!dfile.is_open()) {
    std::cerr << "Could not open binary USRP dump...\n";
    exit(-1);
  }
  
  int16_t real, imag;

  // Read in a buffer of ncoeffs to start the pipeline
  std::vector<gr_complex> stream;
  for(int i=0; i<coeffs.size(); i++) {
    dfile.read((char *)&real, sizeof(real));
    dfile.read((char *)&imag, sizeof(imag));
    stream.push_back(gr_complex(real>>8, imag>>8));
  }

  // Start the pipeline...
  while(!dfile.eof()) {

    // Get a real and imaginary result
    gr_complex result = compute(coeffs, stream);

    // Perform magnitude computation
    int16_t real_result_abs, imag_result_abs;
    uint32_t final_result;
    
    if(result.real()>0)
      real_result_abs = (int32_t)result.real();
    else
      real_result_abs = (int32_t)-result.real();

    if(result.imag()>0)
      imag_result_abs = (int32_t)result.imag();
    else
      imag_result_abs = (int32_t)-result.imag();
      
    if(real_result_abs > imag_result_abs)
      final_result = real_result_abs + imag_result_abs/2;
    else
      final_result = imag_result_abs + real_result_abs/2;

    std::cout << final_result << std::endl;

    // Erase the 0th element and push a new element on to the back
    stream.erase(stream.begin()); 
    dfile.read((char *)&real, sizeof(real));
    dfile.read((char *)&imag, sizeof(imag));
    stream.push_back(gr_complex(real>>8, imag>>8));
  }

  dfile.close();
  return 1;
}
