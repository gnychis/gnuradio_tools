#include <iostream>
#include <fstream>
#include <complex>

typedef std::complex<float> data_t;

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cout << "Usage: ./read_complex <data_file>\n";
    return -1;
  }

  std::ifstream infile;

  infile.open(argv[1], std::ios::binary|std::ios::in);
  if(!infile.is_open())
    exit(-1);
    
  data_t curr;
  int16_t first,second;
  float snum = 0;

  infile.read((char *)&first, sizeof(int16_t));
  infile.read((char *)&second, sizeof(int16_t));

  while(!infile.eof()) {
    printf("%f %d %d\n", snum, first, second);
    infile.read((char *)&first, sizeof(int16_t));
    infile.read((char *)&second, sizeof(int16_t));
    snum+=.125;
  }

  infile.close();
}
