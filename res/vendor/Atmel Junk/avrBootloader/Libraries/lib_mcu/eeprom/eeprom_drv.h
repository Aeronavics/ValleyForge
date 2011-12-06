//******************************************************************************
//! @file $RCSfile: can_boot_drv.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level prototypes and macros for the
//!        Eeprom access for AT90CAN128/64/32 & ATmega16M1/32M1/32C1/64M1/64C1.
//!
//! This file has been validated with:
//!     - AVRStudio 4.15.623,
//!     - IAR C/C++ Compiler for AVR 5.20.1 (5.20.1.50092)
//!
//! @version $Revision: 3.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _EEPROM_DRV_H_
#define _EEPROM_DRV_H_

//_____ I N C L U D E S ________________________________________________________
#include <intrinsics.h>

//_____ D E F I N I T I O N S __________________________________________________
#define     _EEPROM_TYPE_    __eeprom

#define     EEPROM_BYTE_AT   *(U8 _EEPROM_TYPE_*)
#define      SRAM_BYTE_AT    *(U8*)

#define     EEPROM_BLANK_BYTE    0xFF

//_____ M A C R O S ____________________________________________________________

  //--- intrinsic Eeprom functions

  //--- Eeprom basic functions
#define     Eeprom_prog_completed       { while (EECR & (1<<EEWE)); }

  //--- Eeprom functions (c.f. intrinsic Eeprom functions)
#define     Eeprom_rd_byte(addr)        ( EEPROM_BYTE_AT(addr) )        //- "Eeprom_prog_completed" is done in intrinsics function
#define     Eeprom_wr_byte(addr, data)  ( EEPROM_BYTE_AT(addr) = data ) //- "Eeprom_prog_completed" is done in intrinsics function


//_____ D E C L A R A T I O N S ________________________________________________


//******************************************************************************

#endif // _EEPROM_DRV_H_

