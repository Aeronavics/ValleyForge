//******************************************************************************
//! @file $RCSfile: stk600_atmegaxxm1c1_board.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief Targetted board (STK600) include file found in "config.h".
//!
//! The used devices belong to ATmegaxxM1C1 family.
//! This file mainly reflects the switch configuration of the board
//! - For LEDs: Define PORT for LEDS
//! - For Keyboard: Define PORT for KEYs.
//!
//! This file has been validated with:
//!     - AVRStudio 4.15.623,
//!     - IAR C/C++ Compiler for AVR 5.11B/W32 (5.11.2.5)
//!
//! @version $Revision: 3.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _STK600_ATMEGAXXM1C1_BOARD_H_
#define _STK600_ATMEGAXXM1C1_BOARD_H_

//_____ I N C L U D E S ________________________________________________________

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//! Define PORT for LEDs in STK600.
#define LED_PORT_IN     PINB
#define LED_PORT_DIR    DDRB
#define LED_PORT_OUT   PORTB

//! Define PORT for KEYs in STK600.
#define KEY_PORT_IN      PIND
#define KEY_PORT_DIR     DDRD
#define KEY_PORT_OUT    PORTD

//! Hardware condition (for boot or application start)
//!--- HWCB = PD.0 on STK600 board - active low with pullup
#define HWCB_PORT_IN        PIND
#define HWCB_PORT_DIR       DDRD
#define HWCB_PORT_OUT      PORTD
#define HWCB_INPUT_PIN         0
#define HWCB_ACTIVE_LEVEL      0  // Active low = "0"
#define HWCB_PULLUP_ON         1  // With pullup ="1"

//_____ D E C L A R A T I O N S ________________________________________________

//_____ P R O T O T Y P E S ____________________________________________________

//******************************************************************************

#endif  // _STK600_ATMEGAXXM1C1_BOARD_H_



