//******************************************************************************
//! @file $RCSfile: dvk90can1_board.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief Targetted board (DVK90CAN1) include file found in "config.h".
//!
//! The used devices belong to AT90CANxxx family.
//! This file mainly reflects the switch configuration of the board
//! - For LEDs: Define the full uC PORT linked to 8-bit of LEDS
//! - For Keyboard: Define PORT and bits for compass card KEYs.
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

#ifndef _DVK90CAN1_BOARD_H_
#define _DVK90CAN1_BOARD_H_

//_____ I N C L U D E S ________________________________________________________

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//! Define PORT for LEDs in DVK90CAN1.
#define LED_PORT_IN     PINA
#define LED_PORT_DIR    DDRA
#define LED_PORT_OUT   PORTA

//! Define PORT and bits for KEYs in DVK90CAN1.
//!
//! Case1:
//!    Bit   |  7 6 5 4  3 2 1 0
//!    ------+-------------------
//!    PORTE |  S W E N    C
//!    ------+-------------------
//!
//! Case2:
//!    Bit   |  7 6 5 4  3 2 1 0        Bit   |  7 6 5 4  3 2 1 0
//!    ------+-------------------  and  ------+-------------------
//!    PORTE |  S W E N                 PORTD |               C
//!    ------+-------------------       ------+-------------------
#define KEY_PORT_IN      PINE
#define KEY_PORT_DIR     DDRE
#define KEY_PORT_OUT    PORTE
#define KEY_NORTH           4
#define KEY_SOUTH           7
#define KEY_WEST            6
#define KEY_EAST            5
#define KEY_CENTER          2    // Configure the board with the appropriated
                                 // setting (J29)

// If case2, enable the following definitions
//#define KEY_CENTER_PORT_IN  PIND
//#define KEY_CENTER_PORT_DIR DDRD
//#define KEY_CENTER_PORT_OUT PORTD
//#define KEY_CENTER_IN   1       // PORTD.1

//! Hardware condition (for boot or application start)
//!--- HWCB = INT on DVK90CAN1 board = INT0 or PD.0 - active low with pullup
#define HWCB_PORT_IN        PIND
#define HWCB_PORT_DIR       DDRD
#define HWCB_PORT_OUT      PORTD
#define HWCB_INPUT_PIN         0
#define HWCB_ACTIVE_LEVEL      0  // Active low = "0"
#define HWCB_PULLUP_ON         1  // With pullup ="1"
//!--- HWCB = Center Key on DVK90CAN1 board = PE.2 active low with pullup
//#define HWCB_PORT_IN        PINE
//#define HWCB_PORT_DIR       DDRE
//#define HWCB_PORT_OUT      PORTE
//#define HWCB_INPUT_PIN         2
//#define HWCB_ACTIVE_LEVEL      0  // Active low = "0"
//#define HWCB_PULLUP_ON         1  // With pullup ="1"

//_____ D E C L A R A T I O N S ________________________________________________

//_____ P R O T O T Y P E S ____________________________________________________

//******************************************************************************

#endif  // _DVK90CAN1_BOARD_H_



