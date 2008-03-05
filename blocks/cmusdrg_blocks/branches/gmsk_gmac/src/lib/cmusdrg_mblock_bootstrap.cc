#include <cmusdrg_mblock_bootstrap.h>
#include <stdio.h>

cmusdrg_mblock_bootstrap::~cmusdrg_mblock_bootstrap()
{

}

cmusdrg_mblock_bootstrap_sptr
cmusdrg_make_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx,
                              usrp_standard_rx_sptr usrp_rx)
{
  return cmusdrg_mblock_bootstrap_sptr(new cmusdrg_mblock_bootstrap(usrp_tx,usrp_rx));
}

cmusdrg_mblock_bootstrap::cmusdrg_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx,
                                                    usrp_standard_rx_sptr usrp_rx)
{
  d_usrp_tx = usrp_tx.get();
  d_usrp_rx = usrp_rx.get();

  d_usrp_tx->start();
  d_usrp_rx->start();
}

void cmusdrg_mblock_bootstrap::start()
{
  mb_runtime_sptr rt = mb_make_runtime();
  pmt_t result = PMT_NIL;

  pmt_t args = pmt_list2(pmt_make_any(d_usrp_tx), pmt_make_any(d_usrp_rx));

  // Do something intelligent about which mblock to start
  rt->run("gmac_rx_file", "gmac_rx_file", args, &result);
}

void cmusdrg_mblock_bootstrap::stop()
{
  d_usrp_tx->wait_for_completion();
}
