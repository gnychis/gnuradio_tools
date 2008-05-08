#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <list>

const int TSAMPLES=23872;
const int COMP_WINDOW=100;
const int NSKIP=5000;
const int POWER_THRESH=580;
const int MIN_SAMPLES=10000;

std::list<long> power_history;

enum state_t {
  IDLE,
  MONITORING,
  SKIPPING
};
state_t curr_state;

long tx_average;
long curr_average;
long samples_left;
long ntransmissions;
long tx_max;
long curr_max;

void check_power(long mf_flag, long power)
{
  long error;

  switch(curr_state) {

    case IDLE:
      if(mf_flag==1) {
        samples_left=TSAMPLES;
        tx_average=curr_average;
        tx_max=curr_max;
        curr_state=MONITORING;
      }
    break;

    case MONITORING:
//      error = std::abs(curr_average-tx_average);
//      if(error>POWER_THRESH) {
//        std::cout << " fail\n";
//        samples_left+=NSKIP;
//        curr_state=SKIPPING;
//      } 
      if(power>(tx_max+(0.18*tx_max))) {
        std::cout << ntransmissions++ << " fail\n";
        samples_left+=NSKIP;
        curr_state=SKIPPING;
      }
      if(power < 100) {
        std::cout << " false positive\n";
        samples_left=0;
        curr_state=IDLE;
      }
      samples_left--;
      if(samples_left==0) {
        std::cout << ntransmissions++ <<  " success\n";
        curr_state=SKIPPING;
        samples_left=NSKIP;
      }
    break;

    case SKIPPING:
      if(samples_left>0)
        samples_left--;
      else 
        curr_state=IDLE;
    break;

    default:
    break;
  }
}

void compute_average(long power)
{  
  power_history.push_back(power);

  if(power_history.size()<COMP_WINDOW) 
    return;

  power_history.pop_front();

  long long sum;
  std::list<long>::iterator power_it;
  curr_max=0;
  for(power_it = power_history.begin(); power_it != power_history.end(); power_it++) {
    sum += *power_it;
    if(*power_it>curr_max)
      curr_max=*power_it;
  }

  curr_average = sum/COMP_WINDOW;
}

int main(int argc, char **argv) {

  std::string curr_line;

  ntransmissions=0;
  curr_state=SKIPPING;
  samples_left=10000;

  // Input format:
  //   src_ip dst_ip src_port dst_port src_pkts dst_pkts
  while(std::cin) {

    getline(std::cin, curr_line);     // read line from input
    std::istringstream in(curr_line); // put curr line to split

    if(curr_line=="") break;

    std::vector<std::string> tokens;
    for(std::string each; std::getline(in,each,'\t'); tokens.push_back(each));

    // Convert the ports to integers
    long mf_flag, power;
    std::istringstream mf(tokens[0]), pow(tokens[1]);
    mf >> mf_flag;
    pow >> power;

    compute_average(power);
    check_power(mf_flag, power);
  }

  return 1;
}
