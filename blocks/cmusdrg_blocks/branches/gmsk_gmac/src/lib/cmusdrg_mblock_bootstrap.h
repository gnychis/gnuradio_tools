#ifndef INCLUDED_CMUSDRG_MBLOCK_BOOTSTRAP_H
#define INCLUDED_CMUSDRG_MBLOCK_BOOTSTRAP_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <usrp_standard.h>
#include <gr_types.h>
#include <string>
#include <vector>

class cmusdrg_mblock_bootstrap;
typedef boost::shared_ptr<cmusdrg_mblock_bootstrap> cmusdrg_mblock_bootstrap_sptr;

class usrp_standard_tx;
typedef boost::shared_ptr<usrp_standard_tx> usrp_standard_tx_sptr;

class usrp_standard_rx;
typedef boost::shared_ptr<usrp_standard_rx> usrp_standard_rx_sptr;

cmusdrg_mblock_bootstrap_sptr cmusdrg_make_mblock_bootstrap(usrp_standard_tx_sptr, usrp_standard_rx_sptr, char *, int, char *[]);

class cmusdrg_mblock_bootstrap {

    cmusdrg_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx, usrp_standard_rx_sptr usrp_rx, char *block_name, int argc, char *argv[]);

    usrp_standard_tx* d_usrp_tx;
    usrp_standard_rx* d_usrp_rx;
    std::string d_block_name;
    std::vector<std::string> d_argv;

    friend cmusdrg_mblock_bootstrap_sptr cmusdrg_make_mblock_bootstrap(usrp_standard_tx_sptr, usrp_standard_rx_sptr, char *, int argc, char *argv[]);

    public:
        void start();
        void stop();
        ~cmusdrg_mblock_bootstrap();
};

/* Mblock stuff */
#include <mb_mblock.h>
#include <mb_runtime.h>
#include <mb_protocol_class.h>
#include <mb_exception.h>
#include <mb_msg_queue.h>
#include <mb_message.h>
#include <mb_msg_accepter.h>
#include <mb_class_registry.h>
#include <pmt.h>

/* GMAC */
#include <gmac.h>
#include <gmac_symbols.h>
/* GMAC */

#endif 
