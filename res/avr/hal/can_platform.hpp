// Copyright (C) 2013  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/**
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		can_platform.hpp
 *  A header file for the AVR platform specific types for the CAN Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which implements various public types and enums that will differ between platforms for the can module.
 * 
 *  @author		George Xian
 *
 *  @date		7-02-2013
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2013  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  @section Description
 *
 * These are the public enums and types that are specific to the AVR platform.
 */

// Only include this header file once.
#ifndef __CAN_PLATFORM_H__
#define __CAN_PLATFORM_H__

// INCLUDE REQUIRED HEADER FILES.

#include <stdint.h>

/******************* Macros for AVR registers ************************/

// Globals to hold register values that set the baud rate

 
// Pin mappings
#if defined(__AVR_AT90CAN128__)
	#define CAN_PORT_IN     PORT_D
	#define CAN_PORT_DIR    DDRD
	#define CAN_PORT_OUT    PORT_D
	#define CAN_INPUT_PIN   PIN_6
	#define CAN_OUTPUT_PIN  PIN_5
#endif

#if defined (__AVR_ATmega64M1__)
	#define CAN_PORT_IN     PORT_C 
	#define CAN_PORT_DIR    DDRC
	#define CAN_PORT_OUT    PORT_C 
	#define CAN_INPUT_PIN   PIN_3 
	#define CAN_OUTPUT_PIN  PIN_2
#endif

// Masks
#define ERR_GEN_MSK ((1<<SERG)|(1<<CERG)|(1<<FERG)|(1<<AERG))            //! MaSK for GENeral ERRors INTerrupts
#define INT_GEN_MSK ((1<<BOFFIT)|(1<<BXOK)|(ERR_GEN_MSK))                //! MaSK for GENeral INTerrupts

#define BRP_MSK     ((1<<BRP5)|(1<<BRP4)|(1<<BRP3)|(1<<BRP2)|(1<<BRP1)|(1<<BRP0))  //! Mask for BRP in CANBT1
#define SJW_MSK     ((1<<SJW1)|(1<<SJW0))                                //! MaSK for SJW  in CANBT2
#define PRS_MSK     ((1<<PRS2)|(1<<PRS1)|(1<<PRS0))                      //! MaSK for PRS  in CANBT2
#define PHS2_MSK    ((1<<PHS22)|(1<<PHS21)|(1<<PHS20))                   //! MaSK for PHS2 in CANBT2
#define PHS1_MSK    ((1<<PHS12)|(1<<PHS11)|(1<<PHS10))                   //! MaSK for PHS1 in CANBT2
#define BRP         (BRP0)                                               //! BRP  in CANBT1
#define SJW         (SJW0)                                               //! SJW  in CANBT2
#define PRS         (PRS0)                                               //! PRS  in CANBT2
#define PHS2        (PHS20)                                              //! PHS2 in CANBT2
#define PHS1        (PHS10)                                              //! PHS1 in CANBT2

#define HPMOB_MSK   ((1<<HPMOB3)|(1<<HPMOB2)|(1<<HPMOB1)|(1<<HPMOB0))    //! MaSK for MOb in HPMOB
#define MOBNB_MSK   ((1<<MOBNB3)|(1<<MOBNB2)|(1<<MOBNB1)|(1<<MOBNB0))    //! MaSK for MOb in CANPAGE

#define ERR_MOB_MSK ((1<<BERR)|(1<<SERR)|(1<<CERR)|(1<<FERR)|(1<<AERR))  //! MaSK for MOb ERRors
#define INT_MOB_MSK ((1<<TXOK)|(1<<RXOK)|(1<<BERR)|(1<<SERR)|(1<<CERR)|(1<<FERR)|(1<<AERR)) //! MaSK for MOb INTerrupts

#define CONMOB_MSK  ((1<<CONMOB1)|(1<<CONMOB0))                          //! MaSK for CONfiguration MOb
#define DLC_MSK     ((1<<DLC3)|(1<<DLC2)|(1<<DLC1)|(1<<DLC0))            //! MaSK for Data Length Coding
#define CONMOB      (CONMOB0)                                            //! CONfiguration MOb
#define DLC         (DLC0)                                               //! Data Length Coding

// Bit timing
#define BRP_MIN     1       //! Prescaler of FOSC (TQ generation)
#define BRP_MAX     64
#define NTQ_MIN     8       //! Number of TQ in one CAN bit
#define NTQ_MAX     25
                            //! True segment values in TQ
#define PRS_MIN     1       //! Propagation segment
#define PRS_MAX     8
#define PHS1_MIN    2       //! Phase segment 1
#define PHS1_MAX    8
#define PHS2_MIN    2       //! Phase segment 2
#define PHS2_MAX    8
#define SJW_MIN     1       //! Synchro jump width
#define SJW_MAX     4

#define NB_DATA_MAX  8
#define NO_MOB       0xFF

// Status macros
#define STATUS_CLEARED            0x00
    // ----------
#define MOB_NOT_COMPLETED         0x00                                              // 0x00
#define MOB_TX_COMPLETED        (1<<TXOK)                                           // 0x40
#define MOB_RX_COMPLETED        (1<<RXOK)                                           // 0x20
#define MOB_RX_COMPLETED_DLCW  ((1<<RXOK)|(1<<DLCW))                                // 0xA0
#define MOB_ACK_ERROR           (1<<AERR)                                           // 0x01
#define MOB_FORM_ERROR          (1<<FERR)                                           // 0x02
#define MOB_CRC_ERROR           (1<<CERR)                                           // 0x04
#define MOB_STUFF_ERROR         (1<<SERR)                                           // 0x08
#define MOB_BIT_ERROR           (1<<BERR)                                           // 0x10
#define MOB_PENDING            ((1<<RXOK)|(1<<TXOK))                                // 0x60
#define MOB_NOT_REACHED        ((1<<AERR)|(1<<FERR)|(1<<CERR)|(1<<SERR)|(1<<BERR))  // 0x1F
#define MOB_DISABLE               0xFF                                              // 0xFF
    // ----------
#define MOB_Tx_ENA  1
#define MOB_Rx_ENA  2
#define MOB_Rx_BENA 3
    // ----------
    
// Function macros
#define Can_reset()       ( CANGCON  =  (1<<SWRES) )
#define Can_enable()      ( CANGCON |=  (1<<ENASTB))
#define Can_disable()     ( CANGCON &= ~(1<<ENASTB))
    // ----------
#define Can_full_abort()  { CANGCON |=  (1<<ABRQ); CANGCON &= ~(1<<ABRQ); }
#define Can_conf_bt()     { CANBT1=CONF_CANBT1; CANBT2=CONF_CANBT2; CANBT3=CONF_CANBT3; }
    // ----------
#define Can_set_mob(mob)       { CANPAGE = ((mob) << 4);}
#define Can_set_mask_mob()     {  CANIDM4=0xFF; CANIDM3=0xFF; CANIDM2=0xFF; CANIDM1=0xFF; }
#define Can_clear_mask_mob()   {  CANIDM4=0x00; CANIDM3=0x00; CANIDM2=0x00; CANIDM1=0x00; }
#define Can_clear_status_mob() { CANSTMOB=0x00; }
#define Can_clear_mob()        { uint8_t  volatile *__i_; for (__i_=&CANSTMOB; __i_<&CANSTML; __i_++) { *__i_=0x00 ;}}
    // ----------
#define Can_mob_abort()   ( DISABLE_MOB )
    // ----------
#define Can_set_dlc(dlc)  ( CANCDMOB |= (dlc)        )
#define Can_set_ide()     ( CANCDMOB |= (1<<IDE)     )
#define Can_set_rtr()     ( CANIDT4  |= (1<<RTRTAG)  )
#define Can_set_rplv()    ( CANCDMOB |= (1<<RPLV)    )
    // ----------
#define Can_clear_dlc()   ( CANCDMOB &= ~DLC_MSK     )
#define Can_clear_ide()   ( CANCDMOB &= ~(1<<IDE)    )
#define Can_clear_rtr()   ( CANIDT4  &= ~(1<<RTRTAG) )
#define Can_clear_rplv()  ( CANCDMOB &= ~(1<<RPLV)   )
    // ----------
#define DISABLE_MOB       ( CANCDMOB &= (~CONMOB_MSK) )
#define Can_config_tx()        { DISABLE_MOB; CANCDMOB |= (MOB_Tx_ENA  << CONMOB); }
#define Can_config_rx()        { DISABLE_MOB; CANCDMOB |= (MOB_Rx_ENA  << CONMOB); }
#define Can_config_rx_buffer() {              CANCDMOB |= (MOB_Rx_BENA << CONMOB); }
    // ----------
#define Can_get_dlc()      ((CANCDMOB &  DLC_MSK)     >> DLC   )
#define Can_get_ide()      ((CANCDMOB &  (1<<IDE))    >> IDE   )
#define Can_get_rtr()      ((CANIDT4  &  (1<<RTRTAG)) >> RTRTAG)
    // ----------
#define Can_set_rtrmsk()   ( CANIDM4 |= (1<<RTRMSK) )
#define Can_set_idemsk()   ( CANIDM4 |= (1<<IDEMSK) )
    // ----------
#define Can_clear_rtrmsk() ( CANIDM4 &= ~(1<<RTRMSK) )
#define Can_clear_idemsk() ( CANIDM4 &= ~(1<<IDEMSK) )
    // ----------
                //!< STD ID TAG Reading
#define Can_get_std_id(identifier)  { *((uint8_t *)(&(identifier))+1) =  CANIDT1>>5              ; \
                                      *((uint8_t *)(&(identifier))  ) = (CANIDT2>>5)+(CANIDT1<<3); }
    // ----------
                //!< EXT ID TAG Reading
#define Can_get_ext_id(identifier)  { *((uint8_t *)(&(identifier))+3) =  CANIDT1>>3              ; \
                                      *((uint8_t *)(&(identifier))+2) = (CANIDT2>>3)+(CANIDT1<<5); \
                                      *((uint8_t *)(&(identifier))+1) = (CANIDT3>>3)+(CANIDT2<<5); \
                                      *((uint8_t *)(&(identifier))  ) = (CANIDT4>>3)+(CANIDT3<<5); }
    // ----------
                //!< STD ID Construction
#define CAN_SET_STD_ID_10_4(identifier)  (((*((uint8_t *)(&(identifier))+1))<<5)+((* (uint8_t *)(&(identifier)))>>3))
#define CAN_SET_STD_ID_3_0( identifier)  (( * (uint8_t *)(&(identifier))   )<<5)
    // ----------
                //!< STD ID TAG writing
#define Can_set_std_id(identifier)  { CANIDT1   = CAN_SET_STD_ID_10_4(identifier); \
                                      CANIDT2   = CAN_SET_STD_ID_3_0( identifier); \
                                      CANCDMOB &= (~(1<<IDE))                    ; }
    // ----------
                //!< STD ID MASK writing
#define Can_set_std_msk(mask)       { CANIDM1   = CAN_SET_STD_ID_10_4(mask); \
                                      CANIDM2   = CAN_SET_STD_ID_3_0( mask); }
    // ----------
                //!< EXT ID Construction
#define CAN_SET_EXT_ID_28_21(identifier)  (((*((uint8_t *)(&(identifier))+3))<<3)+((*((uint8_t *)(&(identifier))+2))>>5))
#define CAN_SET_EXT_ID_20_13(identifier)  (((*((uint8_t *)(&(identifier))+2))<<3)+((*((uint8_t *)(&(identifier))+1))>>5))
#define CAN_SET_EXT_ID_12_5( identifier)  (((*((uint8_t *)(&(identifier))+1))<<3)+((* (uint8_t *)(&(identifier))   )>>5))
#define CAN_SET_EXT_ID_4_0(  identifier)   ((* (uint8_t *)(&(identifier))   )<<3)
    // ----------
                //!< EXT ID TAG writing
#define Can_set_ext_id(identifier)  { CANIDT1   = CAN_SET_EXT_ID_28_21(identifier); \
                                      CANIDT2   = CAN_SET_EXT_ID_20_13(identifier); \
                                      CANIDT3   = CAN_SET_EXT_ID_12_5( identifier); \
                                      CANIDT4   = CAN_SET_EXT_ID_4_0(  identifier); \
                                      CANCDMOB |= (1<<IDE);                         }
    // ----------
                //!< EXT ID MASK writing
#define Can_set_ext_msk(mask)       { CANIDM1   = CAN_SET_EXT_ID_28_21(mask); \
                                      CANIDM2   = CAN_SET_EXT_ID_20_13(mask); \
                                      CANIDM3   = CAN_SET_EXT_ID_12_5( mask); \
                                      CANIDM4   = CAN_SET_EXT_ID_4_0(  mask); }


#endif /*__CAN_PLATFORM_H__*/

// ALL DONE.
