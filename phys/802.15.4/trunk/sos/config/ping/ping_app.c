#include <sos.h>
/**
 * Must also include the header file that defines the 
 * ping_get_header() function.
 */
mod_header_ptr ping_get_header();
mod_header_ptr loader_get_header();

/**
 * application start
 * This function is called once at the end od SOS initialization
 */
void sos_start(void)
{
  ker_register_module(ping_get_header());
	ker_register_module(loader_get_header());
}



