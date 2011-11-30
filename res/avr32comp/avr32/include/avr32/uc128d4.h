/*****************************************************************************
 *
 * Copyright (C) 2006 Atmel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * * Neither the name of the copyright holders nor the names of
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Model        : UC128D4
 * Revision     : $Revision $
 * Checkin Date : $Date $
 *
 ****************************************************************************/
#ifndef AVR32_UC128D4_H_INCLUDED
#define AVR32_UC128D4_H_INCLUDED


/* Instance count */
#define AVR32_ADCIFD_NUM                   1
#define AVR32_AST_NUM                      1
#define AVR32_AW_NUM                       1
#define AVR32_CAT_NUM                      1
#define AVR32_EIC_NUM                      1
#define AVR32_FLASHCDW_NUM                 1
#define AVR32_FREQM_NUM                    1
#define AVR32_GLOC_NUM                     1
#define AVR32_GPIO_NUM                     1
#define AVR32_HMATRIXB_NUM                 1
#define AVR32_IISC_NUM                     1
#define AVR32_JTAG_NUM                     1
#define AVR32_PDCA_NUM                     1
#define AVR32_PM_NUM                       1
#define AVR32_PULLUP_NUM                   1
#define AVR32_PWMA_NUM                     1
#define AVR32_SCAN_NUM                     1
#define AVR32_SCIF_NUM                     1
#define AVR32_SPI_NUM                      1
#define AVR32_TC_NUM                       1
#define AVR32_TWIM_NUM                     1
#define AVR32_TWIMS_NUM                    1
#define AVR32_TWIS_NUM                     1
#define AVR32_USART_NUM                    3
#define AVR32_USBC_NUM                     1
#define AVR32_WDT_NUM                      1

/* Maskable module clocks */
#define AVR32_PM_CLK_GRP_CPU               0
#define AVR32_PM_CLK_GRP_HSB               1
#define AVR32_PM_CLK_GRP_PBA               2
#define AVR32_PM_CLK_GRP_PBB               3
#define AVR32_PM_NUM_CLK_GRPS              4
#define AVR32_PM_NUM_CLKS_PER_GRP0         1
#define AVR32_PM_NUM_CLKS_PER_GRP1         5
#define AVR32_PM_NUM_CLKS_PER_GRP2         22
#define AVR32_PM_NUM_CLKS_PER_GRP3         3

/* CPU clocks */
#define AVR32_OCD_CLK_CPU                  1
#define AVR32_CORE_CLK_CPU_COUNT           16

/* HSB clocks */
#define AVR32_FLASHCDW_CLK_HSB             32
#define AVR32_HMATRIX_CLK_HSB_PBA_BRIDGE   33
#define AVR32_HMATRIX_CLK_HSB_PBB_BRIDGE   34
#define AVR32_USBC_CLK_HSB                 35
#define AVR32_PDCA_CLK_HSB                 36

/* PBA clocks */
#define AVR32_PDCA_CLK_PBA                 64
#define AVR32_INTC_CLK_PBA                 65
#define AVR32_PM_CLK_PBA                   66
#define AVR32_AST_CLK_PBA                  67
#define AVR32_WDT_CLK_PBA                  68
#define AVR32_EIC_CLK_PBA                  69
#define AVR32_GPIO_CLK_PBA                 70
#define AVR32_USART0_CLK_PBA               71
#define AVR32_USART1_CLK_PBA               72
#define AVR32_USART2_CLK_PBA               73
#define AVR32_SPI_CLK_PBA                  74
#define AVR32_TWIM_CLK_PBA                 75
#define AVR32_TWIS_CLK_PBA                 76
#define AVR32_PWMA_CLK_PBA                 77
#define AVR32_I2SC_CLK_PBA                 78
#define AVR32_TC_CLK_PBA                   79
#define AVR32_ADCIFD_CLK_PBA               80
#define AVR32_SCIF_CLK_PBA                 81
#define AVR32_FREQM_CLK_PBA                82
#define AVR32_CAT_CLK_PBA                  83
#define AVR32_GLOC_CLK_PBA                 84
#define AVR32_AW_CLK_PBA                   85

/* PBB clocks */
#define AVR32_USBC_CLK_PBB                 96
#define AVR32_HMATRIX_CLK_PBB              97
#define AVR32_FLASHCDW_CLK_PBB             98

/* Generic clocks */
#define AVR32_SCIF_GCLK_GCLK0              0
#define AVR32_SCIF_GCLK_GLOC               0
#define AVR32_SCIF_GCLK_GCLK1              1
#define AVR32_SCIF_GCLK_GCLK2              2
#define AVR32_SCIF_GCLK_GCLK3              3
#define AVR32_SCIF_GCLK_USBC               3
#define AVR32_SCIF_GCLK_GCLK4              4
#define AVR32_SCIF_GCLK_PWM                4
#define AVR32_SCIF_GCLK_GCLK5              5
#define AVR32_SCIF_GCLK_IISC               5
#define AVR32_SCIF_GCLK_GCLK6              6
#define AVR32_SCIF_GCLK_AST                6
#define AVR32_SCIF_GCLK_GCLK7              7
#define AVR32_SCIF_GCLK_GCLK8              8
#define AVR32_SCIF_GCLK_ADCIFD             8

/* Core */
#include "avr32/core_sc0_212.h"
/* OCD */
#include "avr32/ocd_s0_212.h"

/* CORE */
#define AVR32_CORE_OCD_DCCPU_READ_IRQ      577
#define AVR32_CORE_OCD_DCEMU_DIRTY_IRQ     576
#define AVR32_CORE_COMPARE_IRQ             0
#define AVR32_CORE_SCAN_CHAIN_MSB          9
#define AVR32_CORE_SCAN_CLOCK_MSB          1


/* OCD */

/* Memories */
#define AVR32_CPU_RAM_ADDRESS              0x00000000
#define AVR32_CPU_RAM_SIZE                 0x00004000
#define AVR32_CPU_RAM                      ((unsigned char *)AVR32_CPU_RAM_ADDRESS)
#define AVR32_FLASH_ADDRESS                0x80000000
#define AVR32_FLASH_SIZE                   0x00020000
#define AVR32_FLASH                        ((unsigned char *)AVR32_FLASH_ADDRESS)
#define AVR32_HTOP0_ADDRESS                0xFFFF0000
#define AVR32_HTOP0_SIZE                   0x00007000
#define AVR32_HTOP0                        ((unsigned char *)AVR32_HTOP0_ADDRESS)
#define AVR32_HTOP1_ADDRESS                0xFFFE0000
#define AVR32_HTOP1_SIZE                   0x00002400
#define AVR32_HTOP1                        ((unsigned char *)AVR32_HTOP1_ADDRESS)

/* Interrupt Controller */
#define AVR32_INTC_ADDRESS                 0xFFFF1000
#define AVR32_INTC                         (*((volatile avr32_intc_t*)AVR32_INTC_ADDRESS))
#define AVR32_INTC_NUM_INT_GRPS            23
#define AVR32_INTC_NUM_IRQS_PER_GRP0       1
#define AVR32_INTC_NUM_IRQS_PER_GRP1       10
#define AVR32_INTC_NUM_IRQS_PER_GRP10      1
#define AVR32_INTC_NUM_IRQS_PER_GRP11      1
#define AVR32_INTC_NUM_IRQS_PER_GRP12      1
#define AVR32_INTC_NUM_IRQS_PER_GRP13      1
#define AVR32_INTC_NUM_IRQS_PER_GRP14      3
#define AVR32_INTC_NUM_IRQS_PER_GRP15      3
#define AVR32_INTC_NUM_IRQS_PER_GRP16      0
#define AVR32_INTC_NUM_IRQS_PER_GRP17      1
#define AVR32_INTC_NUM_IRQS_PER_GRP18      2
#define AVR32_INTC_NUM_IRQS_PER_GRP19      1
#define AVR32_INTC_NUM_IRQS_PER_GRP2       7
#define AVR32_INTC_NUM_IRQS_PER_GRP20      4
#define AVR32_INTC_NUM_IRQS_PER_GRP21      1
#define AVR32_INTC_NUM_IRQS_PER_GRP22      1
#define AVR32_INTC_NUM_IRQS_PER_GRP3       7
#define AVR32_INTC_NUM_IRQS_PER_GRP4       1
#define AVR32_INTC_NUM_IRQS_PER_GRP5       1
#define AVR32_INTC_NUM_IRQS_PER_GRP6       1
#define AVR32_INTC_NUM_IRQS_PER_GRP7       1
#define AVR32_INTC_NUM_IRQS_PER_GRP8       1
#define AVR32_INTC_NUM_IRQS_PER_GRP9       1
#define AVR32_INTC_NUM_NMI                 1

#include "avr32/intc_102.h"


/* ADCIFD */

/* ADCIFD */
#define AVR32_ADCIFD_ADDRESS               0xFFFF5400
#define AVR32_ADCIFD                       (*((volatile avr32_adcifd_t*)AVR32_ADCIFD_ADDRESS))
#define AVR32_ADCIFD_SEQUENCER_LINE        480
#define AVR32_ADCIFD_TIMING_LINE           481
#define AVR32_ADCIFD_WINDOW_LINE           482
#define AVR32_ADCIFD_CHANNELS              8
#define AVR32_ADCIFD_GCLK_NUM              8
#define AVR32_ADCIFD_NBCONVS               8
#define AVR32_ADCIFD_PDCA_ID_RX            8
#define AVR32_ADCIFD_ADCOUT_0_PIN          18
#define AVR32_ADCIFD_ADCOUT_1_PIN          19
#define AVR32_ADCIFD_ADCOUT_2_PIN          20
#define AVR32_ADCIFD_ADCOUT_3_PIN          21
#define AVR32_ADCIFD_ADCOUT_4_PIN          22
#define AVR32_ADCIFD_ADCOUT_5_PIN          23
#define AVR32_ADCIFD_ADCOUT_6_PIN          24
#define AVR32_ADCIFD_ADCOUT_7_PIN          25
#define AVR32_ADCIFD_ADCOUT_8_PIN          26
#define AVR32_ADCIFD_ADCOUT_9_PIN          27
#define AVR32_ADCIFD_CLK_PIN               9
#define AVR32_ADCIFD_EOC_PIN               17
#define AVR32_ADCIFD_EXTTRIG_PIN           22
#define AVR32_ADCIFD_EXTTRIG_FUNCTION      2
#define AVR32_ADCIFD_MUXONMX_PIN           13
#define AVR32_ADCIFD_MUXSEL_0_PIN          14
#define AVR32_ADCIFD_MUXSEL_1_PIN          15
#define AVR32_ADCIFD_MUXSEL_2_PIN          16
#define AVR32_ADCIFD_ONAD_PIN              10
#define AVR32_ADCIFD_ONSAR_PIN             11
#define AVR32_ADCIFD_START_PIN             12

#include "avr32/adcifd_100.h"


/* AST */

/* AST */
#define AVR32_AST_ADDRESS                  0xFFFF1800
#define AVR32_AST                          (*((volatile avr32_ast_t*)AVR32_AST_ADDRESS))
#define AVR32_AST_ALARM_IRQ                40
#define AVR32_AST_CLKREADY_IRQ             640
#define AVR32_AST_OVF_IRQ                  641
#define AVR32_AST_PER_IRQ                  642
#define AVR32_AST_READY_IRQ                643
#define AVR32_AST_CLK32                    1
#define AVR32_AST_GCLK_NUM                 6
#define AVR32_AST_GENCLK                   3
#define AVR32_AST_PB                       2
#define AVR32_AST_RCOSC                    0

#include "avr32/ast_310.h"


/* AW */

/* AW */
#define AVR32_AW_ADDRESS                   0xFFFF6800
#define AVR32_AW                           (*((volatile avr32_aw_t*)AVR32_AW_ADDRESS))
#define AVR32_AW_IRQ                       704
#define AVR32_AW_PDCA_ID_RX                11
#define AVR32_AW_PDCA_ID_TX                21
#define AVR32_AW_DATAOUT_PIN               44

#include "avr32/aw_230.h"


/* CAT */

/* CAT */
#define AVR32_CAT_ADDRESS                  0xFFFF6000
#define AVR32_CAT                          (*((volatile avr32_cat_t*)AVR32_CAT_ADDRESS))
#define AVR32_CAT_IRQ                      672
#define AVR32_CAT_GCLK_NUM                 0
#define AVR32_CAT_PDCA_ID_RX_ACOUNT        9
#define AVR32_CAT_PDCA_ID_RX_DMATSR        10
#define AVR32_CAT_PDCA_ID_TX               20
#define AVR32_CAT_CSA_1_PIN                1
#define AVR32_CAT_CSA_1_FUNCTION           3
#define AVR32_CAT_CSA_3_PIN                4
#define AVR32_CAT_CSA_3_FUNCTION           3
#define AVR32_CAT_CSA_4_PIN                6
#define AVR32_CAT_CSA_4_FUNCTION           3
#define AVR32_CAT_CSA_5_PIN                8
#define AVR32_CAT_CSA_5_FUNCTION           3
#define AVR32_CAT_CSA_6_PIN                10
#define AVR32_CAT_CSA_6_FUNCTION           3
#define AVR32_CAT_CSA_7_PIN                12
#define AVR32_CAT_CSA_7_FUNCTION           3
#define AVR32_CAT_CSA_8_PIN                14
#define AVR32_CAT_CSA_8_FUNCTION           3
#define AVR32_CAT_CSA_9_PIN                16
#define AVR32_CAT_CSA_9_FUNCTION           3
#define AVR32_CAT_CSA_10_PIN               18
#define AVR32_CAT_CSA_10_FUNCTION          3
#define AVR32_CAT_CSA_11_PIN               20
#define AVR32_CAT_CSA_11_FUNCTION          3
#define AVR32_CAT_CSA_12_PIN               22
#define AVR32_CAT_CSA_12_FUNCTION          3
#define AVR32_CAT_CSA_16_PIN               25
#define AVR32_CAT_CSA_16_FUNCTION          3
#define AVR32_CAT_CSA_0_PIN                27
#define AVR32_CAT_CSA_0_FUNCTION           3
#define AVR32_CAT_CSA_22_FUNCTION          3
#define AVR32_CAT_CSA_18_FUNCTION          3
#define AVR32_CAT_CSA_17_FUNCTION          3
#define AVR32_CAT_CSA_19_FUNCTION          3
#define AVR32_CAT_CSA_20_FUNCTION          3
#define AVR32_CAT_CSA_21_FUNCTION          3
#define AVR32_CAT_CSA_23_FUNCTION          3
#define AVR32_CAT_CSA_24_FUNCTION          3
#define AVR32_CAT_CSA_2_PIN                45
#define AVR32_CAT_CSA_2_FUNCTION           3
#define AVR32_CAT_CSA_13_PIN               46
#define AVR32_CAT_CSA_13_FUNCTION          3
#define AVR32_CAT_CSA_14_PIN               48
#define AVR32_CAT_CSA_14_FUNCTION          3
#define AVR32_CAT_CSA_15_PIN               50
#define AVR32_CAT_CSA_15_FUNCTION          3
#define AVR32_CAT_CSB_0_PIN                0
#define AVR32_CAT_CSB_0_FUNCTION           3
#define AVR32_CAT_CSB_1_PIN                2
#define AVR32_CAT_CSB_1_FUNCTION           3
#define AVR32_CAT_CSB_2_PIN                3
#define AVR32_CAT_CSB_2_FUNCTION           3
#define AVR32_CAT_CSB_3_PIN                5
#define AVR32_CAT_CSB_3_FUNCTION           3
#define AVR32_CAT_CSB_4_PIN                7
#define AVR32_CAT_CSB_4_FUNCTION           3
#define AVR32_CAT_CSB_5_PIN                9
#define AVR32_CAT_CSB_5_FUNCTION           3
#define AVR32_CAT_CSB_6_PIN                11
#define AVR32_CAT_CSB_6_FUNCTION           3
#define AVR32_CAT_CSB_7_PIN                13
#define AVR32_CAT_CSB_7_FUNCTION           3
#define AVR32_CAT_CSB_8_PIN                15
#define AVR32_CAT_CSB_8_FUNCTION           3
#define AVR32_CAT_CSB_9_PIN                17
#define AVR32_CAT_CSB_9_FUNCTION           3
#define AVR32_CAT_CSB_10_PIN               19
#define AVR32_CAT_CSB_10_FUNCTION          3
#define AVR32_CAT_CSB_11_PIN               21
#define AVR32_CAT_CSB_11_FUNCTION          3
#define AVR32_CAT_CSB_12_PIN               23
#define AVR32_CAT_CSB_12_FUNCTION          3
#define AVR32_CAT_CSB_15_PIN               24
#define AVR32_CAT_CSB_15_FUNCTION          3
#define AVR32_CAT_CSB_16_PIN               26
#define AVR32_CAT_CSB_16_FUNCTION          3
#define AVR32_CAT_CSB_21_FUNCTION          3
#define AVR32_CAT_CSB_18_FUNCTION          3
#define AVR32_CAT_CSB_17_FUNCTION          3
#define AVR32_CAT_CSB_19_FUNCTION          3
#define AVR32_CAT_CSB_20_FUNCTION          3
#define AVR32_CAT_CSB_22_FUNCTION          3
#define AVR32_CAT_CSB_23_FUNCTION          3
#define AVR32_CAT_CSB_24_FUNCTION          3
#define AVR32_CAT_CSB_13_PIN               47
#define AVR32_CAT_CSB_13_FUNCTION          3
#define AVR32_CAT_CSB_14_PIN               49
#define AVR32_CAT_CSB_14_FUNCTION          3
#define AVR32_CAT_SYNC_PIN                 45
#define AVR32_CAT_SYNC_FUNCTION            0
#define AVR32_CAT_SYNC_1_PIN               50
#define AVR32_CAT_SYNC_1_FUNCTION          1

#include "avr32/cat_400.h"


/* EIC */

/* EIC */
#define AVR32_EIC_ADDRESS                  0xFFFF2000
#define AVR32_EIC                          (*((volatile avr32_eic_t*)AVR32_EIC_ADDRESS))
#define AVR32_EIC_IRQ_1                   32
#define AVR32_EIC_IRQ_2                   33
#define AVR32_EIC_IRQ_3                   34
#define AVR32_EIC_IRQ_4                   35
#define AVR32_EIC_IRQ_5                   36
#define AVR32_EIC_IRQ_6                   37
#define AVR32_EIC_IRQ_7                   38
#define AVR32_EIC_IRQ_8                   39
#define AVR32_EIC_INT_MSB                  8
#define AVR32_EIC_SCAN_MSB                 0
#define AVR32_EIC_STD_NUM                  8
#define AVR32_EIC_EXTINT_8_PIN             5
#define AVR32_EIC_EXTINT_8_FUNCTION        0
#define AVR32_EIC_EXTINT_1_PIN             6
#define AVR32_EIC_EXTINT_1_FUNCTION        0
#define AVR32_EIC_EXTINT_0_0_PIN           13
#define AVR32_EIC_EXTINT_0_0_FUNCTION      0
#define AVR32_EIC_EXTINT_6_0_FUNCTION      0
#define AVR32_EIC_EXTINT_7_0_FUNCTION      0
#define AVR32_EIC_EXTINT_6_1_FUNCTION      1
#define AVR32_EIC_EXTINT_7_1_FUNCTION      1
#define AVR32_EIC_EXTINT_4_0_FUNCTION      1
#define AVR32_EIC_EXTINT_5_0_FUNCTION      1
#define AVR32_EIC_EXTINT_2_0_FUNCTION      1
#define AVR32_EIC_EXTINT_0_1_FUNCTION      1
#define AVR32_EIC_EXTINT_2_1_PIN           14
#define AVR32_EIC_EXTINT_2_1_FUNCTION      2
#define AVR32_EIC_EXTINT_3_PIN             23
#define AVR32_EIC_EXTINT_3_FUNCTION        2
#define AVR32_EIC_EXTINT_4_1_PIN           24
#define AVR32_EIC_EXTINT_4_1_FUNCTION      2
#define AVR32_EIC_EXTINT_5_1_PIN           25
#define AVR32_EIC_EXTINT_5_1_FUNCTION      2

#include "avr32/eic_302.h"


/* FLASHCDW */

/* FLASHCDW */
#define AVR32_FLASHCDW_BASE_ADDRESS	     ((unsigned char *)0x80000000)
#define AVR32_FLASHCDW_ADDRESS             0xFFFE1400
#define AVR32_FLASHCDW                     (*((volatile avr32_flashcdw_t*)AVR32_FLASHCDW_ADDRESS))
#define AVR32_FLASHCDW_IRQ                 128
#define AVR32_FLASHCDW_CALFUSE_NB          40
#define AVR32_FLASHCDW_FLASH_SIZE          131072
#define AVR32_FLASHCDW_FWS_0_MAX_FREQ        15000000
#define AVR32_FLASHCDW_FWS_1_MAX_FREQ        30000000
#define AVR32_FLASHCDW_HSEN_FWS_0_MAX_FREQ   25000000
#define AVR32_FLASHCDW_HSEN_FWS_1_MAX_FREQ   50000000
#define AVR32_FLASHCDW_PAGES_PR_REGION       64
#define AVR32_FLASHCDW_LOCKFUSE_NB         32
#define AVR32_FLASHCDW_PAGE_SIZE           256
#define AVR32_FLASHCDW_USER_PAGE           (*((volatile unsigned char*) AVR32_FLASHCDW_USER_PAGE_ADDRESS))
#define AVR32_FLASHCDW_USER_PAGE_ADDRESS   0x80800000
#define AVR32_FLASHCDW_USER_PAGE_SIZE      (AVR32_FLASHCDW_PAGE_SIZE)
#define AVR32_FLASHCDW_EXTCLK_PIN          3
#define AVR32_FLASHCDW_FLASH_OBS_0_PIN     3
#define AVR32_FLASHCDW_FLASH_OBS_1_PIN     4
#define AVR32_FLASHCDW_FLASH_OBS_2_PIN     5
#define AVR32_FLASHCDW_FLASH_OBS_3_PIN     6
#define AVR32_FLASHCDW_FLASH_OBS_4_PIN     9
#define AVR32_FLASHCDW_FLASH_OBS_5_PIN     10
#define AVR32_FLASHCDW_FLASH_OBS_6_PIN     11
#define AVR32_FLASHCDW_FLASH_OBS_7_PIN     12
#define AVR32_FLASHCDW_FLASH_OBS_8_PIN     13
#define AVR32_FLASHCDW_FLASH_OBS_9_PIN     14
#define AVR32_FLASHCDW_FLASH_OBS_10_PIN    15
#define AVR32_FLASHCDW_FLASH_OBS_11_PIN    16
#define AVR32_FLASHCDW_FLASH_OBS_12_PIN    17
#define AVR32_FLASHCDW_FLASH_OBS_13_PIN    20
#define AVR32_FLASHCDW_FLASH_OBS_14_PIN    21
#define AVR32_FLASHCDW_FLASH_OBS_15_PIN    22
#define AVR32_FLASHCDW_FLASH_OBS_16_PIN    23
#define AVR32_FLASHCDW_FLASH_OBS_17_PIN    24
#define AVR32_FLASHCDW_FLASH_OBS_18_PIN    25
#define AVR32_FLASHCDW_FLASH_OBS_19_PIN    26
#define AVR32_FLASHCDW_FLASH_OBS_20_PIN    27
#define AVR32_FLASHCDW_FLASH_OBS_21_PIN    49
#define AVR32_FLASHCDW_FLASH_OBS_22_PIN    50
#define AVR32_FLASHCDW_LATDEL_PIN          7
#define AVR32_FLASHCDW_LATDELCLK_PIN       8
#define AVR32_FLASHCDW_LATDELMATCH_PIN     45
#define AVR32_FLASHCDW_VMARGIN_PIN         27

#include "avr32/flashcdw_120.h"


/* FREQM */

/* FREQM */
#define AVR32_FREQM_ADDRESS                0xFFFF5C00
#define AVR32_FREQM                        (*((volatile avr32_freqm_t*)AVR32_FREQM_ADDRESS))
#define AVR32_FREQM_IRQ                    256
#define AVR32_FREQM_CPU                    0
#define AVR32_FREQM_CRIPEL                 9
#define AVR32_FREQM_DFLL0                  0
#define AVR32_FREQM_FLO                    0
#define AVR32_FREQM_GENCLK0                10
#define AVR32_FREQM_GENCLK1                11
#define AVR32_FREQM_GENCLK10               0
#define AVR32_FREQM_GENCLK2                12
#define AVR32_FREQM_GENCLK3                13
#define AVR32_FREQM_GENCLK4                14
#define AVR32_FREQM_GENCLK5                15
#define AVR32_FREQM_GENCLK6                16
#define AVR32_FREQM_GENCLK7                17
#define AVR32_FREQM_GENCLK8                18
#define AVR32_FREQM_GENCLK9                0
#define AVR32_FREQM_GENCLKDIV0             0
#define AVR32_FREQM_GENCLKDIV1             0
#define AVR32_FREQM_GENCLKDIV10            0
#define AVR32_FREQM_GENCLKDIV2             0
#define AVR32_FREQM_GENCLKDIV3             0
#define AVR32_FREQM_GENCLKDIV4             0
#define AVR32_FREQM_GENCLKDIV5             0
#define AVR32_FREQM_GENCLKDIV6             0
#define AVR32_FREQM_GENCLKDIV7             0
#define AVR32_FREQM_GENCLKDIV8             0
#define AVR32_FREQM_GENCLKDIV9             0
#define AVR32_FREQM_HSB                    1
#define AVR32_FREQM_NUM_CLK                20
#define AVR32_FREQM_NUM_REF_CLK            0
#define AVR32_FREQM_OSC0                   4
#define AVR32_FREQM_OSC1                   0
#define AVR32_FREQM_OSC2                   0
#define AVR32_FREQM_OSC3                   0
#define AVR32_FREQM_OSC32                  5
#define AVR32_FREQM_OSC4                   0
#define AVR32_FREQM_PBA                    2
#define AVR32_FREQM_PBB                    3
#define AVR32_FREQM_PBC                    0
#define AVR32_FREQM_PLL0                   7
#define AVR32_FREQM_PLL1                   8
#define AVR32_FREQM_PLL2                   0
#define AVR32_FREQM_PLL3                   0
#define AVR32_FREQM_RC120M                 0
#define AVR32_FREQM_RC120M_AW              0
#define AVR32_FREQM_RC32K                  0
#define AVR32_FREQM_RCOSC                  6
#define AVR32_FREQM_RCOSC8                 0
#define AVR32_FREQM_REFSEL_BITS            2
#define AVR32_FREQM_REF_GENCLK0            0
#define AVR32_FREQM_REF_GENCLK1            0
#define AVR32_FREQM_REF_GENCLK2            0
#define AVR32_FREQM_REF_GENCLK3            0
#define AVR32_FREQM_REF_GENCLK4            0
#define AVR32_FREQM_REF_GENCLK5            0
#define AVR32_FREQM_REF_GENCLK6            0
#define AVR32_FREQM_REF_OSC0               2
#define AVR32_FREQM_REF_OSC1               0
#define AVR32_FREQM_REF_OSC2               0
#define AVR32_FREQM_REF_OSC32              1
#define AVR32_FREQM_REF_RCOSC              0
#define AVR32_FREQM_REF_RCOSC8             0

#include "avr32/freqm_310.h"


/* GLOC */

/* GLOC */
#define AVR32_GLOC_ADDRESS                 0xFFFF6400
#define AVR32_GLOC                         (*((volatile avr32_gloc_t*)AVR32_GLOC_ADDRESS))
#define AVR32_GLOC_GCLK_NUM                0
#define AVR32_GLOC_LUTS                    4
#define AVR32_GLOC_IN_0_PIN                0
#define AVR32_GLOC_IN_0_FUNCTION           2
#define AVR32_GLOC_IN_1_PIN                1
#define AVR32_GLOC_IN_1_FUNCTION           2
#define AVR32_GLOC_IN_2_PIN                2
#define AVR32_GLOC_IN_2_FUNCTION           2
#define AVR32_GLOC_IN_5_PIN                3
#define AVR32_GLOC_IN_5_FUNCTION           2
#define AVR32_GLOC_IN_6_PIN                4
#define AVR32_GLOC_IN_6_FUNCTION           2
#define AVR32_GLOC_IN_7_PIN                6
#define AVR32_GLOC_IN_7_FUNCTION           2
#define AVR32_GLOC_IN_8_PIN                7
#define AVR32_GLOC_IN_8_FUNCTION           2
#define AVR32_GLOC_IN_9_PIN                8
#define AVR32_GLOC_IN_9_FUNCTION           2
#define AVR32_GLOC_IN_15_FUNCTION          2
#define AVR32_GLOC_IN_11_FUNCTION          2
#define AVR32_GLOC_IN_14_FUNCTION          2
#define AVR32_GLOC_IN_3_FUNCTION           2
#define AVR32_GLOC_IN_4_PIN                45
#define AVR32_GLOC_IN_4_FUNCTION           2
#define AVR32_GLOC_IN_12_PIN               47
#define AVR32_GLOC_IN_12_FUNCTION          2
#define AVR32_GLOC_IN_10_PIN               48
#define AVR32_GLOC_IN_10_FUNCTION          2
#define AVR32_GLOC_IN_13_PIN               49
#define AVR32_GLOC_IN_13_FUNCTION          2
#define AVR32_GLOC_OUT_1_PIN               5
#define AVR32_GLOC_OUT_1_FUNCTION          2
#define AVR32_GLOC_OUT_0_PIN               44
#define AVR32_GLOC_OUT_0_FUNCTION          2
#define AVR32_GLOC_OUT_2_PIN               46
#define AVR32_GLOC_OUT_2_FUNCTION          2
#define AVR32_GLOC_OUT_3_PIN               50
#define AVR32_GLOC_OUT_3_FUNCTION          2

#include "avr32/gloc_101.h"


/* GPIO */

/* GPIO */
#define AVR32_GPIO_ADDRESS                 0xFFFF2800
#define AVR32_GPIO                         (*((volatile avr32_gpio_t*)AVR32_GPIO_ADDRESS))
#define AVR32_GPIO_IRQ_0                  64
#define AVR32_GPIO_IRQ_1                  65
#define AVR32_GPIO_IRQ_2                  66
#define AVR32_GPIO_IRQ_3                  67
#define AVR32_GPIO_IRQ_4                  68
#define AVR32_GPIO_IRQ_5                  69
#define AVR32_GPIO_IRQ_6                  70
#define AVR32_GPIO_EVER_DEFAULT_VAL        "{NUMBER_OF_PINS{1'b0}}"
#define AVR32_GPIO_EVER_IMPLEMENTED        "{NUMBER_OF_PINS{1'b1}}"
#define AVR32_GPIO_IRQ_MSB                 6
#define AVR32_GPIO_MAX_IRQ_MSB             31
#define AVR32_GPIO_PADDR_BITS              10
#define AVR32_GPIO_PINS_MSB                35
#define AVR32_GPIO_IRQS_PER_GROUP          8
#define AVR32_GPIO_NUMBER_OF_PINS          36
#define AVR32_GPIO_PADDR_MSB               9
#define AVR32_GPIO_PDATA_MSB               31
#define AVR32_GPIO_PORT_LENGTH             2

#include "avr32/gpio_212.h"


/* HMATRIXB */

/* HMATRIXB */
#define AVR32_HMATRIXB_ADDRESS             0xFFFE1000
#define AVR32_HMATRIXB                     (*((volatile avr32_hmatrixb_t*)AVR32_HMATRIXB_ADDRESS))
#define AVR32_HMATRIXB_MASTER_CPU_DATA     0
#define AVR32_HMATRIXB_MASTER_CPU_INSN     1
#define AVR32_HMATRIXB_MASTER_CPU_SAB      2
#define AVR32_HMATRIXB_MASTER_NUM          5
#define AVR32_HMATRIXB_MASTER_PDCA         3
#define AVR32_HMATRIXB_MASTER_USBC_DMA     4
#define AVR32_HMATRIXB_SLAVE_FLASH         0
#define AVR32_HMATRIXB_SLAVE_NUM           4
#define AVR32_HMATRIXB_SLAVE_PBA           2
#define AVR32_HMATRIXB_SLAVE_PBB           3
#define AVR32_HMATRIXB_SLAVE_SRAM          1

#include "avr32/hmatrixb_130.h"


/* IISC */

/* IISC */
#define AVR32_IISC_ADDRESS                 0xFFFF4C00
#define AVR32_IISC                         (*((volatile avr32_iisc_t*)AVR32_IISC_ADDRESS))
#define AVR32_IISC_IRQ                     416
#define AVR32_IISC_GCLK_NUM                5
#define AVR32_IISC_PDCA_ID_RX              6
#define AVR32_IISC_PDCA_ID_RX_1            7
#define AVR32_IISC_PDCA_ID_TX              18
#define AVR32_IISC_PDCA_ID_TX_1            19
#define AVR32_IISC_IMCK_PIN                44
#define AVR32_IISC_IMCK_FUNCTION           1
#define AVR32_IISC_ISCK_PIN                27
#define AVR32_IISC_ISCK_FUNCTION           0
#define AVR32_IISC_ISDI_PIN                50
#define AVR32_IISC_ISDI_FUNCTION           0
#define AVR32_IISC_ISDO_PIN                49
#define AVR32_IISC_ISDO_FUNCTION           0
#define AVR32_IISC_IWS_PIN                 26
#define AVR32_IISC_IWS_FUNCTION            0

#include "avr32/iisc_100.h"


/* JTAG */

/* JTAG */
#define AVR32_JTAG_TCK_PIN                 44
#define AVR32_JTAG_TDI_PIN                 0
#define AVR32_JTAG_TDO_PIN                 1
#define AVR32_JTAG_TMS_PIN                 2



/* PDCA */

/* PDCA */
#define AVR32_PDCA_ADDRESS                 0xFFFF0000
#define AVR32_PDCA                         (*((volatile avr32_pdca_t*)AVR32_PDCA_ADDRESS))
#define AVR32_PDCA_IRQ_0                  96
#define AVR32_PDCA_IRQ_1                  97
#define AVR32_PDCA_IRQ_2                  98
#define AVR32_PDCA_IRQ_3                  99
#define AVR32_PDCA_IRQ_4                  100
#define AVR32_PDCA_IRQ_5                  101
#define AVR32_PDCA_IRQ_6                  102
#define AVR32_PDCA_CHANNEL_LENGTH          7
#define AVR32_PDCA_MON_CH0_IMPL            0
#define AVR32_PDCA_MON_CH1_IMPL            0
#define AVR32_PDCA_PID_USART0_RX            0
#define AVR32_PDCA_PID_USART1_RX            1
#define AVR32_PDCA_PID_USART2_RX            2
#define AVR32_PDCA_PID_SPI_RX               3
#define AVR32_PDCA_PID_TWIM_RX              4
#define AVR32_PDCA_PID_TWIS_RX              5
#define AVR32_PDCA_PID_I2SC_LEFT_RX         6
#define AVR32_PDCA_PID_I2SC_RIGHT_RX        7
#define AVR32_PDCA_PID_ADCIFD_RX            8
#define AVR32_PDCA_PID_CAT_ACOUNT           9
#define AVR32_PDCA_PID_CAT_DMATSR          10
#define AVR32_PDCA_PID_AW_RX               11
#define AVR32_PDCA_PID_USART0_TX           12
#define AVR32_PDCA_PID_USART1_TX           13
#define AVR32_PDCA_PID_USART2_TX           14
#define AVR32_PDCA_PID_SPI_TX              15
#define AVR32_PDCA_PID_TWIM_TX             16
#define AVR32_PDCA_PID_TWIS_TX             17
#define AVR32_PDCA_PID_I2SC_LEFT_TX        18
#define AVR32_PDCA_PID_I2SC_RIGHT_TX       19
#define AVR32_PDCA_PID_CAT_DMATSW          20
#define AVR32_PDCA_PID_AW_TX               21

#include "avr32/pdca_123.h"


/* PM */

/* PM */
#define AVR32_PM_ADDRESS                   0xFFFF1400
#define AVR32_PM                           (*((volatile avr32_pm_t*)AVR32_PM_ADDRESS))
#define AVR32_PM_IRQ                       41
#define AVR32_PM_CPU_MAX_FREQ              48000000
#define AVR32_PM_HSB_MAX_FREQ              48000000
#define AVR32_PM_PBA_MAX_FREQ              48000000
#define AVR32_PM_PBB_MAX_FREQ              48000000
#define AVR32_PM_CLK_APB_NUM               2
#define AVR32_PM_RSTM_N_PIN                45
#define AVR32_PM_TEST_RESET_IN_PIN         49
#define AVR32_PM_TEST_RESET_OEN_PIN        50
#define AVR32_PM_TEST_RESET_OUT_PIN        48

#include "avr32/pm_412.h"


/* PWMA */

/* PWMA */
#define AVR32_PWMA_ADDRESS                 0xFFFF4800
#define AVR32_PWMA                         (*((volatile avr32_pwma_t*)AVR32_PWMA_ADDRESS))
#define AVR32_PWMA_IRQ                     384
#define AVR32_PWMA_GCLK_NUM                4
#define AVR32_PWMA_CHANNELS_MSB            6
#define AVR32_PWMA_CH_SYNC_EVT             0
#define AVR32_PWMA_PWMA_EVT_IMPL_MASK      "7'b0000000"
#define AVR32_PWMA_NUM_CHANNELS            7
#define AVR32_PWMA_0_0_PIN                 7
#define AVR32_PWMA_0_0_FUNCTION            0
#define AVR32_PWMA_1_0_PIN                 8
#define AVR32_PWMA_1_0_FUNCTION            0
#define AVR32_PWMA_2_0_PIN                 21
#define AVR32_PWMA_2_0_FUNCTION            0
#define AVR32_PWMA_6_0_PIN                 22
#define AVR32_PWMA_6_0_FUNCTION            0
#define AVR32_PWMA_1_1_PIN                 0
#define AVR32_PWMA_1_1_FUNCTION            1
#define AVR32_PWMA_2_1_PIN                 1
#define AVR32_PWMA_2_1_FUNCTION            1
#define AVR32_PWMA_3_0_PIN                 2
#define AVR32_PWMA_3_0_FUNCTION            1
#define AVR32_PWMA_2_2_PIN                 13
#define AVR32_PWMA_2_2_FUNCTION            1
#define AVR32_PWMA_3_1_PIN                 14
#define AVR32_PWMA_3_1_FUNCTION            1
#define AVR32_PWMA_4_0_PIN                 15
#define AVR32_PWMA_4_0_FUNCTION            1
#define AVR32_PWMA_5_0_PIN                 18
#define AVR32_PWMA_5_0_FUNCTION            1
#define AVR32_PWMA_6_1_PIN                 19
#define AVR32_PWMA_6_1_FUNCTION            1
#define AVR32_PWMA_3_2_PIN                 25
#define AVR32_PWMA_3_2_FUNCTION            1
#define AVR32_PWMA_4_1_FUNCTION            1
#define AVR32_PWMA_5_1_FUNCTION            1
#define AVR32_PWMA_0_1_PIN                 11
#define AVR32_PWMA_0_1_FUNCTION            2
#define AVR32_PWMA_1_2_PIN                 12
#define AVR32_PWMA_1_2_FUNCTION            2
#define AVR32_PWMA_4_2_PIN                 16
#define AVR32_PWMA_4_2_FUNCTION            2
#define AVR32_PWMA_6_2_FUNCTION            2
#define AVR32_PWMA_5_2_FUNCTION            2

#include "avr32/pwma_200.h"


/* SCAN */

/* SCAN */
#define AVR32_SCAN_CLOCKS_0_PIN            24
#define AVR32_SCAN_CLOCKS_1_PIN            44
#define AVR32_SCAN_ENABLE_FROM_PAD_PIN      23
#define AVR32_SCAN_IN_0_PIN                0
#define AVR32_SCAN_IN_1_PIN                1
#define AVR32_SCAN_IN_2_PIN                2
#define AVR32_SCAN_IN_3_PIN                3
#define AVR32_SCAN_IN_4_PIN                4
#define AVR32_SCAN_IN_5_PIN                5
#define AVR32_SCAN_IN_6_PIN                6
#define AVR32_SCAN_IN_7_PIN                7
#define AVR32_SCAN_IN_8_PIN                8
#define AVR32_SCAN_IN_9_PIN                9
#define AVR32_SCAN_IN_10_PIN               20
#define AVR32_SCAN_OUT_0_PIN               10
#define AVR32_SCAN_OUT_1_PIN               13
#define AVR32_SCAN_OUT_2_PIN               14
#define AVR32_SCAN_OUT_3_PIN               15
#define AVR32_SCAN_OUT_4_PIN               16
#define AVR32_SCAN_OUT_5_PIN               17
#define AVR32_SCAN_OUT_6_PIN               21
#define AVR32_SCAN_OUT_7_PIN               22
#define AVR32_SCAN_OUT_8_PIN               25
#define AVR32_SCAN_OUT_9_PIN               49
#define AVR32_SCAN_OUT_10_PIN              50
#define AVR32_SCAN_OUTPUT_PIN              11
#define AVR32_SCAN_OUTPUT_1_PIN            12
#define AVR32_SCAN_OUTPUT_2_PIN            18
#define AVR32_SCAN_OUTPUT_3_PIN            19
#define AVR32_SCAN_OUTPUT_4_PIN            26
#define AVR32_SCAN_OUTPUT_5_PIN            27
#define AVR32_SCAN_OUTPUT_6_PIN            46
#define AVR32_SCAN_OUTPUT_7_PIN            47
#define AVR32_SCAN_OUTPUT_9_PIN            48



/* SCIF */

/* SCIF */
#define AVR32_SCIF_ADDRESS                 0xFFFF5800
#define AVR32_SCIF                         (*((volatile avr32_scif_t*)AVR32_SCIF_ADDRESS))
#define AVR32_SCIF_IRQ                     608
#define AVR32_SCIF_GCLK_EXT_NUM            3
#define AVR32_SCIF_GCLK_NUM                9
#define AVR32_SCIF_GCLK_NUM_EXTCLK         2:0
#define AVR32_SCIF_GCLK_NUM_STILO          7
#define AVR32_SCIF_GC_DIV_CLOCK            1
#define AVR32_SCIF_GC_NO_DIV_CLOCK         0
#define AVR32_SCIF_GC_USES_CLK_32          1
#define AVR32_SCIF_GC_USES_CLK_CPU         5
#define AVR32_SCIF_GC_USES_CLK_HSB         6
#define AVR32_SCIF_GC_USES_CLK_PBA         7
#define AVR32_SCIF_GC_USES_CLK_PBB         8
#define AVR32_SCIF_GC_USES_CLK_PBC         0
#define AVR32_SCIF_GC_USES_CLK_PBD         0
#define AVR32_SCIF_GC_USES_CLK_SLOW        0
#define AVR32_SCIF_GC_USES_CRIPOSC         10
#define AVR32_SCIF_GC_USES_GCLKPRESC_FP    12
#define AVR32_SCIF_GC_USES_GCLKPRESC_HRP   11
#define AVR32_SCIF_GC_USES_OSC0            2
#define AVR32_SCIF_GC_USES_OSC1            0
#define AVR32_SCIF_GC_USES_OSC2            0
#define AVR32_SCIF_GC_USES_OSC3            0
#define AVR32_SCIF_GC_USES_OSC4            0
#define AVR32_SCIF_GC_USES_PLL0            3
#define AVR32_SCIF_GC_USES_PLL1            4
#define AVR32_SCIF_GC_USES_PLL2            0
#define AVR32_SCIF_GC_USES_PLL3            0
#define AVR32_SCIF_GC_USES_PLL4            0
#define AVR32_SCIF_GC_USES_RC120M          9
#define AVR32_SCIF_GC_USES_RCOSC8          0
#define AVR32_SCIF_GC_USES_STILO           10
#define AVR32_SCIF_GPLP_NUM                2
#define AVR32_SCIF_OSC_NUM                 1
#define AVR32_SCIF_PLL_MSB                 1
#define AVR32_SCIF_PLL_NUM                 2
#define AVR32_SCIF_DN_1_PIN                5
#define AVR32_SCIF_DN_0_PIN                13
#define AVR32_SCIF_FDIV_1_PIN              7
#define AVR32_SCIF_FDIV_0_PIN              15
#define AVR32_SCIF_FDIV_TEST_1_PIN         8
#define AVR32_SCIF_FDIV_TEST_0_PIN         16
#define AVR32_SCIF_GCLK_0_PIN              3
#define AVR32_SCIF_GCLK_0_FUNCTION         1
#define AVR32_SCIF_GCLK_1_PIN              4
#define AVR32_SCIF_GCLK_1_FUNCTION         1
#define AVR32_SCIF_GCLK_2_0_PIN            45
#define AVR32_SCIF_GCLK_2_0_FUNCTION       1
#define AVR32_SCIF_GCLK_2_1_FUNCTION       2
#define AVR32_SCIF_LOCK_1_PIN              4
#define AVR32_SCIF_LOCK_0_PIN              10
#define AVR32_SCIF_PLLCLK_1_PIN            3
#define AVR32_SCIF_PLLCLK_0_PIN            9
#define AVR32_SCIF_UP_1_PIN                6
#define AVR32_SCIF_UP_0_PIN                14
#define AVR32_SCIF_XIN0_PIN                18
#define AVR32_SCIF_XIN32_PIN               11
#define AVR32_SCIF_XOUT0_PIN               19
#define AVR32_SCIF_XOUT32_PIN              12

#include "avr32/scif_1022.h"


/* SPI */

/* SPI */
#define AVR32_SPI_ADDRESS                  0xFFFF3C00
#define AVR32_SPI                          (*((volatile avr32_spi_t*)AVR32_SPI_ADDRESS))
#define AVR32_SPI_IRQ                      288
#define AVR32_SPI_CS_MSB                   3
#define AVR32_SPI_PDCA_ID_RX               3
#define AVR32_SPI_PDCA_ID_TX               15
#define AVR32_SPI_MISO_PIN                 0
#define AVR32_SPI_MISO_FUNCTION            0
#define AVR32_SPI_MISO_1_PIN               25
#define AVR32_SPI_MISO_1_FUNCTION          0
#define AVR32_SPI_MISO_2_PIN               18
#define AVR32_SPI_MISO_2_FUNCTION          2
#define AVR32_SPI_MISO_3_PIN               28
#define AVR32_SPI_MISO_3_FUNCTION          2
#define AVR32_SPI_MOSI_PIN                 1
#define AVR32_SPI_MOSI_FUNCTION            0
#define AVR32_SPI_MOSI_1_PIN               14
#define AVR32_SPI_MOSI_1_FUNCTION          0
#define AVR32_SPI_MOSI_2_PIN               19
#define AVR32_SPI_MOSI_2_FUNCTION          2
#define AVR32_SPI_MOSI_3_PIN               29
#define AVR32_SPI_MOSI_3_FUNCTION          2
#define AVR32_SPI_NPCS_0_0_PIN             16
#define AVR32_SPI_NPCS_0_0_FUNCTION        0
#define AVR32_SPI_NPCS_1_0_PIN             17
#define AVR32_SPI_NPCS_1_0_FUNCTION        0
#define AVR32_SPI_NPCS_0_1_PIN             44
#define AVR32_SPI_NPCS_0_1_FUNCTION        0
#define AVR32_SPI_NPCS_2_0_PIN             9
#define AVR32_SPI_NPCS_2_0_FUNCTION        1
#define AVR32_SPI_NPCS_3_0_PIN             10
#define AVR32_SPI_NPCS_3_0_FUNCTION        1
#define AVR32_SPI_NPCS_1_1_PIN             23
#define AVR32_SPI_NPCS_1_1_FUNCTION        1
#define AVR32_SPI_NPCS_0_2_PIN             24
#define AVR32_SPI_NPCS_0_2_FUNCTION        1
#define AVR32_SPI_NPCS_3_1_FUNCTION        1
#define AVR32_SPI_NPCS_2_1_FUNCTION        1
#define AVR32_SPI_SCK_PIN                  2
#define AVR32_SPI_SCK_FUNCTION             0
#define AVR32_SPI_SCK_1_PIN                15
#define AVR32_SPI_SCK_1_FUNCTION           0
#define AVR32_SPI_SCK_2_PIN                17
#define AVR32_SPI_SCK_2_FUNCTION           2

#include "avr32/spi_211.h"


/* TC */

/* TC */
#define AVR32_TC_ADDRESS                   0xFFFF5000
#define AVR32_TC                           (*((volatile avr32_tc_t*)AVR32_TC_ADDRESS))
#define AVR32_TC_IRQ0                      448
#define AVR32_TC_IRQ1                      449
#define AVR32_TC_IRQ2                      450
#define AVR32_TC_CLK_DIV1                  clk_32
#define AVR32_TC_CLK_DIV2                  2
#define AVR32_TC_CLK_DIV3                  8
#define AVR32_TC_CLK_DIV4                  32
#define AVR32_TC_CLK_DIV5                  128
#define AVR32_TC_A0_PIN                    26
#define AVR32_TC_A0_FUNCTION               2
#define AVR32_TC_A1_PIN                    21
#define AVR32_TC_A1_FUNCTION               1
#define AVR32_TC_A2_PIN                    11
#define AVR32_TC_A2_FUNCTION               1
#define AVR32_TC_B0_PIN                    27
#define AVR32_TC_B0_FUNCTION               2
#define AVR32_TC_B1_PIN                    22
#define AVR32_TC_B1_FUNCTION               1
#define AVR32_TC_B2_PIN                    12
#define AVR32_TC_B2_FUNCTION               1
#define AVR32_TC_CLK0_PIN                  20
#define AVR32_TC_CLK0_FUNCTION             1
#define AVR32_TC_CLK1_PIN                  16
#define AVR32_TC_CLK1_FUNCTION             1
#define AVR32_TC_CLK2_PIN                  17
#define AVR32_TC_CLK2_FUNCTION             1

#include "avr32/tc_2231.h"


/* TWIM */

/* TWIM */
#define AVR32_TWIM_ADDRESS                 0xFFFF4000
#define AVR32_TWIM                         (*((volatile avr32_twim_t*)AVR32_TWIM_ADDRESS))
#define AVR32_TWIM_IRQ                     320
#define AVR32_TWIM_PDCA_ID_RX              4
#define AVR32_TWIM_PDCA_ID_TX              16

#include "avr32/twim_110.h"


/* TWIMS */

/* TWIMS */
#define AVR32_TWIMS_TWCK_PIN               9
#define AVR32_TWIMS_TWCK_FUNCTION          0
#define AVR32_TWIMS_TWCK_PIN               9
#define AVR32_TWIMS_TWCK_INPUT_TEST_PIN    5
#define AVR32_TWIMS_TWCK_OUTPUT_TEST_PIN   6
#define AVR32_TWIMS_TWD_PIN                10
#define AVR32_TWIMS_TWD_FUNCTION           0
#define AVR32_TWIMS_TWD_PIN                10
#define AVR32_TWIMS_TWD_INPUT_TEST_PIN     3
#define AVR32_TWIMS_TWD_OUTPUT_TEST_PIN    4



/* TWIS */

/* TWIS */
#define AVR32_TWIS0_ADDRESS                 0xFFFF4400
#define AVR32_TWIS0                         (*((volatile avr32_twis_t*)AVR32_TWIS_ADDRESS))
#define AVR32_TWIS0_IRQ                     352
#define AVR32_TWIS0_PDCA_ID_RX              5
#define AVR32_TWIS0_PDCA_ID_TX              17

#include "avr32/twis_120.h"


/* USART */

/* USART0 */
#define AVR32_USART0_ADDRESS               0xFFFF3000
#define AVR32_USART0                       (*((volatile avr32_usart_t*)AVR32_USART0_ADDRESS))
#define AVR32_USART0_IRQ                   160
#define AVR32_USART0_CLK_DIV               8
#define AVR32_USART0_PDCA_ID_RX            0
#define AVR32_USART0_PDCA_ID_TX            12
#define AVR32_USART0_CLK_PIN               13
#define AVR32_USART0_CLK_FUNCTION          2
#define AVR32_USART0_CTS_PIN               12
#define AVR32_USART0_CTS_FUNCTION          0
#define AVR32_USART0_CTS_1_PIN             48
#define AVR32_USART0_CTS_1_FUNCTION        1
#define AVR32_USART0_RTS_PIN               11
#define AVR32_USART0_RTS_FUNCTION          0
#define AVR32_USART0_RTS_1_PIN             49
#define AVR32_USART0_RTS_1_FUNCTION        1
#define AVR32_USART0_RXD_PIN               18
#define AVR32_USART0_RXD_FUNCTION          0
#define AVR32_USART0_RXD_1_PIN             46
#define AVR32_USART0_RXD_1_FUNCTION        1
#define AVR32_USART0_TXD_PIN               19
#define AVR32_USART0_TXD_FUNCTION          0
#define AVR32_USART0_TXD_1_PIN             47
#define AVR32_USART0_TXD_1_FUNCTION        1


/* USART1 */
#define AVR32_USART1_ADDRESS               0xFFFF3400
#define AVR32_USART1                       (*((volatile avr32_usart_t*)AVR32_USART1_ADDRESS))
#define AVR32_USART1_IRQ                   192
#define AVR32_USART1_CLK_DIV               8
#define AVR32_USART1_PDCA_ID_RX            1
#define AVR32_USART1_PDCA_ID_TX            13
#define AVR32_USART1_CLK_PIN               20
#define AVR32_USART1_CLK_FUNCTION          0
#define AVR32_USART1_CTS_PIN               9
#define AVR32_USART1_CTS_FUNCTION          2
#define AVR32_USART1_RTS_PIN               10
#define AVR32_USART1_RTS_FUNCTION          2
#define AVR32_USART1_RXD_PIN               24
#define AVR32_USART1_RXD_FUNCTION          0
#define AVR32_USART1_TXD_PIN               23
#define AVR32_USART1_TXD_FUNCTION          0


/* USART2 */
#define AVR32_USART2_ADDRESS               0xFFFF3800
#define AVR32_USART2                       (*((volatile avr32_usart_t*)AVR32_USART2_ADDRESS))
#define AVR32_USART2_IRQ                   224
#define AVR32_USART2_CLK_DIV               8
#define AVR32_USART2_PDCA_ID_RX            2
#define AVR32_USART2_PDCA_ID_TX            14
#define AVR32_USART2_CLK_PIN               15
#define AVR32_USART2_CLK_FUNCTION          2
#define AVR32_USART2_RXD_PIN               27
#define AVR32_USART2_RXD_FUNCTION          1
#define AVR32_USART2_RXD_1_PIN             20
#define AVR32_USART2_RXD_1_FUNCTION        2
#define AVR32_USART2_TXD_PIN               26
#define AVR32_USART2_TXD_FUNCTION          1
#define AVR32_USART2_TXD_1_PIN             21
#define AVR32_USART2_TXD_1_FUNCTION        2

#include "avr32/usart_440.h"


/* USBC */

/* USBC */
#define AVR32_USBC_ADDRESS                 0xFFFE0000
#define AVR32_USBC                         (*((volatile avr32_usbc_t*)AVR32_USBC_ADDRESS))
#define AVR32_USBC_IRQ                     544
#define AVR32_USBC_EPT_NBR                 7
#define AVR32_USBC_GCLK_NUM                3
#define AVR32_USBC_HS_IMPLEMENTED          0
#define AVR32_USBC_OTG_IMPLEMENTED         0
#define AVR32_USBC_VBUS_MONITORING         0
#define AVR32_USBC_DM_PIN                  47
#define AVR32_USBC_DM_FUNCTION             0
#define AVR32_USBC_DM_PIN                  47
#define AVR32_USBC_DP_PIN                  46
#define AVR32_USBC_DP_FUNCTION             0
#define AVR32_USBC_DP_PIN                  46
#define AVR32_USBC_ENABLE_TEST_PIN         4
#define AVR32_USBC_EOPN_TEST_PIN           5
#define AVR32_USBC_FS_TEST_PIN             6
#define AVR32_USBC_OEN_TEST_PIN            7
#define AVR32_USBC_ONN_TEST_PIN            8
#define AVR32_USBC_PDONDM_TEST_PIN         14
#define AVR32_USBC_PDONDP_TEST_PIN         16
#define AVR32_USBC_PUIDLE_TEST_PIN         17
#define AVR32_USBC_PUON_TEST_PIN           45
#define AVR32_USBC_RXDM_TEST_PIN           24
#define AVR32_USBC_RXDP_TEST_PIN           20
#define AVR32_USBC_RXD_TEST_PIN            21
#define AVR32_USBC_TXD_TEST_PIN            23
#define AVR32_USBC_VBUS_PIN                48
#define AVR32_USBC_VBUS_FUNCTION           0

#include "avr32/usbc_200.h"


/* WDT */

/* WDT */
#define AVR32_WDT_ADDRESS                  0xFFFF1C00
#define AVR32_WDT                          (*((volatile avr32_wdt_t*)AVR32_WDT_ADDRESS))

#include "avr32/wdt_410.h"

/* GPIO_LOCAL */

/* GPIO_LOCAL */
#define AVR32_GPIO_LOCAL_ADDRESS           0x40000000
#define AVR32_GPIO_LOCAL                   (*((volatile avr32_gpio_local_t*)AVR32_GPIO_LOCAL_ADDRESS))

#include "avr32/gpio_local_100.h"

/* PAD->GPIO bits mapping */
#define AVR32_PIN_PA00   0
#define AVR32_PIN_PA01   1
#define AVR32_PIN_PA02   2
#define AVR32_PIN_PA03   3
#define AVR32_PIN_PA04   4
#define AVR32_PIN_PA05   5
#define AVR32_PIN_PA06   6
#define AVR32_PIN_PA07   7
#define AVR32_PIN_PA08   8
#define AVR32_PIN_PA09   9
#define AVR32_PIN_PA10   10
#define AVR32_PIN_PA11   11
#define AVR32_PIN_PA12   12
#define AVR32_PIN_PA13   13
#define AVR32_PIN_PA14   14
#define AVR32_PIN_PA15   15
#define AVR32_PIN_PA16   16
#define AVR32_PIN_PA17   17
#define AVR32_PIN_PA18   18
#define AVR32_PIN_PA19   19
#define AVR32_PIN_PA20   20
#define AVR32_PIN_PA21   21
#define AVR32_PIN_PA22   22
#define AVR32_PIN_PA23   23
#define AVR32_PIN_PA24   24
#define AVR32_PIN_PA25   25
#define AVR32_PIN_PA26   26
#define AVR32_PIN_PA27   27
#define AVR32_PIN_PB12   44
#define AVR32_PIN_PB13   45
#define AVR32_PIN_PB14   46
#define AVR32_PIN_PB15   47
#define AVR32_PIN_PB16   48
#define AVR32_PIN_PB17   49
#define AVR32_PIN_PB18   50


/* #ifndef AVR32_UC128D4_H_INCLUDED */
#endif
