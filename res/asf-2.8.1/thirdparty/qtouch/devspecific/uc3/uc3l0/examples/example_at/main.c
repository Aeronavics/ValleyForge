/* This source file is part of the ATMEL QTouch Library Release 4.3.1 */
/* This file is prepared for Doxygen automatic documentation generation. */
/*! \file *********************************************************************
 *
 * \brief Autonomous QTouch Example on STK600-RCUC3L0 or UC3L-EK board.
 *
 * This file contains the AT32UC3L QTouch Library API Example application
 * for Autonomous QTouch.
 *
 * On the STK600-RCUC3L0 board, the Example demonstrates communication with
 * QTouch Studio using the QT600 USB Bridge.
 *
 * On the UC3L-EK board, the Example demonstrates Wakeup from Sleep.
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

/*----------------------------------------------------------------------------
                            compiler information
----------------------------------------------------------------------------*/
#if !((defined(__GNUC__) && defined(__AVR32__)) || (defined(__ICCAVR32__) || defined(__AAVR32__)))
#error 'This compiler is not supported at the moment.'
#endif

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/
#if defined(__ICCAVR__)
#include <intrinsics.h>
#endif
#include "compiler.h"

#include "board.h"

/**
 * Includes for Clock & AST.
 */
#include "power_clocks_lib.h"
#include "ast.h"

#include "gpio.h"

#if defined(__GNUC__)
#include "intc.h"
#endif

/**
 * Includes for Touch Library.
 */
#include "touch_api_at32uc3l.h"

/**
 * Includes for Touch Debug interface.
 */
#if DEF_TOUCH_QDEBUG_ENABLE == 1
#include "QDebug_at32uc3l.h"
#endif

/*----------------------------------------------------------------------------
                            manifest constants
----------------------------------------------------------------------------*/
/*! \name Example Clock configuration settings.
 * Note: The QDebug protocol USART clock settings are available in
 * qdebug/Serial.h.  When modifying the EXAMPLE_CPUCLK_HZ clock, care must be
 * taken to modify the TARGET_PBA_FREQ_HZ and TARGET_CPU_FREQ_HZ defines in
 * the Serial.h file for the QDebug protocol to work correctly.
 */
//! @{

#define EXAMPLE_TARGET_DFLL_FREQ_HZ       (96000000)	//!< DFLL target frequency, in Hz
#define EXAMPLE_TARGET_MCUCLK_FREQ_HZ     (48000000)	//!< MCU clock target frequency, in Hz
#define EXAMPLE_TARGET_PBACLK_FREQ_HZ     (48000000)	//!< PBA clock target frequency, in Hz
#define EXAMPLE_TARGET_PBBCLK_FREQ_HZ     (48000000)	//!< PBA clock target frequency, in Hz

//! @}

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                            type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                            Structure Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                global variables
----------------------------------------------------------------------------*/
/**
 * Flag set by touch_at_status_change_interrupt_callback() function when a fresh Touch
 * status is available.
 */
volatile int8_t autonomous_qtouch_in_touch = -1;

/**
 * Dummy variable for QDebug protocol for compatibility with QMatrix and QTouch.
 */
uint16_t measurement_period_ms;

/*----------------------------------------------------------------------------
                                extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                static variables
----------------------------------------------------------------------------*/
/*! \name Parameters to pcl_configure_clocks().
 */
//! @{

static scif_gclk_opt_t gc_dfllif_ref_opt = { SCIF_GCCTRL_SLOWCLOCK, 0, false };
static pcl_freq_param_t pcl_dfll_freq_param = {
  .main_clk_src = PCL_MC_DFLL0,
  .cpu_f = EXAMPLE_TARGET_MCUCLK_FREQ_HZ,
  .pba_f = EXAMPLE_TARGET_PBACLK_FREQ_HZ,
  .pbb_f = EXAMPLE_TARGET_PBBCLK_FREQ_HZ,
  .dfll_f = EXAMPLE_TARGET_DFLL_FREQ_HZ,
  .pextra_params = &gc_dfllif_ref_opt
};

//! @}

/**
 * Autonomous QTouch Configuration structure provided as input to Touch Library.
 *
 * Note: Use the touch_config_at32uc3l.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure. */
static touch_at_config_t at_config = {
  {
   AT_SP_SELECTED		/* Autonomous Touch Sense pair selected. */
   },
  {
   AT_CAT_CLK_DIV,		/* Autonomous Touch Burst timing clock divider. */
   AT_CHLEN,			/* chlen; ATCFG0 Register. */
   AT_SELEN,			/* selen; ATCFG0 Register. */
   AT_DISHIFT,			/* dishift; ATCFG1 Register. */
   AT_ENABLE_EXTERNAL_SYNC,	/* sync; ATCFG1 Register. */
   AT_ENABLE_SPREAD_SPECTRUM,	/* spread; ATCFG1 Register. */
   AT_DILEN,			/* dilen; ATCFG1 Register. */
   AT_MAX_ACQ_COUNT,		/* max; MGCFG1 Register. */
   {
    AT_FILTER,			/* Autonomous Touch Filter Setting. Refer ATCFG2 register. */
    AT_OUTSENS,			/* Out-of-Touch Sensitivity. Refer ATCFG2 register. */
    AT_SENSE,			/* Sensitivity. Refer ATCFG2 register. */
    AT_PTHR,			/* Positive Recalibration Threshold. Refer ATCFG3 register. */
    AT_PDRIFT,			/* Positive Drift Compensation. Refer ATCFG3 register. */
    AT_NDRIFT,			/* Negative Drift Compensation. Refer ATCFG3 register. */
    }
   }
};

/**
 * General configuration options common to QMatrix, QTouch and Autonomous Touch
 * provided as input to Touch library.
 *
 * Note: Use the touch_config_at32uc3l.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure. */
static touch_general_config_t general_config = {
  TOUCH_SYNC_PIN_OPTION,	/* Specify the sync pin option,
				   if included in the hardware design.
				   refer general_pin_options_t. */
  TOUCH_SPREAD_SPECTRUM_MAX_DEV,	/* uint8_t  maxdev; SSCFG Register. Max deviation of spread spectrum. */
  TOUCH_CSARES,			/* uint32_t csares; CSA Resistor control register. */
  TOUCH_CSBRES			/* uint32_t csbres;  CSA Resistor control register. */
};

/**
 * Touch Library input configuration structure.
 */
touch_config_t touch_config = {
  NULL,				/* Pointer to QMatrix configuration structure. */
  &at_config,			/* Pointer to Autonomous Touch configuration structure. */
  NULL,				/* Pointer to QTouch Group A configuration structure. */
  NULL,				/* Pointer to QTouch Group B configuration structure. */
  &general_config		/* Pointer to General configuration structure. */
};

/*----------------------------------------------------------------------------
                                prototypes
----------------------------------------------------------------------------*/
/*! \brief Initialize host app, pins, watchdog, clock etc.
 */
static void init_system (void);

/*! \brief Autonomous QTouch Group status change callback function example prototype.
 */
static void touch_at_status_change_interrupt_callback (touch_at_status *
						       p_at_status);

/*! \brief Initialize clock.
 */
static unsigned long init_clock (void);

/*! \brief Initialize Asynchronous Timer.
 */
#if DEF_TOUCH_QDEBUG_ENABLE == 0
static void ast_init (void);
#endif

/*! \brief Example application entry function.
 */
int
main (void)
{

/*  BEFORE USING THE EXAMPLE PROJECTS.

1. For support queries on,
     - QTouch Library usage
     - Capacitive Touch Sensor Tuning
     - Capacitive Touch Schematic design
     - Capacitive Touch Sensor design
   email touch@atmel.com

2. For more QTouch Library documentation,
   refer doc8207: Atmel QTouch Library User Guide.

   For Capacitive Touch Sensor tuning guidelines,
   refer QTAN0062: QTouch and QMatrix Sensitivity Tuning for Keys, Sliders and Wheels.

   For Capacitive Touch Sensor design,
   refer doc10620.pdf: Touch Sensors Design Guide.

   http://www.atmel.com/dyn/products/app_notes.asp?family_id=697

3. The Example application uses a CPU, PBA and PBB clock of 48MHz.
   When using a different frequency setting, the following parameters must be
   changed accordingly to ensure proper QTouch operation.
   a. AT_CAT_CLK_DIV.
   b. TOUCH_SPREAD_SPECTRUM_MAX_DEV, when Spread spectrum is enabled.
   c. PBA_HZ, when using qdebug/SPI_Master.c
   d. TARGET_PBA_FREQ_HZ and TARGET_CPU_FREQ_HZ, when using qdebug/SERIAL.c

4. The Example project has been tested with 3.3v Single supply mode.

5. The Example projects demonstrates:-
   a) Autonomous QTouch Sleep mode.
      The UC3L-EK board has been used to test the Sleep mode of operation since
      an external 32KHz crystal is available on this board.  The Asynchornous
      timer is configured to periodically generate an peripheral event. When
      the device is set to STATIC Sleep mode, the Asynchonous Timer (AST) uses
      the 32KHz external clock.  A single peripheral event from the AST trigger
      one Autonomous QTouch measurement.  This happens periodically.  The CPU
      is not woken up unless there is a IN_TOUCH or OUT_OF_TOUCH detection in
      the Autonomous QTouch sensor.

      Important Note: The (csa3/csb3) Touch channel connections are
      multiplexed with the JTAG pins. So, when using the JTAG debugging mode, these
      Touch channel connections MUST be removed. In the Flash mode, this will not
      cause any issues.

	  Sense Pair 3 (SP3) is used
      -----------------------------------------------
	  CAT CSA/CSB name - UC3L-EK board Port-pin name
	  ------------------------------------------------
	  KEY 1
	  csa3 (SNS3)	 - 	PA02  //Pin 3 on JTAG Header
	  csb3 (SNSK3)	 - 	PA03  //Pin 9 on JTAG Header

   b) QTouch Studio mode.
      When the define DEF_TOUCH_QDEBUG_ENABLE in the touch_config_at32uc3l.h
      file is set to 1, this example project can be used to connect to QTouch
      studio. STK600 board and QT600 USB Bridge can be used to verify this.

      STK600-Autonomous QTouch Test setup pin information.
      The following table indicates the STK600 pin connections for the STK600-
      Autonomous QTouch test setup.

      ----------------------------------------------
	  CAT CSA/CSB name - STK600 board Port-pin name
      ----------------------------------------------
	  KEY 1
	  csa15 		 - 	pe4
	  csb15 		 - 	pe1

      ----------------------------------------------
	  QT600 USB Bridge
	  'TOUCH DATA' Header Pin name - STK600 board Port-pin name
	  ----------------------------------------------
	  PA22 - 'TOUCH DATA' header pin 8 - clk 	 - pc6
	  PA21 - 'TOUCH DATA' header pin 7 - miso	 - pc5
	  PA20 - 'TOUCH DATA' header pin 6 - mosi    - pc4
	  PA14 - 'TOUCH DATA' header pin 5 - nss 	 - pb6

6. For the case of Autonomous QTouch, the following settings can be modified by
   the QTouch Studio.
   a. Detect Threshold (Sense level) - AT_SENSE.
   b. Detect Integration - AT_FILTER.
   c. Negative Drift rate - AT_NDRIFT.
   d. Positive Drift rate - AT_PDRIFT.

7. When two or more acquisition methods are used, care must be taken such that a
   given port pin is not used by more than one method at the same time.  The following
   pin configuration options available in touch_config_at32uc3l.h must be carefully
   chosen to avoid any overlapping.
   a. QMatrix Pin Configuration Options.
   b. Autonomous QTouch Pin Configuration Options.
   c. QTouch Group A Pin Configuration Options.
   d. QTouch Group B Pin Configuration Options.
   e. Touch Sync Pin option.
*/

  touch_ret_t touch_ret = TOUCH_SUCCESS;
#if DEF_TOUCH_QDEBUG_ENABLE == 1
  uint32_t delay_counter;
#endif

  /* Initialize host clock, pins, watchdog, etc. */
  init_system ();

#if 0
    /* When using 1.8V Single supply mode, the Voltage Regulator can be shut-down
       using the code below, in-order to save power.
       See Voltage Regulator Calibration Register in datasheet for more information.
       CAUTION: When using 3.3V Single supply mode, the Voltage Regulator cannot
       be shut-down. */
    uint32_t tmp = (AVR32_SCIF.vregcr);
    tmp &= (~(1 << 5));
    AVR32_SCIF.unlock = 0xAA000000 | AVR32_SCIF_VREGCR;
    AVR32_SCIF.vregcr = tmp;

    while((AVR32_SCIF.vregcr & 0x20));
#endif

  /* Disable interrupts. */
  Disable_global_interrupt ();

  /* The INTC driver has to be used only for GNU GCC for AVR32. */
#if (defined __GNUC__)

  /* Initialize interrupt vectors. */
  INTC_init_interrupts ();

  /* Register the Touch Library CAT interrupt handler to the interrupt controller.
     Note: This interrupt registration is a MUST before using the Touch Library
     with the GCC compiler.

     For the case of IAR the registration of interrupt is automatically taken
     care by the compiler. The Touch Libary CAT interrupt level for the case
     of IAR is fixed to Interrupt level 3. */
  INTC_register_interrupt (&touch_acq_done_irq, AVR32_CAT_IRQ,
			   AVR32_INTC_INT3);

#endif

  /* Enable interrupts. */
  Enable_global_interrupt ();

  /* Initialize touch library and uc3l cat module for Autonomous QTouch operation. */
  touch_ret = touch_at_sensor_init (&touch_config);
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1u);		/* Check API Error return code. */
    }

#if DEF_TOUCH_QDEBUG_ENABLE == 1
  /* Initialize the debug interface. */
  QDebug_Init ();
#else
  /* Initialize Asynchronous Timer in periodic mode. */
  ast_init ();

  /* Enable the Asynchronous Timer. */
  ast_enable (&AVR32_AST);

#endif

  /* Enable Autonomous QTouch sensor for continuous acquisition. A IN_TOUCH or
     OUT_OF_TOUCH status is continuously updated until the sensor is disabled
     using the touch_at_sensor_disable() API. */
  touch_ret =
    touch_at_sensor_enable (touch_at_status_change_interrupt_callback);
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1u);		/* Check API Error return code. */
    }

#if DEF_TOUCH_QDEBUG_ENABLE == 0
  /* Turn OFF LED0 of UC3L-EK. */
  gpio_set_gpio_pin (AVR32_PIN_PA21);
#endif

  /* Loop forever */
  for (;;)
    {

#if DEF_TOUCH_QDEBUG_ENABLE == 1
      /* QT600 USB Bridge two-way QDebug communication application Example. */
      /* Process any commands received from QTouch Studio. */
      QDebug_ProcessCommands ();

      /* Send out the Touch debug information data each time when Touch
         measurement process is completed . */
      QDebug_SendData (0x000A);	/* Enable TOUCH_STATUS_CHANGE and TOUCH_CHANNEL_REF_CHANGE
				   qt_lib_flags allways for Autonomous QTouch.  */

      /* Delay so that we dont send the data to QTouch Studio too frequently. */
      for (delay_counter = 0u; delay_counter < 1200u; delay_counter++);

#else

      /* Sleep mode.
         If there is a chance that any PB write operations are incomplete, the CPU
         should perform a read operation from any register on the PB bus before
         executing the sleep instruction. */
      AVR32_INTC.ipr[0];	/* Dummy read. */

      /* Enable Asynchronous Wakeup for CAT module */
      pm_asyn_wake_up_enable (AVR32_PM_AWEN_CATWEN_MASK);

      /* Go into a sleep mode until woken up by Autonomous QTouch. */
      SLEEP (AVR32_PM_SMODE_FROZEN);

      /* Disable Asynchronous Wakeup for CAT module */
      pm_asyn_wake_up_enable (AVR32_PM_AWEN_CATWEN_MASK);

      /* Clear All AST Interrupt request and clear SR */
      AVR32_AST.scr = 0xFFFFFFFF;

      /* When woken up by Autonomous QTouch interrupt, the touch_at_status_change_interrupt_callback()
         is called that updates the autonomous_qtouch_in_touch status flag. */

      /* Host application code goes here */
#endif

    }
}

/*! \brief Autonomous QTouch status change interrupt callback function.
 * This callback function is called by the Touch library in the
 * CAT Autonomous QTouch status change Interrupt context, each time
 * there is a status change in the Autonomous Touch sensor.
 *
 * \param  p_at_status: Autonomous QTouch status.
 *         p_at_status->status_change: Autonomous QTouch status change.
 *         p_at_status->base_count: Autonomous QTouch base count value.
 *         p_at_status->current_count: Autonomous QTouch current count value.
 * \note   1. CAUTION - This callback function is called in the CAT Autonomous
 * QTouch Status change INTERRUPT SERVICE ROUTINE by the Touch Library.
 * 2. The Autonomous QTouch Status change callback is called both for
 * an IN_TOUCH status change and an OUT_OF_TOUCH status change.
 */
void
touch_at_status_change_interrupt_callback (touch_at_status * p_at_status)
{
  if (p_at_status->status_change == IN_TOUCH)
    {
      autonomous_qtouch_in_touch = 1u;

#if DEF_TOUCH_QDEBUG_ENABLE == 0
      /* Turn ON LED0 once Autonomous QTouch sense is detected. */
      gpio_clr_gpio_pin (AVR32_PIN_PA21);
#endif
    }
  else				/* p_at_status->status_change == OUT_OF_TOUCH */
    {
      autonomous_qtouch_in_touch = 0u;
#if DEF_TOUCH_QDEBUG_ENABLE == 0
      /* Turn ON LED0 once Autonomous QTouch sense is detected. */
      gpio_set_gpio_pin (AVR32_PIN_PA21);
#endif
    }
}

/*! \brief Initialize host clock, pins, watchdog, etc.
 */
void
init_system (void)
{
  int32_t ret_val = 0u;

  /* 1. Configure and start the DFLL0 in open loop mode to generate a frequency of 96MHz.
     2. Set Flash Wait state.
     3. Configure CPU, PBA, PBB clock to 48MHz.
     4. Set up the GCLK_CAT for QMatrix operation.  */
  ret_val = init_clock ();
  if (ret_val != 0u)
    {
      while (1);		/* Clock configuration failed. */
    }

  /* Do any other system initialization. */

}

/*! \brief Initialize Clock.
 */
static unsigned long
init_clock (void)
{
  unsigned long ret_val = 0u;

#if DEF_TOUCH_QDEBUG_ENABLE == 0
  /* For UC3L-EK board, 32Khz external oscillator is connected to xin32_2 and xout32_2. */
  scif_osc32_opt_t opt = {
    SCIF_OSC_MODE_2PIN_CRYSTAL_HICUR,	/* 2-pin Crystal and high current mode. Crystal is connected to XIN32/XOUT32. */
    AVR32_SCIF_OSCCTRL32_STARTUP_0_RCOSC,	/* oscillator startup time. */
    true,			/* select the alternate xin32_2 and xout32_2 for the 32kHz crystal oscillator. */
    false,			/* disable the 1kHz output. */
    true			/* enable the 32kHz output. */
  };

  ret_val |= scif_start_osc32 (&opt, true);
#endif

  /*Configure the DFLL and switch the main clock source to the DFLL. */
  ret_val |= pcl_configure_clocks (&pcl_dfll_freq_param);

  return (ret_val);
}

/*! \brief Initialize AST.
 */
#if DEF_TOUCH_QDEBUG_ENABLE == 0
static void
ast_init (void)
{
  unsigned long ast_counter = 0;

  avr32_ast_pir0_t pir = {
    .insel = 10			/* Set a event every 62.5ms. */
  };

  if (!ast_init_counter
      (&AVR32_AST, AST_OSC_32KHZ, AST_PSEL_32KHZ_1HZ, ast_counter))
    {
      while (1u);		/* Check AST timer. */
    }

  ast_set_periodic0_value (&AVR32_AST, pir);

  ast_enable_periodic0 (&AVR32_AST);

  /* Clear All AST Interrupt request and clear SR */
  AVR32_AST.scr = 0xFFFFFFFF;

}
#endif
