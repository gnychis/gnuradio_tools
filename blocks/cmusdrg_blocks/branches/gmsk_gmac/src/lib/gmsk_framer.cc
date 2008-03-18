/* -*- c++ -*- */
/*
 * Copyright 2007 Free Software Foundation, Inc.
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gmsk.h>
#include <gmsk_framer.h>

static bool verbose = false;

// The framer will use the special flag bit to detect the incoming frame.  To be
// clean this should be a new block, but for performance reasons I'm keeping it
// here.
void gmsk::framer(const std::vector<unsigned char> input, unsigned long timestamp)
{
  int bit=0;
  int nbits=(int)input.size();

  while(bit < nbits) {
    switch(d_state)
    {
      //-------------------------- SYNC_SEARCH -----------------------------//
      // The gr_correlate_access_code block sets the second bit of its output
      // when it detects the end of the framing bits.  Therefore, when we find
      // the second bit set in our input, we know that we've found our framing
      // bits.
      case SYNC_SEARCH:
        if(input[bit] & 0x2) {    // Start of frame marker
          framer_calculate_timestamp(timestamp, bit, nbits);
          framer_found_sync();
          break;
        }
        bit++;
        break;

      //-------------------------- WAIT_HEADER -----------------------------//
      // After we've found the framing bits, we wait for the number of bits in
      // the header to arrive.
      case WAIT_HEADER:
        framer_new_header_bit(input[bit]);
        bit++;
        break;

      //-------------------------- HAVE_HEADER -----------------------------//
      // Once we have enough bits to construct the header, we pack them into our
      // frame header structure.
      case HAVE_HEADER:
        framer_have_header();
        break;

      //-------------------------- WAIT_PAYLOAD ----------------------------//
      // After constructing the header and reading the payload length from it,
      // we wait for a payload number number of bits to arrive.
      case WAIT_PAYLOAD:
        framer_new_payload_bit(input[bit]);
        bit++;
        break;

      //-------------------------- HAVE_PAYLOAD ----------------------------//
      // After receiving the correct number of payload bits, we pack them into a
      // buffer and ship framing information and the bits to the MAC layer.
      case HAVE_PAYLOAD:
        framer_have_payload();
        break;

      default:
        break;
    }
  }
}

// Here, we attempt to approximate the timestamp of the frame by attempting to
// calculate the time of arrival in the FPGA of the first sample that was used
// to create the first symbol, used to create the first bit ;)
//
// The timestamp corresponds to the last sample in the USB block, so we need to
// backcalculate from the total number of bits to the current bit, and then
// backwards further to the synchronization bits.
void gmsk::framer_calculate_timestamp(unsigned long timestamp, int bit, int nbits)
{
  
}

// We have found the framing bits and are now synchronized.
void gmsk::framer_found_sync() 
{
  d_state = WAIT_HEADER;  // Wait for header number of bits.
  d_squelch=false;        // No need to squelch on an incoming frame
  d_hdr_bits.clear();     // Prepare header bits

  if(verbose)
    std::cout << "[GMSK] Found framing bits found\n";
}

// A new bit has arrived, place it in a queue and we will pack all of the bits
// layer into a buffer.
void gmsk::framer_new_header_bit(unsigned char bit)
{
  d_hdr_bits.push_back(bit);

  if(d_hdr_bits.size() == (sizeof(d_frame_hdr_t)*8))
    d_state = HAVE_HEADER;
}

// A new payload bit has arrived.
void gmsk::framer_new_payload_bit(unsigned char bit)
{
  d_payload_bits.push_back(bit);

  if((int)d_payload_bits.size() == (d_cframe_hdr.payload_len * 8)) {
    d_state = HAVE_PAYLOAD;
    if(verbose)
      std::cout << "[GMSK] Have payload\n";
  }
}

void gmsk::framer_have_header()
{
  unsigned char *frame_bp = (unsigned char *)&d_cframe_hdr;

  if(verbose)
    std::cout << "[GMSK] Header's worth of bits\n";

  // Mask out the actual bits from the 'unsigned char' representation and stuff
  // them into the frame.
  for(int hdr_byte=0; hdr_byte < (int)sizeof(d_frame_hdr_t); hdr_byte++) {
    for(int byte_bit=0; byte_bit < 8; byte_bit++) {
      frame_bp[hdr_byte] = (frame_bp[hdr_byte] << 1) | (d_hdr_bits[(8*hdr_byte)+byte_bit] & 0x1);
    }
  }
  
  // Do some logic checks on the payload length, that it's greater than 0 and
  // that it's less than the maximum frame size
  if(!(d_cframe_hdr.payload_len>0) || !(d_cframe_hdr.payload_len <= (MAX_FRAME_SIZE-max_frame_payload()))) {
    if(verbose)
      std::cout << "[GMSK] Improper payload detected\n";
    d_squelch=true;           // start to squelch again
    d_state = SYNC_SEARCH;    // On failure, let's go back to looking for the framing bits
    return;
  }

  if(verbose)
    std::cout << "[GMSK] Have header:"
              << "\n        src: " << d_cframe_hdr.src_addr
              << "\n        dst: " << d_cframe_hdr.dst_addr
              << "\n        payload_len: " << d_cframe_hdr.payload_len
              << "\n        crc: " << d_cframe_hdr.crc
              << "\n        ack: " << d_cframe_hdr.ack
              << std::endl;

  d_state = WAIT_PAYLOAD;   // On success, wait for payload_len worth of bits
}

void gmsk::framer_have_payload()
{
  pmt_t uvec;
  char *vdata;
  size_t ignore;

  // Create a PMT vector to store data
  uvec = pmt_make_u8vector(d_cframe_hdr.payload_len, 0);
  vdata = (char *) pmt_u8vector_writeable_elements(uvec, ignore);
  
  // Pack the bits from a bit-per-char representation into a buffer
  for(int hdr_byte=0; hdr_byte < (int)d_cframe_hdr.payload_len; hdr_byte++) 
    for(int byte_bit=0; byte_bit < 8; byte_bit++) 
      vdata[hdr_byte] = (vdata[hdr_byte] << 1) | (d_payload_bits[(8*hdr_byte)+byte_bit] & 0x1);

  framer_have_frame(uvec);  // Pass the payload bits on
}


void gmsk::framer_have_frame(pmt_t uvec)
{
  pmt_t pkt_properties;
  pkt_properties = pmt_make_dict();
  size_t ignore;
  char *vdata = (char *) pmt_u8vector_writeable_elements(uvec, ignore);
  boost::crc_32_type bcrc;
  
  // Create a dictionary (hash like structure) with frame header information,
  // you can put as much as you want in here
  pmt_dict_set(pkt_properties, pmt_intern("timestamp"), pmt_from_long(d_frame_timestamp));
  pmt_dict_set(pkt_properties, pmt_intern("src"), pmt_from_long(d_cframe_hdr.src_addr));
  pmt_dict_set(pkt_properties, pmt_intern("dst"), pmt_from_long(d_cframe_hdr.dst_addr));

  // If the frame is an ACK, we don't care about payload... lets just pass it up
  if(d_cframe_hdr.ack) {
    pmt_dict_set(pkt_properties, pmt_intern("ack"), PMT_T);
    goto exit_framer_have_frame;
  }

  // Compute a CRC on the payload
  bcrc.reset();
  bcrc.process_bytes(vdata, d_cframe_hdr.payload_len);

  // Compare the computed CRC to the CRC contained in the header
  if(d_cframe_hdr.crc == (int)bcrc.checksum())
    pmt_dict_set(pkt_properties, pmt_intern("crc"), PMT_T);   // CRC passes
  else
    pmt_dict_set(pkt_properties, pmt_intern("crc"), PMT_F);   // CRC failed

  pmt_dict_set(pkt_properties, pmt_intern("ack"), PMT_F);     // Not an ACK

 exit_framer_have_frame:
  d_cs->send(s_response_demod, pmt_list2(uvec, pkt_properties));
  d_payload_bits.clear();   // Clear the payload bits
  d_squelch=true;           // start to squelch again
  d_state = SYNC_SEARCH;    // Go back to searching for the framing bits

  if(verbose)
    std::cout << "[GMSK] Pushing up demoded data\n";
}

