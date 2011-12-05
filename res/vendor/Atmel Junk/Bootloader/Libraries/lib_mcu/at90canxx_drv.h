//******************************************************************************
//! @file $RCSfile: at90canxx_drv.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file gives reference information about the intrinsic
//!        functions of AT90CANxx devices. These functions provide direct
//!        access to low-level processor operations.
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

#ifndef _AT90CANXX_DRV_H_
#define _AT90CANXX_DRV_H_

//_____ I N C L U D E S ____________________________________________________
#include <intrinsics.h>

//_____ D E F I N I T I O N S ______________________________________________
#define     SFR_BYTE_AT     *(U8 volatile*)

//_____ D E C L A R A T I O N S ____________________________________________

//_____ M A C R O S ________________________________________________________
#define     Sfr_rd_byte(addr_byte)               ( SFR_BYTE_AT(addr_byte) )


//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Enable_interrupt
//!
//! Set the Global Interrupt flag (I) in SREG (status register).
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//-----
//#define Enable_interrupt()      { asm ("sei") ; }
#define Enable_interrupt()      { __enable_interrupt(); }    //- Intrinsic function

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Disable_interrupt
//!
//! Clear the Global Interrupt flag (I) in SREG (status register).
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//-----
//#define Disable_interrupt()     { asm ("cli") ; }
#define Disable_interrupt()     { __disable_interrupt(); }    //- Intrinsic function

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Indirect_jump_to
//!
//! Jump within the lowest 64K words (128K bytes) section of Flash.
//!
//! @warning: WORD address as parameter
//!
//! @param: WORD address (PC <- Z(15:0))
//!
//! @return none
//-----
//#define Indirect_jump_to(jump_addr)  { GPIOR2=High(jump_addr);    \
                                       GPIOR1=Low (jump_addr);    \
                                       asm ("lds r31, 0x2B") ;    \
                                       asm ("lds r30, 0x2A") ;    \
                                       asm ("ijmp");              }

#define Indirect_jump_to(jump_addr)   { __indirect_jump_to(jump_addr); }    //- Intrinsic function

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Direct_jump_to_zero
//!
//! Jump at the addresse 0x0000 (not a reset !)
//!
//! @warning: not a reset!
//!
//! @param none
//!
//! @return none
//-----
#define Direct_jump_to_zero()   { asm ("jmp 0"); }

//#define  Direct_jump_to_zero()   { __indirect_jump_to(0); }     //- Intrinsic function

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Hard_reset
//!
//! RESET device with Watchdog Timer.
//!
//! @warning: Watchdog Timer used
//!           Check BOOTRST fuse setting
//!
//! @param none
//!
//! @return none
//-----
#define Hard_reset()    { WDTCR |= 1<<WDE;  while(1); }

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION WD_off
//!
//! Disable Watchdog Timer.
//!
//! @warning: Watchdog Timer used
//!
//! @param none
//!
//! @return none
//-----
#define WD_off()    { MCUSR &= ~(1<<WDRF); WDTCR = (1<<WDCE) | (1<<WDE); WDTCR = 0; }

//--------------------------------------------------------------------------
//  @fn MACRO-FUNCTION WD_reset
//!
//! RESET (update) Watchdog Timer when it is 'ON'.
//!
//! @warning: Watchdog Timer used
//!
//! @param none
//!
//! @return none
//-----
#define WD_reset()    { __watchdog_reset(); }    //- Intrinsic function equ. {asm("wrd");}


//**************************************************************************
#endif // _AT90CANXX_DRV_H_
