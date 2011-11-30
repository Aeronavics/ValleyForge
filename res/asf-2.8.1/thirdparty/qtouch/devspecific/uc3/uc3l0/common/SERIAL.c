/* This source file is part of the ATMEL QTouch Library Release 4.3.1 */
/* This file is prepared for Doxygen automatic documentation generation. */
/*! \file *********************************************************************
 *
 * \brief  This file contains the Serial interface API used by QDebug component
 * to transfer data over USART Serial interface.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  AT32UC3L0.
 * - Userguide:          QTouch Library User Guide - doc8207.pdf.
 * - Support email:      touch@atmel.com
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

/* Copyright (c) 2010 Atmel Corporation. All rights reserved.
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

/*============================ INCLUDES ======================================*/
#include "SERIAL.h"
#include "pdca.h"
#include "usart.h"
#include "gpio.h"
#include "cycle_counter.h"

#if defined(__GNUC__)
#include "intc.h"
#endif

#include "QDebugSettings.h"
#include "QDebugTransport.h"

/*============================ GLOBAL VARIABLES ==============================*/
char SERIAL_RX_Buffer[RX_BUFFER_SIZE];
volatile unsigned int SERIAL_RX_index;
volatile bool MessageReady = false;
volatile int rx_size = RX_BUFFER_SIZE;

/*! \brief Serial Data Interrupt Handler.
 */
ISR(int_usart_handler, QDEBUG_SERIAL_USART_IRQ_GROUP, 1)
{
  unsigned char c;


  if (QDEBUG_SERIAL_USART->csr & AVR32_USART_RXRDY_MASK)
    {
      c =
	(QDEBUG_SERIAL_USART->
	 rhr & AVR32_USART_RHR_RXCHR_MASK) >> AVR32_USART_RHR_RXCHR_OFFSET;
      if (MessageReady == true)
	{
	  //Do not update message will old message has not been read
	  return;
	}

      SERIAL_RX_Buffer[SERIAL_RX_index++] = c;
      // resyn until we get MESSAGE_START
      if (SERIAL_RX_Buffer[0] != MESSAGE_START)
	{
	  SERIAL_RX_index = 0;
	}

      if (SERIAL_RX_index == 3u)
	{
	  rx_size = ((SERIAL_RX_Buffer[1] << 8) | SERIAL_RX_Buffer[2]);
	}

      // If SERIAL_RX_index==3 run PDCA to received rest of the message
      if (SERIAL_RX_index == 3u)
	{
	  // Disable RXRDY interrupt before switch to PDCA MODE
	  QDEBUG_SERIAL_USART->idr = AVR32_USART_IDR_RXRDY_MASK;
	  rx_size = ((SERIAL_RX_Buffer[1] << 8) | SERIAL_RX_Buffer[2]);
	  pdca_load_channel (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART,
			     (void *) &(SERIAL_RX_Buffer[3]), rx_size - 2);
	  pdca_enable (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART);
	  pdca_enable_interrupt_transfer_complete (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART);
	}

      if (SERIAL_RX_index > 3)
	{
	  // Must not occurred, require a synchro
	  SERIAL_RX_index = 0;
	}
    }
}

/*! \brief Serial PDCA Interrupt Handler.
 */
ISR(int_pdca_handler, QDEBUG_SERIAL_PDCA_IRQ_GROUP, 1)
{
  if ((pdca_get_transfer_status (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART) & AVR32_PDCA_TRC_MASK)
      != 0)
    {
      // Message has been fully received, can enable again RXRDY interrupt
      pdca_disable_interrupt_transfer_complete (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART);
      QDEBUG_SERIAL_USART->ier = AVR32_USART_IER_RXRDY_MASK;
      SERIAL_RX_index =
	((SERIAL_RX_Buffer[1] << 8) | SERIAL_RX_Buffer[2]) + 1;
      MessageReady = true;
    }
}

/*! \brief Initialize the Serial interface.
 */
void
SERIAL_Init (void)
{

  SERIAL_RX_index = 0;
  SERIAL_RX_Buffer[0] = 0;
  
  #if defined(AVR32_HMATRIX)
  // HSB Bus matrix register MCFG1 is associated with the CPU instruction master interface.
  AVR32_HMATRIX.mcfg[AVR32_HMATRIX_MASTER_CPU_INSN] = 0x1;  
  #elif defined(AVR32_HMATRIXB)
  // HSB Bus matrix register MCFG1 is associated with the CPU instruction master interface.
  AVR32_HMATRIXB.mcfg[AVR32_HMATRIXB_MASTER_CPU_INSN] = 0x1;
  #endif

  // Usart PIN definition
  static const gpio_map_t USART_GPIO_MAP = {
    {QDEBUG_SERIAL_USART_RX_PIN, QDEBUG_SERIAL_USART_RX_FUNCTION},
    {QDEBUG_SERIAL_USART_TX_PIN, QDEBUG_SERIAL_USART_TX_FUNCTION}
  };

  // USART options.
  static const usart_options_t USART_OPTIONS = {
    .baudrate = QDEBUG_SERIAL_BAUD_RATE,
    .charlength = 8,
    .paritytype = USART_NO_PARITY,
    .stopbits = USART_1_STOPBIT,
    .channelmode = USART_NORMAL_CHMODE,
  };

  // Assign GPIO pins to USART_0.
  gpio_enable_module (USART_GPIO_MAP,
		      sizeof (USART_GPIO_MAP) / sizeof (USART_GPIO_MAP[0]));

  // Initialize the USART in RS232 mode.
  usart_init_rs232 (QDEBUG_SERIAL_USART, &USART_OPTIONS, QDEBUG_PBA_FREQ_HZ);


  // PDCA channel TX options
  static const pdca_channel_options_t PDCA_TX_OPTIONS = {
    .addr = (void *) TX_Buffer,	// memory address
    .pid = QDEBUG_SERIAL_PDCA_PID_USART_TX,	// select peripheral - data are transmit on USART TX line.
    .size = 0,			// transfer counter
    .r_addr = NULL,		// next memory address
    .r_size = 0,		// next transfer counter
    .transfer_size = PDCA_TRANSFER_SIZE_BYTE	// select size of the transfer
  };

  // PDCA channel RX options
  static const pdca_channel_options_t PDCA_RX_OPTIONS = {
    .addr = (void *) RX_Buffer,	// memory address
    .pid = QDEBUG_SERIAL_PDCA_PID_USART_RX,	// select peripheral - data are transmit on USART RX line.
    .size = 0,			// transfer counter
    .r_addr = NULL,		// next memory address
    .r_size = 0,		// next transfer counter
    .transfer_size = PDCA_TRANSFER_SIZE_BYTE	// select size of the transfer
  };

  // init PDCA channel with options.
  pdca_init_channel (QDEBUG_SERIAL_PDCA_CHANNEL_TX_USART, &PDCA_TX_OPTIONS);
  pdca_init_channel (QDEBUG_SERIAL_PDCA_CHANNEL_RX_USART, &PDCA_RX_OPTIONS);

  // Register the USART interrupt handler to the interrupt controller.
  // Highest priority is required for the USART, since we do not want to loose
  // any characters.
  Disable_global_interrupt ();

#if (defined __GNUC__)
  INTC_register_interrupt (&int_usart_handler, QDEBUG_SERIAL_USART_IRQ, AVR32_INTC_INT3);
  INTC_register_interrupt (&int_pdca_handler, QDEBUG_SERIAL_PDCA_IRQ, AVR32_INTC_INT0);
#endif

  QDEBUG_SERIAL_USART->ier = AVR32_USART_IER_RXRDY_MASK;
  Enable_global_interrupt ();
}

/*! \brief Send message to remote target over the Serial interface.
 */
void
SERIAL_Send_Message (void)
{
  pdca_load_channel (QDEBUG_SERIAL_PDCA_CHANNEL_TX_USART, (void *) (&TX_Buffer[0]),
		     (TX_index + 1));
  pdca_enable (QDEBUG_SERIAL_PDCA_CHANNEL_TX_USART);

  // Wait for message to be sent
  while ((pdca_get_transfer_status (QDEBUG_SERIAL_PDCA_CHANNEL_TX_USART) &
	  PDCA_TRANSFER_COMPLETE) == 0)
    {
      // Wait 1ms Before read again pdca transfer status
      cpu_delay_ms (1, QDEBUG_CPU_FREQ_HZ);
    }
}

/*! \brief Retrieve message from remote target over the Serial interface.
 */
void
SERIAL_Retrieve_Message (void)
{
  int i;
  if (MessageReady == true)
    {
      for (i = 0; i < SERIAL_RX_index; i++)
	{
	  RX_Buffer[i] = SERIAL_RX_Buffer[i];
	}
      SERIAL_RX_index = 0;
      MessageReady = false;
    }
  else
    {
      RX_Buffer[0] = 0;
    }
}
