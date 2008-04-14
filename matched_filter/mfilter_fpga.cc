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
    complex_coeffs.push_back(gr_complex(real, imag));
  }

  coeffs.close();

  std::cout << "Read " << complex_coeffs.size() << " from " << filename << "...\n";

  return complex_coeffs;
}

void rotate_coeffs(std::vector<gr_complex> &coeffs)
{
  std::cout << "Rotating " << coeffs.size() << " coefficients\n";

  for(int i=0; i < coeffs.size(); i++) {

    float real = coeffs[i].real();
    float imag = coeffs[i].imag();

    int opt_real, opt_imag;

    if(real>0 && imag>=0) {         // Shift Q1 to (0,1) = 1 = 0b00
      opt_real = 0;
      opt_imag = 1;
    }
    else if(real<=0 && imag>0) {    // Shift Q2 to (-1,0) = 3 = 0b11
      opt_real = 1;
      opt_imag = 1;
    }
    else if(real<0 && imag<=0) {    // Shift Q3 to (0,-1) = 2 = 0b10
      opt_real = 1;
      opt_imag = 0;
    }
    else if(real>=0 && imag<0) {    // Shift Q4 to (1,0) = 0 = 0b00
      opt_real = 0;
      opt_imag = 0;
    }
    
    coeffs[i] = gr_complex(opt_real, opt_imag);
  }
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

  // Read in a buffer of ncoeffs to start the pipeline
  uint16_t real, imag;
  std::vector<gr_complex> stream;
  for(int i=0; i<coeffs.size(); i++) {
    dfile.read((char *)&real, sizeof(real));
    dfile.read((char *)&imag, sizeof(imag));
    stream.push_back(gr_complex(0xff00 & real, 0xff00 & imag));
  }

  // Start the pipeline...
  while(!dfile.eof()) {
    // Compute real
    // Compute imag
    // Compute result

    // Erase the 0th element and push a new element on to the back
    stream.erase(stream.begin()); 
    dfile.read((char *)&real, sizeof(real));
    dfile.read((char *)&imag, sizeof(imag));
    stream.push_back(gr_complex(0xff00 & real, 0xff00 & imag));
  }

  dfile.close();
  return 1;
}
