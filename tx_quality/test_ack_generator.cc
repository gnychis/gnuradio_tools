#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <list>

const int TSAMPLES=23872;
const int COMP_WINDOW=20;

std::list<unsigned long> power_history;

unsigned long tx_average;
unsigned long curr_average;

void compute_average(unsigned long power)
{  
  power_history.push_back(power);

  if(power_history.size()<COMP_WINDOW) 
    return;

  power_history.pop_front();

  unsigned long long sum;
  std::list<unsigned long>::iterator power_it;
  for(power_it = power_history.begin(); power_it != power_history.end(); power_it++)
    sum += *power_it;

  curr_average = sum/COMP_WINDOW;
}

int main(int argc, char **argv) {

  std::string curr_line;

  // Input format:
  //   src_ip dst_ip src_port dst_port src_pkts dst_pkts
  while(std::cin) {

    getline(std::cin, curr_line);     // read line from input
    std::istringstream in(curr_line); // put curr line to split

    if(curr_line=="") break;

    std::vector<std::string> tokens;
    for(std::string each; std::getline(in,each,'\t'); tokens.push_back(each));

    // Convert the ports to integers
    unsigned long mf_flag, power;
    std::istringstream mf(tokens[0]), pow(tokens[1]);
    mf >> mf_flag;
    pow >> power;

    compute_average(power);
  }

  return 1;
}
