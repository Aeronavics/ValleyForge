/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file ******************************************************************
 *
 * \brief USB configuration file.
 *
 * This file contains the possible external configuration of the USB.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with a USB module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ***************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"
#include "board.h"
#include "print_funcs.h"
#include "usb_ids.h"


//! @defgroup usb_general_conf USB application configuration
//!
//! @{

  // _________________ USB MODE CONFIGURATION ____________________________
  //
  //! @defgroup USB_op_mode USB operating modes configuration
  //! Defines to enable device or host USB operating modes
  //! supported by the application
  //! @{

    //! @brief ENABLE to activate the host software framework support
    //!
    //! Possible values true or false
#define USB_HOST_FEATURE            false

    //! @brief ENABLE to activate the device software framework support
    //!
    //! Possible values true or false
#define USB_DEVICE_FEATURE          true

#if UC3A3
#    define USB_HIGH_SPEED_SUPPORT         true
#else
#    define USB_HIGH_SPEED_SUPPORT         false
#endif

  //! @}


  // _________________ DEVICE MODE CONFIGURATION __________________________
  //
  //! @defgroup USB_device_mode_cfg USB device operating mode configuration
  //!
  //! @{

#if USB_DEVICE_FEATURE == true

#define NB_ENDPOINTS          6 // Number of endpoints in the application including control endpoint
#define TX_EP                 1
#define RX_EP                 2
#define INT_EP                3
#define EP_MS_IN              4
#define EP_MS_OUT             5

    //! @defgroup device_cst_actions USB device custom actions
    //!
    //! @{
      // Write here the action to associate with each USB event.
      // Be careful not to waste time in order not to disturb the functions.
#define Usb_sof_action()                usb_sof_action()
#define Usb_wake_up_action()
#define Usb_resume_action()
#define Usb_suspend_action()
#define Usb_reset_action()
#define Usb_vbus_on_action()
#define Usb_vbus_off_action()
#define Usb_set_configuration_action()  Usb_enable_sof_interrupt()
    //! @}

#define SBC_VENDOR_ID                   "ATMEL   "          //  8 bytes only
#define SBC_PRODUCT_ID                  "UC3 MASS STORAGE"  // 16 bytes only
#define SBC_REVISION_ID                 "0.00"              //  4 bytes only

    //! @defgroup device_scsi_cst_actions USB device SCSI custom actions
    //!
    //! @{
      // Write here the action to associate with each SCSI command.
      // Be careful not to waste time in order not to disturb the functions.
#define Scsi_start_read_action()
#define Scsi_stop_read_action()
#define Scsi_start_write_action()
#define Scsi_stop_write_action()
    //! @}

extern void usb_sof_action(void);
extern void usb_suspend_action(void);

#endif  // USB_DEVICE_FEATURE == true

  //! @}


  //! USB interrupt priority level
#define USB_INT_LEVEL                   AVR32_INTC_INT0

  //! Debug trace macro
#define LOG_STR(str)                    //print_dbg(str)


//! @}


#endif  // _CONF_USB_H_
