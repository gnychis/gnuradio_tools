#include <sstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

int main(int argc, char **argv) {

  getline(std::cin, curr_line);     // skip the header description line in flow-export

  // Input format:
  //   src_ip dst_ip src_port dst_port src_pkts dst_pkts
  while(std::cin) {

    getline(std::cin, curr_line);     // read line from input
    std::istringstream in(curr_line); // put curr line to split

    if(curr_line=="") break;

    std::vector<std::string> tokens;
    for(std::string each; std::getline(in,each,','); tokens.push_back(each));

    if(tokens.size() != 5) 
      continue;

    // Read the src and dst IPs
    std::string src_ip, dst_ip;
    std::istringstream sip(tokens[1]), dip(tokens[2]);
    sip >> src_ip;
    dip >> dst_ip;

    if(excluded_hosts[src_ip])
      continue;

    if(excluded_hosts[dst_ip])
      continue;

    // Convert the ports to integers
    int src_port, dst_port;
    std::istringstream sp(tokens[3]), dp(tokens[4]);
    sp >> src_port;
    dp >> dst_port;

    if(src_port > MAX_PORT || dst_port > MAX_PORT)
      continue;
    
    // Finally, read the packets
    unsigned long pkts;
    std::istringstream pk(tokens[0]);
    pk >> pkts;

    take_stats(src_ip, dst_ip, src_port, dst_port, pkts); 
  }

  std::cout << "Outputting\n";
  fflush(stdout);
  
  // Output FSD stats
  std::ofstream fsd_out;
  std::map<int,int>::iterator fsd_iter;
  fsd_out.open((std::string("working/fsd_stats_")+timestamp).c_str());
  for(fsd_iter=fsd_stats.begin(); fsd_iter!=fsd_stats.end(); fsd_iter++)
    fsd_out << fsd_iter->first << " " << fsd_iter->second << std::endl;
  fsd_out.close();
  fsd_stats.clear();

  // Output src port stats
  std::ofstream sport_out;
  sport_out.open((std::string("working/sport_stats_")+timestamp).c_str());
  for(int csp=0; csp<MAX_PORT; csp++)
    sport_out << csp << " " << src_port_pkts[csp] << std::endl;
  sport_out.close();

  // Output dst port stats
  std::ofstream dport_out;
  dport_out.open((std::string("working/dport_stats_")+timestamp).c_str());
  for(int csp=0; csp<MAX_PORT; csp++)
    dport_out << csp << " " << dst_port_pkts[csp] << std::endl;
  dport_out.close();

  // Output src/dst addresses 
  std::ofstream saddr_out, daddr_out;
  saddr_out.open((std::string("working/saddr_stats_")+timestamp).c_str());
  daddr_out.open((std::string("working/daddr_stats_")+timestamp).c_str());
  std::map<std::string,struct addr_stats_s>::iterator addr_iter;
  for(addr_iter=addr_stats.begin(); addr_iter!=addr_stats.end(); addr_iter++) {
    unsigned long src_pkts = (addr_iter->second).src_pkts,
                  dst_pkts = (addr_iter->second).dst_pkts;

    if(src_pkts!=0)
      saddr_out << addr_iter->first << " " << src_pkts << std::endl;

    if(dst_pkts!=0)
      daddr_out << addr_iter->first << " " << dst_pkts << std::endl;
  }
  addr_stats.clear();
  saddr_out.close();
  daddr_out.close();

  return 1;
}
