#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <list>
#include <stdlib.h>

const int TSAMPLES=23872;
const int COMP_WINDOW=50;
const int NSKIP=5000;
const int POWER_THRESH=580;
const int MIN_SAMPLES=10000;
const int SHISTORY_WINDOW=300;

std::list<long> power_history;
std::list<long> shistory;

enum state_t {
  IDLE,
  MONITORING,
  SKIPPING
};
state_t curr_state;

enum result_t {
  PASS,
  FAIL,
  FP
};
result_t result;

long curr_average;
long samples_left;
long ntransmissions;
long tx_max;
long curr_max;

const float PTHRESH=0.18;
const float HTHRESH=85;

std::ofstream ofile;

inline std::string stringify(long x)
{
  std::ostringstream o;
  o << x;
  return o.str();
} 

void print_history()
{
  std::list<long>::iterator power_it;
  for(power_it = shistory.begin(); power_it != shistory.end(); power_it++) 
    ofile << *power_it << std::endl;
}

void check_power(long mf_flag, long power)
{
  long error;

  switch(curr_state) {

    case IDLE:
      if(mf_flag==1) {
        samples_left=TSAMPLES;
        tx_max=curr_max;
        curr_state=MONITORING;
        ofile.open("/tmp/out");
        print_history();
      }
    break;

    case MONITORING:
//      error = std::abs(curr_average-tx_average);
//      if(error>POWER_THRESH) {
//        std::cout << " fail\n";
//        samples_left+=NSKIP;
//        curr_state=SKIPPING;
//      } 
      if(power>(tx_max+HTHRESH)) {
        std::cout << "fail " << ntransmissions++ << std::endl;
        result=FAIL;
        samples_left+=NSKIP;
        curr_state=SKIPPING;
      }
      if(power < 50) {
        std::string txs = stringify(ntransmissions-1);
        std::cout << " false positive\n";
        system(std::string("mv /tmp/out /home/gnychis/school/gr/cmu_sdrg/tx_quality/transmissions/fp_"+txs).c_str());
        samples_left=0;
        curr_state=IDLE;
      }
      samples_left--;
      if(samples_left==0) {
        std::cout << "pass " << ntransmissions++ << std::endl;
        result=PASS;
        curr_state=SKIPPING;
        samples_left=NSKIP;
      }
    fflush(stdout);
    break;

    case SKIPPING:
      if(samples_left>0) {
        samples_left--;
      } else { 
        curr_state=IDLE; {
        ofile.close();
        std::string txs = stringify(ntransmissions-1);
        if(result==PASS || result==FAIL)
          system(std::string("mv /tmp/out /home/gnychis/school/gr/cmu_sdrg/tx_quality/transmissions/tx_"+txs).c_str());
        }
      }
    break;

    default:
    break;
  }
  if(ofile.is_open())
    ofile << power << std::endl;
}

void compute_average(long power)
{  
  power_history.push_back(power);
  shistory.push_back(power);

  if(power_history.size()<COMP_WINDOW) 
    return;

  if(shistory.size()<SHISTORY_WINDOW)
    return;

  power_history.pop_front();
  shistory.pop_front();

  std::list<long>::iterator power_it;
  curr_max=0;
  for(power_it = power_history.begin(); power_it != power_history.end(); power_it++) {
//    sum += *power_it;
    if(*power_it>curr_max)
      curr_max=*power_it;
  }

//  curr_average = sum/COMP_WINDOW;
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
