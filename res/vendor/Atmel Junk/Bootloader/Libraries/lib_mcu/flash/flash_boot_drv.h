//******************************************************************************
//! @file $RCSfile: flash_boot_drv.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level prototypes and macros for the
//!        Flash access for AT90CAN128/64/32 parts.
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

#ifndef _FLASH_BOOT_DRV_H_
#define _FLASH_BOOT_DRV_H_

//_____ I N C L U D E S ________________________________________________________
#include <intrinsics.h>

//_____ D E F I N I T I O N S __________________________________________________
#define     _FLASH_TYPE_        __flash
#define     _FARFLASH_TYPE_     __farflash

#define     FLASH_BYTE_AT       *(U8 _FLASH_TYPE_*)
#define     FARFLASH_BYTE_AT    *(U8 _FARFLASH_TYPE_*)
#define     FLASH_WORD_AT       *(U16 _FLASH_TYPE_*)
#define     FARFLASH_WORD_AT    *(U16 _FARFLASH_TYPE_*)
#define     SRAM_BYTE_AT        *(U8*)

#define     FLASH_BLANK_WORD    0xFFFF

//_____ M A C R O S ____________________________________________________________

//--- intrinsic Flash functions
#define     Flash_fill_temp_buffer(addr, data_w)  { _SPM_FILLTEMP((void _FLASH_TYPE_*) addr, data_w); }
#define     Flash_page_write(page_addr)           { _SPM_PAGEWRITE((void _FLASH_TYPE_*) page_addr)  ; }
#define     Flash_page_erase(page_addr)           { _SPM_ERASE((void _FLASH_TYPE_*) page_addr)      ; }

  //--- other Flash functions
#define     Stdflash_rd_byte(addr_byte)           ( FLASH_BYTE_AT(addr_byte) )
#define     Stdflash_rd_word(addr_word)           ( FLASH_WORD_AT(addr_word) )
#define     Farflash_rd_byte(addr_byte)           ( FARFLASH_BYTE_AT(addr_byte) )
#define     Farflash_rd_word(addr_word)           ( FARFLASH_WORD_AT(addr_word) )

#define     Flash_rww_section_enable              { __DataToR0ByteToSPMCR_SPM(0x00, 0x11) ; }
#define     Flash_prog_completed                  { while (SPMCSR & (1<<SPMEN)); }


//--- Sram functions
#define     Sram_rd_byte(addr_byte)               ( SRAM_BYTE_AT(addr_byte) )

//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_fill_temp_buffer
//!
//! This function allows to load a word in the temporary Flash buffer..
//!
//! @warning none
//!
//! @param: addr    Address in Flash memory to write the 16-bit word.
//!         word    Word value to write in the Flash memory.
//!
//! @return none
extern  void flash_fill_temp_buffer(U16 addr, U16 word);

//------------------------------------------------------------------------------
//  @fn flash_page_write
//!
//! This function allows to write a Flash page with the temporary Flash
//! buffer content.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to write (program).
//!
//! @return none
extern  void flash_page_write(U16 page_addr);

//------------------------------------------------------------------------------
//  @fn flash_page_erase
//!
//! This function allows to erase a Flash page.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to erase.
//!
//! @return none
extern void flash_page_erase(U16 page_addr);


//******************************************************************************

#endif // _FLASH_BOOT_DRV_H_

