#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

int main(int argc, char **argv) {

  std::string curr_line;

  getline(std::cin, curr_line);     // skip the header description line in flow-export

  // Input format:
  //   src_ip dst_ip src_port dst_port src_pkts dst_pkts
  while(std::cin) {

    getline(std::cin, curr_line);     // read line from input
    std::istringstream in(curr_line); // put curr line to split

    if(curr_line=="") break;

    std::vector<std::string> tokens;
    for(std::string each; std::getline(in,each,','); tokens.push_back(each));

    // Convert the ports to integers
    float flag, power;
    std::istringstream mf(tokens[0]), pow(tokens[1]);
    mf >> flag;
    pow >> power;

    std::cout << flag << " " << power << std::endl;
  }

  return 1;
}
