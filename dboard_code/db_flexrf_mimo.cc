

#include "db_flexrf_mimo.h"
#include <usrp_standard.h>
#include <iostream>
#include <assert.h>

using namespace std;

db_flexrf_mimo::db_flexrf_mimo(usrp_standard_rx* rx,usrp_standard_tx* tx, unsigned int side) {

  d_rx=rx;
  d_tx=tx;
  d_side=side;
  dbid_rx=d_rx -> daughterboard_id(d_side);   
  dbid_tx=d_tx -> daughterboard_id(d_side);   

  rx_is_configured=false;
  tx_is_configured=false;


  switch (dbid_rx) {
  
     case 39:
     case 52:
         freq_mult=1;
         phdet_freq=64e6/16;
         R=3407936;
         control=5228836;
         prescaler=16;
         Nconstant=0;
      
       break;
     
     default:
       cout<<"Sorry, this daughterboard (" << dbid_rx << ") is not implemented yet! \n";
       exit(1);
       break;
  };

  switch (dbid_tx) {
  
     case 43:
     case 53:
     
       break;

     default:
       cout<<"Sorry, this daughterboard (" << dbid_tx << ") is not implemented yet! \n";
       exit(1);  
       break;
  };

  if (side>1) {
    cout << "Side must be 0 or 1";
    exit(1);
  };

}

void db_flexrf_mimo::select_rx2(void ) {
  if (rx_is_configured) {
             d_rx->write_io(d_side,RX2_RX1N,RX2_RX1N);
  };

}

void db_flexrf_mimo::select_tx(void ) {
  if (tx_is_configured) {
    d_tx->write_io(d_side,~RX_TXN,RX_TXN);
  };

}

float db_flexrf_mimo::configure(float freq,unsigned int gain,unsigned int rxtx) {
  

    if (rxtx>1) {
      cout << "txrx>1 ! \n";
      exit(1);
    };


    d_rx->_write_oe(0,0,0xffff);
    if (d_side==0)
      if (rxtx==0)
        d_rx->_write_fpga_reg (FR_RX_A_REFCLK, 0);
      else
        d_tx->_write_fpga_reg (FR_TX_A_REFCLK, 0);
    else
      if (rxtx==0)
        d_rx->_write_fpga_reg (FR_RX_B_REFCLK, 0);
      else
        d_tx->_write_fpga_reg (FR_TX_B_REFCLK, 0);

    if (gain>4095)
      gain=4095;

    if (rxtx==0) {
       set_rx_gain(gain);

       d_rx->_write_oe(d_side,POWER_UP|RX2_RX1N|ENABLE,0xffff); 
       d_rx->write_io(d_side,
		   (~POWER_UP) |RX2_RX1N|ENABLE,POWER_UP|RX2_RX1N|ENABLE);

       d_rx->write_io(d_side,0,RX2_RX1N);
    } else {

      //d_tx->set_pga(d_side*2+0,d_tx->pga_max());
      //d_tx->set_pga(d_side*2+1,d_tx->pga_max());

      d_tx->_write_oe(d_side,(POWER_UP|RX_TXN|ENABLE), 0xffff);
      d_tx->write_io(d_side,((~POWER_UP) |RX_TXN), (POWER_UP|RX_TXN|ENABLE));

    }

    if (rxtx==0) {
      if (d_side==0) {
        d_rx->set_adc_buffer_bypass(0,1);  
        d_rx->set_adc_buffer_bypass(1,1);
      } else {
        d_rx->set_adc_buffer_bypass(2,1);  
        d_rx->set_adc_buffer_bypass(3,1);
      };
    };

    desired_n=(int) (freq*freq_mult/phdet_freq+0.5);     

    

    float actual_freq=desired_n * phdet_freq;

    int B = (int) (desired_n/prescaler);


    int B_DIV=B;
    int A=(int) (desired_n - prescaler*B);
    int A_DIV=A;


     if (B_DIV<A_DIV) {
       cout << "B_DIV<<A_DIV !\n";
       exit(1);
     };


    unsigned int N = (B_DIV << 8) | (A_DIV<<2) | Nconstant;


    write_it((R & ~0x3) | 1,d_side*2+rxtx);


    write_it((control & ~0x3) | 0,d_side*2+rxtx);
    
    // wait 10ms


    clockid_t c1=CLOCK_REALTIME;
    struct timespec *res;
    struct timespec tp1, tp2;
    double elapsed_time;

    clock_gettime(CLOCK_REALTIME,&tp1);
    do {
      clock_gettime(CLOCK_REALTIME,&tp2);
      elapsed_time=tp2.tv_sec-tp1.tv_sec + (tp2.tv_nsec-tp1.tv_nsec)/1e9;
    } while (elapsed_time < 0.010);


    write_it((N & ~0x3) | 2, d_side*2+rxtx);

    int lock_detect;
    d_rx->read_io (d_side, &lock_detect);
    lock_detect=lock_detect & PLL_LOCK_DETECT;
    d_rx->read_io (d_side, &lock_detect);
    lock_detect=lock_detect & PLL_LOCK_DETECT;

    if (lock_detect==0) {
      cout << "lock_detect==0 !! \n";
      exit(1);
    };

    if (rxtx==0)
      rx_is_configured=true;
    else
      tx_is_configured=true;

    return actual_freq;


}

void db_flexrf_mimo::set_rx_gain(long gain)
{
  float pga_gain, agc_gain;
  float V_maxgain, V_mingain, V_fullscale;
  float dac_value;

  float maxgain = d_rx->pga_max()+70 - d_rx->pga_max();
  float mingain = d_rx->pga_min();

  if(gain>maxgain) {
    pga_gain = gain-maxgain;
    assert(pga_gain <= d_rx->pga_max());
    agc_gain = maxgain;
  } else {
    pga_gain = 0;
    agc_gain = gain;
  }
  V_maxgain = 0.2;
  V_mingain = 1.2;
  V_fullscale = 3.3;
  dac_value = (agc_gain*(V_maxgain-V_mingain)/(maxgain-mingain) + V_mingain)*4096/V_fullscale;
  assert(dac_value>=0);
  assert(dac_value<4096);
  std::cout << "dac_value: " << dac_value << std::endl;
  std::cout << "pga_gaine: " << pga_gain << std::endl;
  d_rx->write_aux_dac(0, 0, (int)dac_value);
  d_rx->set_pga(0, (int)pga_gain);
}


void db_flexrf_mimo::write_it(unsigned int v,unsigned int slot) {
  char *s1,*s2,*s3, s1c, s2c, s3c;
  std::string str=std::string();

  s1=&s1c;  s2=&s2c;  s3=&s3c; 


  *s1=static_cast<char>(((v >> 16) & 0xff));
  *s2=static_cast<char>(((v >> 8) & 0xff));
  *s3=static_cast<char>(((v >> 0) & 0xff));

  str.append(string(s1,1));
  str.append(string(s2,1));
  str.append(string(s3,1));

  switch (slot) {
  case 0:
    d_rx->_write_spi (0,SPI_ENABLE_RX_A,0,str);
    break;
  case 1:
    d_rx->_write_spi (0,SPI_ENABLE_TX_A,0,str);
    break;
  case 2:
    d_rx->_write_spi (0,SPI_ENABLE_RX_B,0,str);
    break;
  case 3:
    d_rx->_write_spi (0,SPI_ENABLE_TX_B,0,str);
    break;
  };  

};


