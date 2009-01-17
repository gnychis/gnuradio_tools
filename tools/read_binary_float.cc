#include <iostream>
#include <fstream>
#include <complex>

typedef float data_t;

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cout << "Usage: ./read <data_file>\n";
    return -1;
  }

  std::ifstream infile;

  infile.open(argv[1], std::ios::binary|std::ios::in);
  if(!infile.is_open())
    return -1;
    
  data_t curr;
  infile.read((char *)&curr, sizeof(data_t));

  while(!infile.eof()) {
    printf("%f\n", curr);
    infile.read((char *)&curr, sizeof(data_t));
  }

  infile.close();
}
