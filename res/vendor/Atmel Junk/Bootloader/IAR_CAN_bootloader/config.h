//******************************************************************************
//! @file $RCSfile: config.h,v $
//!
//! Copyright (c) 2009 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief Configuration file for the following project:
//!             - iar_can_bootloader
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

//_____ I N C L U D E S ________________________________________________________
#ifndef  ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif

#include <ioavr.h>
#include "iar_compiler.h"

#if   defined(__AT90CAN128__) || \
      defined(__AT90CAN64__)  || \
      defined(__AT90CAN32__)
#   include "at90canxx_drv.h"
    // First board option:
#   include "dvk90can1_board.h"
    // Second board option:
//#   include "stk600_at90canxx_board.h"
#elif defined(__ATmega16M1__) || \
      defined(__ATmega32M1__) || \
      defined(__ATmega32C1__) || \
      defined(__ATmega64M1__) || \
      defined(__ATmega64C1__)
#   include "atmegaxxm1c1_drv.h"
    // First board option:
//#   include "stk524_board.h"
    // Second board option:
//#   include "stk600_atmegaxxm1c1_board.h"
    // Third board option:
#   include "mc310_board.h"
#else
#   error Wrong device selection in IAR Embedded Workbench IDE "Project->Options ...->General Options->Target"
#endif

//_____ D E F I N I T I O N S __________________________________________________

//---------------- BOOT LOADER DEFINITION --------------------------------------
#define     BOOT_LOADER_SIZE            0x1000  // Size in bytes: 4KB
#define     MAX_FLASH_SIZE_TO_ERASE     ( FLASH_SIZE - ((U32)(BOOT_LOADER_SIZE)) )

//---------------- PROCESSOR DEFINITION ----------------------------------------

#define     XRAM_END            XRAMEND     // Defined in "ioxxx.h"
#define     RAM_END             RAMEND      // Defined in "ioxxx.h"
#define     E2_END              E2END       // Defined in "ioxxx.h"
#define     FLASH_END           FLASHEND    // Defined in bytes in "ioxxx.h"
#define     FLASH_SIZE          ((U32)(FLASH_END)) + 1 // Size in bytes

// Switches for specific definitions & switches
// Some specific definitions are defined across "ioavr.h" i.e.e FLASHEND, E2END ...
#if   defined(__AT90CAN128__)               // __HAS_ELPM__ defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x81        // AT90CANxxx family
#   define  PRODUCT_NAME        0x97        // 128 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     256         // Size in bytes, constant for AT90CANxx devices
#   define  _BOOT_CONF_TYPE_    __farflash  // Bootloader mapped above 64K
#   define  _RAMPZ_IS_USED_                 // RAMPZ register used if Flash memory used is upper than 64K bytes


#elif defined(__AT90CAN64__)                // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x81        // AT90CANxxx family
#   define  PRODUCT_NAME        0x96        // 64 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     256         // Size in bytes, constant for AT90CANxx devices
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K


#elif defined(__AT90CAN32__)                // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x81        // AT90CANxxx family
#   define  PRODUCT_NAME        0x95        // 32 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     256         // Size in bytes, constant for AT90CANxx devices
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#elif defined(__ATmega16M1__)               // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x84        // ATmegaxxM1C1 family
#   define  PRODUCT_NAME        0x94        // 16 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     128         // Size in bytes
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#elif defined(__ATmega32M1__)               // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x84        // ATmegaxxM1C1 family
#   define  PRODUCT_NAME        0x95        // 32 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     128         // Size in bytes
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#elif defined(__ATmega32C1__)                // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x86        // ATmegaxxM1C1 family
#   define  PRODUCT_NAME        0x95        // 32 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     128         // Size in bytes
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#elif defined(__ATmega64M1__)               // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x84        // AATmegaxxM1C1 family
#   define  PRODUCT_NAME        0x96        // 64 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     256         // Size in bytes
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#elif defined(__ATmega64C1__)               // __HAS_ELPM__ not-defined by IAR device selection
#   define  MANUF_ID            0x1E        // ATMEL
#   define  FAMILY_CODE         0x86        // ATmegaxxM1C1 family
#   define  PRODUCT_NAME        0x96        // 64 Kbytes of Flash
#   define  PRODUCT_REV         0x00        // Rev 0
#   define  FLASH_PAGE_SIZE     256         // Size in bytes
#   define  _BOOT_CONF_TYPE_    __flash     // Bootloader mapped below 64K

#else
#   error Wrong device selection in IAR Embedded Workbench IDE "Project->Options ...->General Options->Target"
#endif

#define     FOSC                8000

//---------------- CAN DEFINITION ----------------------------------------------
//#define   CAN_BAUDRATE        500         // Baudrate in kBit
#define     CAN_BAUDRATE        CAN_AUTOBAUD

//******************************************************************************

#endif  // _CONFIG_H_

