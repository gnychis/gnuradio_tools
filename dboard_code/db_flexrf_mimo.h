/* -*- c++ -*- */
/*
 * Copyright 2003,2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DB_FLEXRF_MIMO_H
#define INCLUDED_DB_FLEXRF_MIMO_H

#include <usrp_standard.h>




// These defines are taken from db_flexrf.py

#define FR_TX_A_REFCLK          40
#define FR_RX_A_REFCLK          41
#define FR_TX_B_REFCLK          42
#define FR_RX_B_REFCLK          43

#define MIN_GAIN 0.0
#define MAX_GAIN 90.0
#define GAIN_RES 0.05

#define PLL_LOCK_DETECT  (1 << 2)


#define POWER_UP (1 << 7)   // enables power supply
#define RX2_RX1N (1 << 6)   // Rx only: antenna switch between RX2 and TX/RX port
#define RX_TXN (1 << 6)  
#define ENABLE  (1 << 5)    // enables mixer
#define AUX_RXAGC (1 << 8)



// These defines are taken from usrp_spi_defs.h 
#define SPI_ENABLE_TX_A         0x10    // select d'board TX A
#define SPI_ENABLE_RX_A         0x20    // select d'board RX A
#define SPI_ENABLE_TX_B         0x40    // select d'board TX B
#define SPI_ENABLE_RX_B         0x80    // select d'board RX B




class db_flexrf_mimo {

  public:
 
  /*!
   * \brief Instantiate a flexradio daughterboard.
   * 
   * \param rx          
   * \param tx          
   * \param side.       Which daughterboard =0 for A, =1 for B. 
   */

  db_flexrf_mimo(usrp_standard_rx *rx,usrp_standard_tx *tx, unsigned int side);

  /*!
   * \brief Configure flexradio daughterboard
   * 
   * 
   * \param desired_freq.  The desired frequency of the LO.
   * \param gain.          The gain in receiving mode [0,4095].
   * \param rxtx           If rxtx=0 then the RX is configured, otherwise the tx.
   * \returns the actual frequency of the LO 
   */
  float  configure(float desired_freq,unsigned int gain,unsigned int rxtx); 

  /*!
   * \brief Select the rx2 port as input for the rx.    
   */
  void select_rx2(void );

  /*!
   * \brief Connect the TX to the RX/TX port.    
   */
  void select_tx(void );

   /*!
    * \brief Connect the TX/RX antenna to the transmitter.
    */
   void set_tx(void);
   /*!
    * brief Connected the TX/RX antenna to the receiver.
    */   
   void set_rx(void);

   void set_rx_gain(long);
   void set_tx_atr_mask(long);
   void set_tx_atr_txval(long);
   void set_tx_atr_rxval(long);
   void set_rx_atr_mask(long);
   void set_rx_atr_txval(long);
   void set_rx_atr_rxval(long);
   void set_tx_auto_tr(bool);
   void set_rx_auto_tr(bool);
  private: 

  void write_it(unsigned int,unsigned int);

    unsigned int dbid_rx, dbid_tx,d_side, R_DIV, desired_n, R, control;
    unsigned int Nconstant;
    float  refclk_divisor,refclk_freq,phdet_freq,prescaler,freq_mult;

    usrp_standard_rx* d_rx;
    usrp_standard_tx* d_tx;

    bool rx_is_configured;
    bool tx_is_configured;
};


#endif //INCLUDED_DB_FLEXRF_MIMO_H
