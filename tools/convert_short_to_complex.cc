#include <iostream>
#include <fstream>
#include <complex>
#include <stdint.h>

typedef int16_t data_t;
typedef std::complex<float> data2_t;

int main(int argc, char *argv[]) {

  if(argc != 3) {
    std::cout << "Usage: ./read_complex <data_file> <out>\n";
    return -1;
  }

  std::ifstream infile;
  std::ofstream ofile;

  infile.open(argv[1], std::ios::binary|std::ios::in);
  ofile.open(argv[2], std::ios::binary|std::ios::out);
  if(!infile.is_open() || !ofile.is_open())
    return -1;
    
  data_t real, imag;
  data2_t comp;

  infile.read((char *)&real, sizeof(data_t));
  infile.read((char *)&imag, sizeof(data_t));
  comp = data2_t(real,imag);
  ofile.write((const char *)&comp, sizeof(comp));


  while(!infile.eof()) {
    infile.read((char *)&real, sizeof(data_t));
    infile.read((char *)&imag, sizeof(data_t));
    comp = data2_t(real,imag);
    ofile.write((const char *)&comp, sizeof(comp));
  }

  infile.close();
  ofile.close();
}
