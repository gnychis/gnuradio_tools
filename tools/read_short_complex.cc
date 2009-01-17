#include <iostream>
#include <fstream>
#include <complex>

typedef int16_t data_t;

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cout << "Usage: ./read_complex <data_file>\n";
    return -1;
  }

  std::ifstream infile;

  infile.open(argv[1], std::ios::binary|std::ios::in);
  if(!infile.is_open())
    return -1;
    
  data_t real, imag;

  infile.read((char *)&real, sizeof(data_t));
  infile.read((char *)&imag, sizeof(data_t));

  while(!infile.eof()) {
    printf("%d %d\n", real, imag);
    infile.read((char *)&real, sizeof(data_t));
    infile.read((char *)&imag, sizeof(data_t));
  }

  infile.close();
}
