#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

const int tsamples=23872;

// State
bool first;
bool monitoring;
long samples_left;
long ntransmission;

// Stats
unsigned long avg, min, max;
unsigned long long sum;

void compute()
{
  bool ack;

  if(first) {
    std::cout << ntransmission << "1";
    first=false;
    return;
  }

  avg=sum/tsamples;

}

void handle(unsigned long power)
{
  if(!monitoring && first) {
    monitoring=true;
    samples_left=tsamples;
  }

  sum+=power;
  samples_left--;

  if(samples_left==0)
    compute();
}

int main(int argc, char **argv) {

  std::string curr_line;

  first=true;

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

    if(mf_flag || monitoring)
      handle(power);

    std::cout << mf_flag << " " << power << std::endl;
  }

  return 1;
}
