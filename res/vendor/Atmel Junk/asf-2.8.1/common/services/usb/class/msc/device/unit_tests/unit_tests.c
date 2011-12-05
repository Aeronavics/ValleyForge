/**
 * \file
 *
 * \brief Main functions for MSC unit test
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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

#include <stdio.h>
#include <asf.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include "at45dbx.h"

/**
 * \mainpage ASF USB Device MSC
 *
 * \section intro Introduction
 * This unit test implements an USB Device MSC enumeration.
 * It is to validated the MSC enumeration 
 * and USB core callback (VBus presence, resume, suspend and SOF).
 * This unit test uses the native MSC driver for these operating systems.
 *
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stopbit configuration of USART
 */
//@}

static bool main_b_vbus_event = false;
static bool main_b_resume_event = false;
static bool main_b_suspend_event = false;
static bool main_b_sof_event = false;
static bool main_b_msc_enumerated = false;
static bool main_b_msc_read = false;


#if UC3A3
//! \brief Init HMatrix
static void init_hmatrix(void);
#endif
#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) \
	|| ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))
//! \brief Initializes SD/MMC resources: GPIO, MCI and SD/MMC.
static void sd_mmc_mci_resources_init(void);
#endif


static void run_usb_msc_test(const struct test_case *test)
{
#if UC3A3
	// Init Hmatrix bus   
	sysclk_enable_pbb_module(SYSCLK_HMATRIX);
	init_hmatrix();
#endif
#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)
	at45dbx_init();
#endif
#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) \
	|| ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))
	// Initialize SD/MMC with MCI PB clock.
	sysclk_enable_pbb_module(SYSCLK_MCI);
	sysclk_enable_hsb_module(SYSCLK_DMACA);
	sd_mmc_mci_resources_init();
#endif

	// Start USB stack to authorize VBus monitoring
	udc_start();

	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		main_vbus_action(true);
	}

	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (!main_b_msc_read) {

		if (main_b_msc_enumerated) {
			if (!udi_msc_process_trans()) {
				sleepmgr_enter_sleep();
			}
		}else{
			sleepmgr_enter_sleep();
		}
	}
	test_assert_true(test, main_b_msc_enumerated, "MSC enumeration fails");

	udc_stop();
}

static void run_usb_msc_read_test(const struct test_case *test)
{
	test_assert_true(test, main_b_msc_read, "No read access detected");
}


static void run_usb_vbus_test(const struct test_case *test)
{
	test_assert_true(test, main_b_vbus_event, "Event vbus not receiv");
}

static void run_usb_resume_test(const struct test_case *test)
{
	test_assert_true(test, main_b_resume_event, "Event resume not receiv");
}

static void run_usb_suspend_test(const struct test_case *test)
{
	test_assert_true(test, main_b_suspend_event, "Event suspend not receiv");
}

static void run_usb_sof_test(const struct test_case *test)
{
	test_assert_true(test, main_b_sof_event, "Event sof not receiv");
}


/**
 * \brief Run usb device msc unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * usb unit test suite and runs it.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
#if defined(__GNUC__) && defined(__AVR32__)
	// This unit test will be launched on a test-server, using avr32program.
	// The reset is done through the OCD. The 'setbuf' command allows to make the
	// application starts correctly: it will not execute the 'breakpoint'
	// instruction in _fstat_host (used by printf) and the core will not stay
	// blocked on the 'breakpoint' instruction (executed in the debug mode).
	setbuf(stdout, NULL);
#endif
	// Define all the timestamp to date test cases
	DEFINE_TEST_CASE(usb_msc_test, NULL,
			run_usb_msc_test, NULL,
			"USB Device msc enumeration test");
	DEFINE_TEST_CASE(usb_msc_read_test, NULL,
			run_usb_msc_read_test, NULL,
			"USB MSC read access test");
	DEFINE_TEST_CASE(usb_vbus_test, NULL,
			run_usb_vbus_test, NULL,
			"USB vbus event test");
	DEFINE_TEST_CASE(usb_resume_test, NULL,
			run_usb_resume_test, NULL,
			"USB resume event test");
	DEFINE_TEST_CASE(usb_suspend_test, NULL,
			run_usb_suspend_test, NULL,
			"USB suspend event test");
	DEFINE_TEST_CASE(usb_sof_test, NULL,
			run_usb_sof_test, NULL,
			"USB sof event test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(usb_msc_tests) = {
		&usb_msc_test,
		&usb_msc_read_test,
		&usb_vbus_test,
		&usb_resume_test,
		&usb_suspend_test,
		&usb_sof_test,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(usb_msc_suite, usb_msc_tests,
			"Common usb MSC service with test suite");

	// Run all tests in the suite
	test_suite_run(&usb_msc_suite);

	while (1) {
		// Intentionally left empty.
	}
}


void main_vbus_action(bool b_high)
{
	if (b_high) {
		main_b_vbus_event = true;
		// Attach USB Device
		udc_attach();
	} else {
		// VBUS not present
		udc_detach();
	}
}

void main_suspend_action(void)
{
	main_b_resume_event = true;
}

void main_resume_action(void)
{
	main_b_suspend_event = true;
}

void main_sof_action(void)
{
	main_b_sof_event = true;
}

bool main_msc_enable(void)
{
	main_b_msc_enumerated = true;
	return true;
}

void main_msc_disable(void)
{
	main_b_msc_enumerated = false;
}

void main_msc_read_finish(void)
{
	main_b_msc_read = true;
}

#if UC3A3
/*! \name Hmatrix bus configuration
 */
static void init_hmatrix(void)
{
	union {
		unsigned long scfg;
		avr32_hmatrix_scfg_t SCFG;
	} u_avr32_hmatrix_scfg;

	// For the internal-flash HMATRIX slave, use last master as default.
	u_avr32_hmatrix_scfg.scfg =
			AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH];
	u_avr32_hmatrix_scfg.SCFG.defmstr_type =
			AVR32_HMATRIX_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH] =
			u_avr32_hmatrix_scfg.scfg;
}
#endif


#if ((defined SD_MMC_MCI_0_MEM) && (SD_MMC_MCI_0_MEM == ENABLE)) \
	|| ((defined SD_MMC_MCI_1_MEM) && (SD_MMC_MCI_1_MEM == ENABLE))
#include "conf_sd_mmc_mci.h"
#include "mci.h"

/*! \brief Initializes SD/MMC resources: GPIO, MCI and SD/MMC.
 */
static void sd_mmc_mci_resources_init(void)
{
	static const gpio_map_t SD_MMC_MCI_GPIO_MAP = {
		{SD_SLOT_8BITS_CLK_PIN, SD_SLOT_8BITS_CLK_FUNCTION},	// SD CLK.
		{SD_SLOT_8BITS_CMD_PIN, SD_SLOT_8BITS_CMD_FUNCTION},	// SD CMD.
		{SD_SLOT_8BITS_DATA0_PIN, SD_SLOT_8BITS_DATA0_FUNCTION},	// SD DAT[0].
		{SD_SLOT_8BITS_DATA1_PIN, SD_SLOT_8BITS_DATA1_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA2_PIN, SD_SLOT_8BITS_DATA2_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA3_PIN, SD_SLOT_8BITS_DATA3_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA4_PIN, SD_SLOT_8BITS_DATA4_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA5_PIN, SD_SLOT_8BITS_DATA5_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA6_PIN, SD_SLOT_8BITS_DATA6_FUNCTION},	// DATA Pin.
		{SD_SLOT_8BITS_DATA7_PIN, SD_SLOT_8BITS_DATA7_FUNCTION}	// DATA Pin.
	};

	// Assign I/Os to MCI.
	gpio_enable_module(SD_MMC_MCI_GPIO_MAP,
			sizeof(SD_MMC_MCI_GPIO_MAP) /
			sizeof(SD_MMC_MCI_GPIO_MAP[0]));

	// Enable pull-up for Card Detect.
	gpio_enable_pin_pull_up(SD_SLOT_8BITS_CARD_DETECT);

	// Enable pull-up for Write Protect.
	gpio_enable_pin_pull_up(SD_SLOT_8BITS_WRITE_PROTECT);

	sd_mmc_mci_init(SD_SLOT_8BITS, sysclk_get_pbb_hz(), sysclk_get_cpu_hz());
}
#endif // SD_MMC_MCI_0_MEM == ENABLE || SD_MMC_MCI_1_MEM == ENABLE

