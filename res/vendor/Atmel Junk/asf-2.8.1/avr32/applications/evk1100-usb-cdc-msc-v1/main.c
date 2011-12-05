/*This file is prepared for Doxygen automatic documentation generation.*/
/**
 * \file
 *
 * \brief Main file of the USB CDC example.
 *
 * Copyright (C) 2009 - 2011 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/*! \mainpage AVR UC3 USB software framework for CDC (using USB stack from ASF v1)
 *
 * This manual is divided into the following sections:
 * - \ref desc "Description of the Communication Device Class (CDC) USB class"
 * - \ref sample "About the Sample Application"
 * - \ref device_use "Using the USB Device Mode"
 * - \ref host_use "Using the USB Host Mode"
 * - \ref arch "Firmware Architecture"
 * - \ref files "Main Files used by the demo"
 *
 * \section desc Description of the Communication Device Class (CDC) USB class
 * The Communication Device Class (CDC) is a general-purpose way to enable all
 * types of communications on the Universal Serial Bus (USB). This class makes it possible
 * to connect telecommunication devices such as digital telephones or analog
 * modems, as well as networking devices like ADSL or Cable modems.
 * While a CDC device enables the implementation of quite complex devices, it can also
 * be used as a very simple method for communication on the USB. For example, a CDC
 * device can appear as a virtual COM port, which greatly simplifies application programming
 * on the host side.
 *
 * \section sample About the Sample Application
 * This embedded application source code illustrates how to implement a USB CDC application
 * on the AVR32 microcontroller.
 *
 * As the AVR32 implements a device/host USB controller, the embedded application can operate
 * in one of the following USB operating modes:
 *   - USB device;
 *   - USB reduced-host controller;
 *   - USB dual-role device (depending on the ID pin).
 *
 * To optimize embedded code/RAM size and reduce the number of source modules, the application can be
 * configured to use one and only one of these operating modes.
 *
 * \page device_use Using the USB Device Mode
 *
 * The DEVICE source code illustrates how to implement on the AVR32 microcontroller
 * a Serial to USB application.
 *
 * \image html appli.jpg "Serial to USB application architecture"
 *
 * \section install Installation
 *
 * For our example, we will only use a PC for the demonstration: it will both connect to the USB and to the
 * COM port of the EVK110x boards.
 *
 * Connect the USART peripheral to the USART connector of the EVK110x board.
 * Connect the application to a USB host (e.g. a PC) with a mini-B (embedded side) to A (PC host side) cable.
 * The application will behave as a virtual COM.
 * \image html appli_evk1100_device.jpg "EVK1100 USB Device Mode"
 * \image html appli_evk1101_device.jpg "EVK1101 USB Device Mode"
 * For the first connection of the EVK110x board on the PC,
 * the operating system will detect a new peripheral. This will open a new hardware installation window.
 * Choose "No, not this time" to connect to Windows Update for this installation and click `Next':
 *
 * \image html install_1.jpg "Found New Hardware Wizard"
 *
 * On the next screen, select "Install from a list or specific location (Advanced)" and click `Next'.
 * Then request to search in the DRIVER folder of the "CDC EXAMPLES"
 * directory as shown below and click `Next'
 *
 * \image html install_3.jpg "location"
 *
 * A warning message "The software [...]
 * has not passed Windows Logo testing..." will appear. Click on "Continue Anyway":
 *
 * \image html install_4.jpg "Warning"
 *
 * Windows will then process the installation of the driver. Once completed, click `Finish'.
 *
 * \image html install_5.jpg "Installation done"
 *
 * For our example, we will use 2 serial terminals (e.g. HyperTerminal under
 * Windows systems or minicom under Linux systems; USART settings: 57600 bauds, 8-bit data, no parity bit,
 * 1 stop bit, no flow control):
 *  - One on the virtual COM, known as "AT32UC3xxx CDC USB to USART" (known as "Virtual Serial Term" in this document).
 * You will find the virtual COM number in the Windows Device Manager, as shown hereafter (in this example,
 * the virtual COM port number is COM6):
 *
 * \image html usb_cdc_device_manager.jpg "Installation done"
 *
 *  - One on the COM on which the EVK110x serial output has been connected to (known as "Serial Term" in this document).
 *
 * Open the 2 terminals using the same baudrates.
 *  - Any characters typed on the "Virtual Serial COM" terminal will be transferred from USB through USART and thus be dispayed on the "Serial Term"
 *  - Any characters typed on the "Serial COM" terminal will be transferred from USART through USB and then be dispayed on the "Virtual Serial Term"
 *
 * Note that the serial parameters (baud rate, stop bits, etc...) of the "Virtual Serial Term" are automatically
 * applied on the "Serial COM" USART.
 *
 * \page host_use Using the USB Host Mode
 *
 * This embedded application source code illustrates how to implement a simple USB host application with CDC support.
 * In the host mode, the USB can be connected (with a mini A connector attached to the mini AB EVK110x receptacle)
 * to a standard CDC device (or another EVK110x running device CDC application).
 * The controller will initialize and enumerate a device CDC application.
 *
 * In our example, we will connect 2 EVK110x boards together using the USB: one will act as a host, the second
 * one will operate as a device.
 * Connect the USART output of each board to the COM ports of a PC (e.g. HyperTerminal under
 * Windows systems or minicom under Linux systems; USART settings: 57600 bauds, 8-bit data, no parity bit,
 * 1 stop bit, no flow control).
 *
 * \image html appli_host.jpg
 *
 * Open the 2 terminals using the same baudrates.
 *  - Any characters typed on the "Serial COM x" terminal will be transferred through USART and then be dispayed on the "Serial COM y"
 *  - Any characters typed on the "Serial COM y" terminal will be transferred through USART and then be dispayed on the "Serial COM x"
 *
 * The following picture shows the architecture of the host application:
 * \image html appli_host.gif
 *
 * \page arch Architecture
 * As illustrated in the figure bellow, the application entry point is located is the cdc_example.c file.
 * The application can be ran using the FreeRTOS operating system, or in standalone mode.
 * In the standalone mode, the main function runs the usb_task, the device_cdc_task and host_cdc_task tasks in an infinite loop.
 *
 * The application is based on three different tasks:
 * - The usb_task  (usb_task.c associated source file), is the task performing the USB low level
 * enumeration process in device mode.
 * Once this task has detected that the usb connection is fully operationnal, it updates different status flags
 * that can be checked within the high level application tasks.
 * - The device_cdc_task task performs the high level device application operation.
 * Once the device is fully enumerated (DEVICE SET_CONFIGURATION request received), the task will transform
 * the product as a virtual COM port: any bytes received from the USB will be redirected to the USART and vice versa.
 * - The host_cdc_task task performs the high level host application operation.
 * Once a device is connected and fully enumerated, the task will also transform the product as a virtual COM port.
 * You can for example connect an other EVK110x board itself in the device role.
 *
 * \image html arch_full.jpg "Architecture Overview"
 *
 * \page files Main Files
 * - device_cdc_task.c : high level device CDC application operation
 * - device_cdc_task.h : high level device CDC application operation header
 * - host_cdc_task.c : high level host CDC application operation
 * - host_cdc_task.h : high level host CDC application operation header
 * - uart_usb_lib.c : controls the USART USB functions.
 * - uart_usb_lib.h : USART USB functions header.
 * - cdc_example.c : CDC code example
 */

//_____  I N C L U D E S ___________________________________________________

#include "compiler.h"
#include "board.h"
#include "print_funcs.h"
#include "intc.h"
#include "power_clocks_lib.h"
#include "main.h"
#include "gpio.h"
#include "ctrl_access.h"
#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)
  #include "spi.h"
  #include "conf_at45dbx.h"
#endif
#if (defined SD_MMC_SPI_MEM) && (SD_MMC_SPI_MEM == ENABLE)
  #include "spi.h"
  #include "conf_sd_mmc_spi.h"
#endif
#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) || ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))
  #include "mci.h"
  #include "conf_sd_mmc_mci.h"
#endif
#include "conf_usb.h"
#include "usb_task.h"
#if USB_DEVICE_FEATURE == true
#include "device_cdc_task.h"
#include "device_mass_storage_task.h"
#endif
#include <stdio.h>


//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________

/*! \name System Clock Frequencies
 */
//! @{
pcl_freq_param_t pcl_freq_param =
{
	.cpu_f        = APPLI_CPU_SPEED,
	.pba_f        = APPLI_PBA_SPEED,
	.osc0_f       = FOSC0,
	.osc0_startup = OSC0_STARTUP
};
//! @}

/*! \name Hmatrix bus configuration
 */
void init_hmatrix(void)
{
	union
	{
		unsigned long                 scfg;
		avr32_hmatrix_scfg_t          SCFG;
	} u_avr32_hmatrix_scfg;

	// For the internal-flash HMATRIX slave, use last master as default.
	u_avr32_hmatrix_scfg.scfg = AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH];
	u_avr32_hmatrix_scfg.SCFG.defmstr_type = AVR32_HMATRIX_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH] = u_avr32_hmatrix_scfg.scfg;
}



#ifndef FREERTOS_USED

	#if (defined __GNUC__)

/*! \brief Low-level initialization routine called during startup, before the
 *         main function.
 *
 * This version comes in replacement to the default one provided by the Newlib
 * add-ons library.
 * Newlib add-ons' _init_startup only calls init_exceptions, but Newlib add-ons'
 * exception and interrupt vectors are defined in the same section and Newlib
 * add-ons' interrupt vectors are not compatible with the interrupt management
 * of the INTC module.
 * More low-level initializations are besides added here.
 */
int _init_startup(void)
{
	// Import the Exception Vector Base Address.
	extern void _evba;

	// Load the Exception Vector Base Address in the corresponding system register.
	Set_system_register(AVR32_EVBA, (int)&_evba);

	// Enable exceptions.
	Enable_global_exception();

	// Initialize interrupt handling.
	INTC_init_interrupts();

	// Don't-care value for GCC.
	return 1;
}

	#elif __ICCAVR32__

/*! \brief Low-level initialization routine called during startup, before the
 *         main function.
 */
int __low_level_init(void)
{
	// Enable exceptions.
	Enable_global_exception();

	// Initialize interrupt handling.
	INTC_init_interrupts();

	// Request initialization of data segments.
	return 1;
}

	#endif  // Compiler

#endif  // FREERTOS_USED



#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)

/*! \brief Initializes AT45DBX resources: GPIO, SPI and AT45DBX.
 */
static void at45dbx_resources_init(void)
{
	static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
	{
		{AT45DBX_SPI_SCK_PIN,          AT45DBX_SPI_SCK_FUNCTION         },  // SPI Clock.
		{AT45DBX_SPI_MISO_PIN,         AT45DBX_SPI_MISO_FUNCTION        },  // MISO.
		{AT45DBX_SPI_MOSI_PIN,         AT45DBX_SPI_MOSI_FUNCTION        },  // MOSI.
#define AT45DBX_ENABLE_NPCS_PIN(NPCS, unused) \
		{AT45DBX_SPI_NPCS##NPCS##_PIN, AT45DBX_SPI_NPCS##NPCS##_FUNCTION},  // Chip Select NPCS.
		MREPEAT(AT45DBX_MEM_CNT, AT45DBX_ENABLE_NPCS_PIN, ~)
#undef AT45DBX_ENABLE_NPCS_PIN
	};

	// SPI options.
	spi_options_t spiOptions =
	{
		.reg          = AT45DBX_SPI_FIRST_NPCS,   // Defined in conf_at45dbx.h.
		.baudrate     = AT45DBX_SPI_MASTER_SPEED, // Defined in conf_at45dbx.h.
		.bits         = AT45DBX_SPI_BITS,         // Defined in conf_at45dbx.h.
		.spck_delay   = 0,
		.trans_delay  = 0,
		.stay_act     = 1,
		.spi_mode     = 0,
		.modfdis      = 1
	};

	// Assign I/Os to SPI.
	gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
				sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));

	// If the SPI used by the AT45DBX is not enabled.
	if (!spi_is_enabled(AT45DBX_SPI)) {
		// Initialize as master.
		spi_initMaster(AT45DBX_SPI, &spiOptions);

		// Set selection mode: variable_ps, pcs_decode, delay.
		spi_selectionMode(AT45DBX_SPI, 0, 0, 0);

		// Enable SPI.
		spi_enable(AT45DBX_SPI);
	}

	// Initialize data flash with SPI PB clock.
	at45dbx_init(spiOptions, pcl_freq_param.pba_f);
}

#endif  // AT45DBX_MEM == ENABLE


#if (defined SD_MMC_SPI_MEM) && (SD_MMC_SPI_MEM == ENABLE)

/*! \brief Initializes SD/MMC resources: GPIO, SPI and SD/MMC.
 */
static void sd_mmc_spi_resources_init(void)
{
	static const gpio_map_t SD_MMC_SPI_GPIO_MAP =
	{
		{SD_MMC_SPI_SCK_PIN,  SD_MMC_SPI_SCK_FUNCTION },  // SPI Clock.
		{SD_MMC_SPI_MISO_PIN, SD_MMC_SPI_MISO_FUNCTION},  // MISO.
		{SD_MMC_SPI_MOSI_PIN, SD_MMC_SPI_MOSI_FUNCTION},  // MOSI.
		{SD_MMC_SPI_NPCS_PIN, SD_MMC_SPI_NPCS_FUNCTION}   // Chip Select NPCS.
	};

	// SPI options.
	spi_options_t spiOptions =
	{
		.reg          = SD_MMC_SPI_NPCS,
		.baudrate     = SD_MMC_SPI_MASTER_SPEED,  // Defined in conf_sd_mmc_spi.h.
		.bits         = SD_MMC_SPI_BITS,          // Defined in conf_sd_mmc_spi.h.
		.spck_delay   = 0,
		.trans_delay  = 0,
		.stay_act     = 1,
		.spi_mode     = 0,
		.modfdis      = 1
	};

	// Assign I/Os to SPI.
	gpio_enable_module(SD_MMC_SPI_GPIO_MAP,
			sizeof(SD_MMC_SPI_GPIO_MAP) / sizeof(SD_MMC_SPI_GPIO_MAP[0]));

	// If the SPI used by the SD/MMC is not enabled.
	if (!spi_is_enabled(SD_MMC_SPI)) {
		// Initialize as master.
		spi_initMaster(SD_MMC_SPI, &spiOptions);

		// Set selection mode: variable_ps, pcs_decode, delay.
		spi_selectionMode(SD_MMC_SPI, 0, 0, 0);

		// Enable SPI.
		spi_enable(SD_MMC_SPI);
	}

	// Initialize SD/MMC with SPI PB clock.
	sd_mmc_spi_init(spiOptions, pcl_freq_param.pba_f);
}

#endif  // SD_MMC_SPI_MEM == ENABLE


#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) || ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))

/*! \brief Initializes SD/MMC resources: GPIO, MCI and SD/MMC.
 */
static void sd_mmc_mci_resources_init(void)
{
	static const gpio_map_t SD_MMC_MCI_GPIO_MAP =
	{
		{SD_SLOT_8BITS_CLK_PIN,   SD_SLOT_8BITS_CLK_FUNCTION  },  // SD CLK.
		{SD_SLOT_8BITS_CMD_PIN,   SD_SLOT_8BITS_CMD_FUNCTION  },  // SD CMD.
		{SD_SLOT_8BITS_DATA0_PIN, SD_SLOT_8BITS_DATA0_FUNCTION},  // SD DAT[0].
		{SD_SLOT_8BITS_DATA1_PIN, SD_SLOT_8BITS_DATA1_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA2_PIN, SD_SLOT_8BITS_DATA2_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA3_PIN, SD_SLOT_8BITS_DATA3_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA4_PIN, SD_SLOT_8BITS_DATA4_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA5_PIN, SD_SLOT_8BITS_DATA5_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA6_PIN, SD_SLOT_8BITS_DATA6_FUNCTION},  // DATA Pin.
		{SD_SLOT_8BITS_DATA7_PIN, SD_SLOT_8BITS_DATA7_FUNCTION}   // DATA Pin.
	};

	// MCI options.
	static const mci_options_t MCI_OPTIONS =
	{
		.card_speed = 400000,
		.card_slot  = SD_SLOT_8BITS, // Default card initialization.
	};

	// Assign I/Os to MCI.
	gpio_enable_module(SD_MMC_MCI_GPIO_MAP,
			sizeof(SD_MMC_MCI_GPIO_MAP) / sizeof(SD_MMC_MCI_GPIO_MAP[0]));

	// Enable pull-up for Card Detect.
	gpio_enable_pin_pull_up(SD_SLOT_8BITS_CARD_DETECT);

	// Enable pull-up for Write Protect.
	gpio_enable_pin_pull_up(SD_SLOT_8BITS_WRITE_PROTECT);

	// Initialize SD/MMC with MCI PB clock.
	sd_mmc_mci_init(&MCI_OPTIONS, pcl_freq_param.pba_f, pcl_freq_param.cpu_f);
}

#endif  // SD_MMC_MCI_0_MEM == ENABLE || SD_MMC_MCI_1_MEM == ENABLE


/*! \brief Main function. Execution starts here.
 *
 * \retval No return from main function
 */
int main(void)
{
	// Configure system clocks.
	if (pcl_configure_clocks(&pcl_freq_param) != PASS)
		while (true);

	// Initialize usart comm
	init_dbg_rs232(pcl_freq_param.pba_f);

#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)
	at45dbx_resources_init();
#endif
#if SD_MMC_SPI_MEM == ENABLE
	sd_mmc_spi_resources_init();
#endif
#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) || ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))
	sd_mmc_mci_resources_init();
#endif
#ifdef FREERTOS_USED
	if (!ctrl_access_init()) {
		portDBG_TRACE("The module CTRL_ACCESS could not be initialized.");
		while (1);
	}
#endif  // FREERTOS_USED

	// Init Hmatrix bus
	init_hmatrix();

	// Initialize USB clock.
	pcl_configure_usb_clock();

	// Initialize USB task
	usb_task_init();

	// Display a welcome banner on USART
	print_dbg("                                                       ......       ......     \r\n");
	print_dbg("       IIIIII  IIIII        IIII   IIIIIIIIIII      IIIIIIIIIII. .IIIIIIIIII.  \r\n");
	print_dbg("      IIIIIII   IIIII      IIIII  IIIIIIIIIIIII     IIIIIIIIIIII..IIIIIIIIIII. \r\n");
	print_dbg("     IIIIIIIII  IIIII     IIIII   IIIII   IIIII     I.      IIIII.:.     IIIII \r\n");
	print_dbg("     IIII IIIII  IIIII    IIII   IIIII    IIIII            .IIII.        IIIII \r\n");
	print_dbg("    IIIII  IIII   IIII   IIIII  IIIIIIIIIIIIII         IIIIIIII          IIII. \r\n");
	print_dbg("    IIII   IIIII  IIIII IIIII   IIIIIIIIIIIII          IIIIIIII.       .IIII:  \r\n");
	print_dbg("   IIIII    IIIII  IIIIIIIII   IIIIIIIIIII                 .IIIII     IIIII.   \r\n");
	print_dbg("  IIIIIIIIIIIIIII   IIIIIIII   IIIII IIIII                  .IIII   .IIII:     \r\n");
	print_dbg("  IIIIIIIIIIIIIIII  IIIIIII   IIIII   IIII         II:.    .IIIII .IIIII.      \r\n");
	print_dbg(" IIIII        IIIII  IIIIII  IIIII    IIIII        IIIIIIIIIIIII.IIIIIIIIIIIIII\r\n");
	print_dbg(" IIIII        IIIII  IIIII   IIIII    IIIII        :IIIIIIIIII.  IIIIIIIIIIIIII\r\n");
	print_dbg("                      III                                                      \r\n");
	print_dbg("                       II                                                      \r\n");

#if USB_DEVICE_FEATURE == true
	// Initialize device CDC USB task
	device_cdc_task_init();
	device_mass_storage_task_init();
#endif

#ifdef FREERTOS_USED
	// Start OS scheduler
	vTaskStartScheduler();
	portDBG_TRACE("FreeRTOS returned.");
	while (true);
#else
	// No OS here. Need to call each task in round-robin mode.
	while (true) {
		usb_task();
	#if USB_DEVICE_FEATURE == true
		device_cdc_task();
		device_mass_storage_task();
	#endif
	}
#endif  // FREERTOS_USED
}

volatile U16  sof_cnt;
volatile U16  sof_cnt_ms;

//!
//! @brief usb_sof_action
//!
//! This function increments the sof_cnt counter each time
//! the USB Start-of-Frame interrupt subroutine is executed (1 ms).
//! Useful to manage time delays
//!
void usb_sof_action(void)
{
	sof_cnt++;
	sof_cnt_ms++;
}
