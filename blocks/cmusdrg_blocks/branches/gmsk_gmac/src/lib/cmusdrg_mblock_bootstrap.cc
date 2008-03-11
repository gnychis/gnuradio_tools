#include <cmusdrg_mblock_bootstrap.h>
#include <iostream>

#define verbose 0

cmusdrg_mblock_bootstrap::~cmusdrg_mblock_bootstrap()
{

}

cmusdrg_mblock_bootstrap_sptr
cmusdrg_make_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx,
                              usrp_standard_rx_sptr usrp_rx,
                              char *block_name,
                              const std::vector<std::string> &argv)
{
  return cmusdrg_mblock_bootstrap_sptr(new cmusdrg_mblock_bootstrap(usrp_tx,usrp_rx,block_name,argv));
}

cmusdrg_mblock_bootstrap::cmusdrg_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx,
                                                    usrp_standard_rx_sptr usrp_rx,
                                                    char *block_name,
                                                    const std::vector<std::string> &argv)
{
  d_usrp_tx = usrp_tx.get();
  d_usrp_rx = usrp_rx.get();

  d_block_name = std::string(block_name); 
  
  if(verbose)
    std::cout << "[MBLOCK_BOOTSTRAP] Initializing " << d_block_name << std::endl;

  d_argv.assign(argv.begin(), argv.end());
}

void cmusdrg_mblock_bootstrap::start()
{
  mb_runtime_sptr rt = mb_make_runtime();
  pmt_t result = PMT_NIL;

  pmt_t args = pmt_list2(pmt_list2(pmt_make_any(d_usrp_tx), pmt_make_any(d_usrp_rx)), pmt_make_any(d_argv));

  // Do something intelligent about which mblock to start
  rt->run(d_block_name, d_block_name, args, &result);
}

void cmusdrg_mblock_bootstrap::stop()
{
  d_usrp_tx->wait_for_completion();
}
