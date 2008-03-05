#include <usrp_standard.h>

class cmusdrg_mblock_bootstrap;
typedef boost::shared_ptr<cmusdrg_mblock_bootstrap>  cmusdrg_mblock_bootstrap_sptr;
%template(cmusdrg_mblock_bootstrap_sptr)  boost::shared_ptr<cmusdrg_mblock_bootstrap>;

%rename(usrp_ref) cmusdrg_make_mblock_bootstrap;

cmusdrg_mblock_bootstrap_sptr
cmusdrg_make_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx, usrp_standard_rx_sptr usrp_rx);

class cmusdrg_mblock_bootstrap {
    cmusdrg_mblock_bootstrap(usrp_standard_tx_sptr usrp_tx, usrp_standard_rx_sptr usrp_rx);

    public:
        void start();
        void packet();
        void stop();
        ~cmusdrg_mblock_bootstrap();
};

%pythoncode %{
cmusdrg_mblock_bootstrap_sptr.__repr__ = lambda self: "<cmusdrg_mblock_bootstrap %s (%d)>" %(self.name(), self.unique_id())
%}
%ignore cmusdrg_mblock_bootstrap;
