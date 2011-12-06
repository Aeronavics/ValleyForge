//******************************************************************************
//! @file $RCSfile: eeprom_lib.c,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains all prototypes and macros to perform Eeprom
//!        access for AT90CAN128/64/32 nd ATmega16M1/32M1/32C1/64M1/64C1.
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

#ifndef _EEPROM_LIB_H_
#define _EEPROM_LIB_H_


//_____ I N C L U D E S ________________________________________________________

#include "config.h"
#include "eeprom_drv.h"

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn eeprom_rd_byte
//!
//! This function allows to read a byte in up to 64K bytes of Eeprom memory.
//!
//! @warning
//!
//! @param: addr_byte   Address to read the byte in Eeprom memory.
//!
//! @return:    Value read in the Eeprom memory.
extern U8 eeprom_rd_byte(U16 addr_byte);

//------------------------------------------------------------------------------
//  @fn eeprom_wr_byte
//!
//! This function allows to write a byte in up to 64K of Eeprom memory.
//!
//! @warning
//!
//! @param: addr_byte   Address in Eeprom memory to write the byte.
//!         value       Value to write in the Eeprom memory.
//!
//! @return none
extern void eeprom_wr_byte(U16 addr_byte, U8 value);

//------------------------------------------------------------------------------
//  @fn eeprom_rd_block
//!
//! This function allows to read up to 65535 bytes (64K Bytes-1 byte) of
//! the Eeprom memory.
//!
//! @warning: 1 - This function isn't able to address the fully 64K bytes
//!               but we cannot find in the device a source buffer up to
//!               64K bytes.
//!
//! @param: src    Start address in Eeprom memory where write data.
//!         *dest  Address of data to write.
//!         n      number of byte to write.
//!
//! @return none
extern void eeprom_rd_block(U16 src, U8* dest, U16 n);

//------------------------------------------------------------------------------
//  @fn eeprom_wr_block
//!
//! This function allows to write up to 65535 bytes (64K Bytes-1 byte) in
//! the Eeprom memory.
//!
//! @warning: 1 - This function isn't able to address the fully 64K bytes
//!               but we cannot find in the device a source buffer up to
//!               64K bytes.
//!
//! @param: *src   Address of data to write.
//!         dest   Start address in Eeprom memory where write data.
//!         n      number of byte to write.
//!
//! @return none
extern void eeprom_wr_block(U8* src, U16 dest, U16 n);

//------------------------------------------------------------------------------
//  @fn eeprom_full_erase
//!
//! This function erases the whole Eeprom memory.
//!
//! @warning none
//!
//! @param none
//!
//! @return none
extern void eeprom_full_erase(void);


//******************************************************************************

#endif  // _EEPROM_LIB_H_
