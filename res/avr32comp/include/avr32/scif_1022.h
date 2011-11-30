/*****************************************************************************
 *
 * Copyright (C) 2010 Atmel Corporation
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
 * Model        : ATUC128D4
 * Revision     : $Revision: 83926 $
 * Checkin Date : $Date: 2010-04-27 15:13:30 +0200 (ti., 27 april 2010) $ 
 *
 ****************************************************************************/
#ifndef AVR32_SCIF_1022_H_INCLUDED
#define AVR32_SCIF_1022_H_INCLUDED

#include "avr32/abi.h"


/*
 Note to user:

 The following defines are always generated:
 - Register offset: AVR32_SCIF_<register>
 - Bitfield mask:   AVR32_SCIF_<register>_<bitfield>
 - Bitfield offset: AVR32_SCIF_<register>_<bitfield>_OFFSET
 - Bitfield size:   AVR32_SCIF_<register>_<bitfield>_SIZE
 - Bitfield values: AVR32_SCIF_<register>_<bitfield>_<value name>

 The following defines are generated if they don't cause ambiguities,
 i.e. the name is unique, or all values with that name are the same.
 - Bitfield mask:   AVR32_SCIF_<bitfield>
 - Bitfield offset: AVR32_SCIF_<bitfield>_OFFSET
 - Bitfield size:   AVR32_SCIF_<bitfield>_SIZE
 - Bitfield values: AVR32_SCIF_<bitfield>_<value name>
 - Bitfield values: AVR32_SCIF_<value name>

 All defines are sorted alphabetically.
*/


#define AVR32_SCIF_ACG                                               3
#define AVR32_SCIF_ACG_MASK                                 0x00000008
#define AVR32_SCIF_ACG_OFFSET                                        3
#define AVR32_SCIF_ACG_SIZE                                          1
#define AVR32_SCIF_ADDR                                              0
#define AVR32_SCIF_ADDR_MASK                                0x000003ff
#define AVR32_SCIF_ADDR_OFFSET                                       0
#define AVR32_SCIF_ADDR_SIZE                                        10
#define AVR32_SCIF_AE                                               31
#define AVR32_SCIF_AE_MASK                                  0x80000000
#define AVR32_SCIF_AE_OFFSET                                        31
#define AVR32_SCIF_AE_SIZE                                           1
#define AVR32_SCIF_BGCR                                     0x0000002c
#define AVR32_SCIF_BGCR_CALIB                                        0
#define AVR32_SCIF_BGCR_CALIB_MASK                          0x00000007
#define AVR32_SCIF_BGCR_CALIB_OFFSET                                 0
#define AVR32_SCIF_BGCR_CALIB_SIZE                                   3
#define AVR32_SCIF_BGCR_FCD                                         16
#define AVR32_SCIF_BGCR_FCD_MASK                            0x00010000
#define AVR32_SCIF_BGCR_FCD_OFFSET                                  16
#define AVR32_SCIF_BGCR_FCD_SIZE                                     1
#define AVR32_SCIF_BGCR_MASK                                0x80010007
#define AVR32_SCIF_BGCR_RESETVALUE                          0x00000000
#define AVR32_SCIF_BGCR_SFV                                         31
#define AVR32_SCIF_BGCR_SFV_MASK                            0x80000000
#define AVR32_SCIF_BGCR_SFV_OFFSET                                  31
#define AVR32_SCIF_BGCR_SFV_SIZE                                     1
#define AVR32_SCIF_BOD                                      0x00000028
#define AVR32_SCIF_BODDET                                            4
#define AVR32_SCIF_BODDET_MASK                              0x00000010
#define AVR32_SCIF_BODDET_OFFSET                                     4
#define AVR32_SCIF_BODDET_SIZE                                       1
#define AVR32_SCIF_BODVERSION                               0x000003dc
#define AVR32_SCIF_BODVERSION_MASK                          0x000f0fff
#define AVR32_SCIF_BODVERSION_RESETVALUE                    0x00000120
#define AVR32_SCIF_BODVERSION_VARIANT                               16
#define AVR32_SCIF_BODVERSION_VARIANT_MASK                  0x000f0000
#define AVR32_SCIF_BODVERSION_VARIANT_OFFSET                        16
#define AVR32_SCIF_BODVERSION_VARIANT_SIZE                           4
#define AVR32_SCIF_BODVERSION_VERSION                                0
#define AVR32_SCIF_BODVERSION_VERSION_MASK                  0x00000fff
#define AVR32_SCIF_BODVERSION_VERSION_OFFSET                         0
#define AVR32_SCIF_BODVERSION_VERSION_SIZE                          12
#define AVR32_SCIF_BOD_CTRL                                          8
#define AVR32_SCIF_BOD_CTRL_ENABLED                         0x00000001
#define AVR32_SCIF_BOD_CTRL_ENABLED_NORESET                 0x00000002
#define AVR32_SCIF_BOD_CTRL_MASK                            0x00000300
#define AVR32_SCIF_BOD_CTRL_OFF1                            0x00000000
#define AVR32_SCIF_BOD_CTRL_OFF2                            0x00000003
#define AVR32_SCIF_BOD_CTRL_OFFSET                                   8
#define AVR32_SCIF_BOD_CTRL_SIZE                                     2
#define AVR32_SCIF_BOD_FCD                                          16
#define AVR32_SCIF_BOD_FCD_MASK                             0x00010000
#define AVR32_SCIF_BOD_FCD_OFFSET                                   16
#define AVR32_SCIF_BOD_FCD_SIZE                                      1
#define AVR32_SCIF_BOD_HYST                                          6
#define AVR32_SCIF_BOD_HYST_MASK                            0x00000040
#define AVR32_SCIF_BOD_HYST_OFFSET                                   6
#define AVR32_SCIF_BOD_HYST_SIZE                                     1
#define AVR32_SCIF_BOD_LEVEL                                         0
#define AVR32_SCIF_BOD_LEVEL_MASK                           0x0000003f
#define AVR32_SCIF_BOD_LEVEL_OFFSET                                  0
#define AVR32_SCIF_BOD_LEVEL_SIZE                                    6
#define AVR32_SCIF_BOD_MASK                                 0x8001037f
#define AVR32_SCIF_BOD_RESETVALUE                           0x00000000
#define AVR32_SCIF_BOD_SFV                                          31
#define AVR32_SCIF_BOD_SFV_MASK                             0x80000000
#define AVR32_SCIF_BOD_SFV_OFFSET                                   31
#define AVR32_SCIF_BOD_SFV_SIZE                                      1
#define AVR32_SCIF_CALIB                                             0
#define AVR32_SCIF_CALIB_OFFSET                                      0
#define AVR32_SCIF_CEN                                               0
#define AVR32_SCIF_CEN_MASK                                 0x00000001
#define AVR32_SCIF_CEN_OFFSET                                        0
#define AVR32_SCIF_CEN_SIZE                                          1
#define AVR32_SCIF_CKSEL                                             1
#define AVR32_SCIF_CKSEL_MASK                               0x0000000e
#define AVR32_SCIF_CKSEL_OFFSET                                      1
#define AVR32_SCIF_CKSEL_SIZE                                        3
#define AVR32_SCIF_CMVERSION                                0x000003cc
#define AVR32_SCIF_CMVERSION_MASK                           0x000f0fff
#define AVR32_SCIF_CMVERSION_RESETVALUE                     0x00000100
#define AVR32_SCIF_CMVERSION_VARIANT                                16
#define AVR32_SCIF_CMVERSION_VARIANT_MASK                   0x000f0000
#define AVR32_SCIF_CMVERSION_VARIANT_OFFSET                         16
#define AVR32_SCIF_CMVERSION_VARIANT_SIZE                            4
#define AVR32_SCIF_CMVERSION_VERSION                                 0
#define AVR32_SCIF_CMVERSION_VERSION_MASK                   0x00000fff
#define AVR32_SCIF_CMVERSION_VERSION_OFFSET                          0
#define AVR32_SCIF_CMVERSION_VERSION_SIZE                           12
#define AVR32_SCIF_CRYSTAL                                  0x00000001
#define AVR32_SCIF_CRYSTAL_ACG                              0x00000001
#define AVR32_SCIF_CRYSTAL_NO_ACG                           0x00000002
#define AVR32_SCIF_CTRL                                              8
#define AVR32_SCIF_CTRL_ENABLED                             0x00000001
#define AVR32_SCIF_CTRL_ENABLED_NORESET                     0x00000002
#define AVR32_SCIF_CTRL_MASK                                0x00000300
#define AVR32_SCIF_CTRL_OFF1                                0x00000000
#define AVR32_SCIF_CTRL_OFF2                                0x00000003
#define AVR32_SCIF_CTRL_OFFSET                                       8
#define AVR32_SCIF_CTRL_SIZE                                         2
#define AVR32_SCIF_DIV                                              16
#define AVR32_SCIF_DIVEN                                             1
#define AVR32_SCIF_DIVEN_MASK                               0x00000002
#define AVR32_SCIF_DIVEN_OFFSET                                      1
#define AVR32_SCIF_DIVEN_SIZE                                        1
#define AVR32_SCIF_DIV_MASK                                 0x00ff0000
#define AVR32_SCIF_DIV_OFFSET                                       16
#define AVR32_SCIF_DIV_SIZE                                          8
#define AVR32_SCIF_DMD                                               9
#define AVR32_SCIF_DMD_MASK                                 0x00000200
#define AVR32_SCIF_DMD_OFFSET                                        9
#define AVR32_SCIF_DMD_SIZE                                          1
#define AVR32_SCIF_EN                                                0
#define AVR32_SCIF_ENABLED                                  0x00000001
#define AVR32_SCIF_ENABLED_NORESET                          0x00000002
#define AVR32_SCIF_EN_MASK                                  0x00000001
#define AVR32_SCIF_EN_OFFSET                                         0
#define AVR32_SCIF_EN_SIZE                                           1
#define AVR32_SCIF_EXT_CLOCK                                0x00000000
#define AVR32_SCIF_FCD                                              16
#define AVR32_SCIF_FCD_MASK                                 0x00010000
#define AVR32_SCIF_FCD_OFFSET                                       16
#define AVR32_SCIF_FCD_SIZE                                          1
#define AVR32_SCIF_FPCR                                     0x00000054
#define AVR32_SCIF_FPCR_CKSEL                                        1
#define AVR32_SCIF_FPCR_CKSEL_MASK                          0x0000000e
#define AVR32_SCIF_FPCR_CKSEL_OFFSET                                 1
#define AVR32_SCIF_FPCR_CKSEL_SIZE                                   3
#define AVR32_SCIF_FPCR_FPEN                                         0
#define AVR32_SCIF_FPCR_FPEN_MASK                           0x00000001
#define AVR32_SCIF_FPCR_FPEN_OFFSET                                  0
#define AVR32_SCIF_FPCR_FPEN_SIZE                                    1
#define AVR32_SCIF_FPCR_MASK                                0x0000000f
#define AVR32_SCIF_FPCR_RESETVALUE                          0x00000000
#define AVR32_SCIF_FPDIV                                    0x0000005c
#define AVR32_SCIF_FPDIV_FPDIV                                       0
#define AVR32_SCIF_FPDIV_FPDIV_MASK                         0x000fffff
#define AVR32_SCIF_FPDIV_FPDIV_OFFSET                                0
#define AVR32_SCIF_FPDIV_FPDIV_SIZE                                 20
#define AVR32_SCIF_FPDIV_MASK                               0x000fffff
#define AVR32_SCIF_FPDIV_OFFSET                                      0
#define AVR32_SCIF_FPDIV_RESETVALUE                         0x00000000
#define AVR32_SCIF_FPDIV_SIZE                                       20
#define AVR32_SCIF_FPEN                                              0
#define AVR32_SCIF_FPEN_MASK                                0x00000001
#define AVR32_SCIF_FPEN_OFFSET                                       0
#define AVR32_SCIF_FPEN_SIZE                                         1
#define AVR32_SCIF_FPMUL                                    0x00000058
#define AVR32_SCIF_FPMUL_FPMUL                                       0
#define AVR32_SCIF_FPMUL_FPMUL_MASK                         0x000fffff
#define AVR32_SCIF_FPMUL_FPMUL_OFFSET                                0
#define AVR32_SCIF_FPMUL_FPMUL_SIZE                                 20
#define AVR32_SCIF_FPMUL_MASK                               0x000fffff
#define AVR32_SCIF_FPMUL_OFFSET                                      0
#define AVR32_SCIF_FPMUL_RESETVALUE                         0x00000000
#define AVR32_SCIF_FPMUL_SIZE                                       20
#define AVR32_SCIF_GAIN                                              1
#define AVR32_SCIF_GAIN_MASK                                0x00000006
#define AVR32_SCIF_GAIN_OFFSET                                       1
#define AVR32_SCIF_GAIN_SIZE                                         2
#define AVR32_SCIF_GCCTRL                                   0x00000060
#define AVR32_SCIF_GCCTRL_CEN                                        0
#define AVR32_SCIF_GCCTRL_CEN_MASK                          0x00000001
#define AVR32_SCIF_GCCTRL_CEN_OFFSET                                 0
#define AVR32_SCIF_GCCTRL_CEN_SIZE                                   1
#define AVR32_SCIF_GCCTRL_DIV                                       16
#define AVR32_SCIF_GCCTRL_DIVEN                                      1
#define AVR32_SCIF_GCCTRL_DIVEN_MASK                        0x00000002
#define AVR32_SCIF_GCCTRL_DIVEN_OFFSET                               1
#define AVR32_SCIF_GCCTRL_DIVEN_SIZE                                 1
#define AVR32_SCIF_GCCTRL_DIV_MASK                          0x00ff0000
#define AVR32_SCIF_GCCTRL_DIV_OFFSET                                16
#define AVR32_SCIF_GCCTRL_DIV_SIZE                                   8
#define AVR32_SCIF_GCCTRL_MASK                              0x00ff0f03
#define AVR32_SCIF_GCCTRL_OSCSEL                                     8
#define AVR32_SCIF_GCCTRL_OSCSEL_MASK                       0x00000f00
#define AVR32_SCIF_GCCTRL_OSCSEL_OFFSET                              8
#define AVR32_SCIF_GCCTRL_OSCSEL_SIZE                                4
#define AVR32_SCIF_GCCTRL_RESETVALUE                        0x00000000
#define AVR32_SCIF_GCLKPRESCVERSION                         0x000003d0
#define AVR32_SCIF_GCLKPRESCVERSION_MASK                    0x000f0fff
#define AVR32_SCIF_GCLKPRESCVERSION_RESETVALUE              0x00000100
#define AVR32_SCIF_GCLKPRESCVERSION_VARIANT                         16
#define AVR32_SCIF_GCLKPRESCVERSION_VARIANT_MASK            0x000f0000
#define AVR32_SCIF_GCLKPRESCVERSION_VARIANT_OFFSET                  16
#define AVR32_SCIF_GCLKPRESCVERSION_VARIANT_SIZE                     4
#define AVR32_SCIF_GCLKPRESCVERSION_VERSION                          0
#define AVR32_SCIF_GCLKPRESCVERSION_VERSION_MASK            0x00000fff
#define AVR32_SCIF_GCLKPRESCVERSION_VERSION_OFFSET                   0
#define AVR32_SCIF_GCLKPRESCVERSION_VERSION_SIZE                    12
#define AVR32_SCIF_GCLKVERSION                              0x000003f8
#define AVR32_SCIF_GCLKVERSION_MASK                         0x000f0fff
#define AVR32_SCIF_GCLKVERSION_RESETVALUE                   0x00000101
#define AVR32_SCIF_GCLKVERSION_VARIANT                              16
#define AVR32_SCIF_GCLKVERSION_VARIANT_MASK                 0x000f0000
#define AVR32_SCIF_GCLKVERSION_VARIANT_OFFSET                       16
#define AVR32_SCIF_GCLKVERSION_VARIANT_SIZE                          4
#define AVR32_SCIF_GCLKVERSION_VERSION                               0
#define AVR32_SCIF_GCLKVERSION_VERSION_MASK                 0x00000fff
#define AVR32_SCIF_GCLKVERSION_VERSION_OFFSET                        0
#define AVR32_SCIF_GCLKVERSION_VERSION_SIZE                         12
#define AVR32_SCIF_GPLP                                     0x00000048
#define AVR32_SCIF_GPLPVERSION                              0x000003f4
#define AVR32_SCIF_GPLPVERSION_MASK                         0x000f0fff
#define AVR32_SCIF_GPLPVERSION_RESETVALUE                   0x00000200
#define AVR32_SCIF_GPLPVERSION_VARIANT                              16
#define AVR32_SCIF_GPLPVERSION_VARIANT_MASK                 0x000f0000
#define AVR32_SCIF_GPLPVERSION_VARIANT_OFFSET                       16
#define AVR32_SCIF_GPLPVERSION_VARIANT_SIZE                          4
#define AVR32_SCIF_GPLPVERSION_VERSION                               0
#define AVR32_SCIF_GPLPVERSION_VERSION_MASK                 0x00000fff
#define AVR32_SCIF_GPLPVERSION_VERSION_OFFSET                        0
#define AVR32_SCIF_GPLPVERSION_VERSION_SIZE                         12
#define AVR32_SCIF_GPLP_GPLP                                         0
#define AVR32_SCIF_GPLP_GPLP_MASK                           0xffffffff
#define AVR32_SCIF_GPLP_GPLP_OFFSET                                  0
#define AVR32_SCIF_GPLP_GPLP_SIZE                                   32
#define AVR32_SCIF_GPLP_MASK                                0xffffffff
#define AVR32_SCIF_GPLP_OFFSET                                       0
#define AVR32_SCIF_GPLP_RESETVALUE                          0x00000000
#define AVR32_SCIF_GPLP_SIZE                                        32
#define AVR32_SCIF_HRCOUNT                                           8
#define AVR32_SCIF_HRCOUNT_MASK                             0xffffff00
#define AVR32_SCIF_HRCOUNT_OFFSET                                    8
#define AVR32_SCIF_HRCOUNT_SIZE                                     24
#define AVR32_SCIF_HRPCR                                    0x00000050
#define AVR32_SCIF_HRPCR_CKSEL                                       1
#define AVR32_SCIF_HRPCR_CKSEL_MASK                         0x0000000e
#define AVR32_SCIF_HRPCR_CKSEL_OFFSET                                1
#define AVR32_SCIF_HRPCR_CKSEL_SIZE                                  3
#define AVR32_SCIF_HRPCR_HRCOUNT                                     8
#define AVR32_SCIF_HRPCR_HRCOUNT_MASK                       0xffffff00
#define AVR32_SCIF_HRPCR_HRCOUNT_OFFSET                              8
#define AVR32_SCIF_HRPCR_HRCOUNT_SIZE                               24
#define AVR32_SCIF_HRPCR_HRPEN                                       0
#define AVR32_SCIF_HRPCR_HRPEN_MASK                         0x00000001
#define AVR32_SCIF_HRPCR_HRPEN_OFFSET                                0
#define AVR32_SCIF_HRPCR_HRPEN_SIZE                                  1
#define AVR32_SCIF_HRPCR_MASK                               0xffffff0f
#define AVR32_SCIF_HRPCR_RESETVALUE                         0x00000000
#define AVR32_SCIF_HRPEN                                             0
#define AVR32_SCIF_HRPEN_MASK                               0x00000001
#define AVR32_SCIF_HRPEN_OFFSET                                      0
#define AVR32_SCIF_HRPEN_SIZE                                        1
#define AVR32_SCIF_HYST                                              6
#define AVR32_SCIF_HYST_MASK                                0x00000040
#define AVR32_SCIF_HYST_OFFSET                                       6
#define AVR32_SCIF_HYST_SIZE                                         1
#define AVR32_SCIF_ICR                                      0x00000010
#define AVR32_SCIF_ICR_AE                                           31
#define AVR32_SCIF_ICR_AE_MASK                              0x80000000
#define AVR32_SCIF_ICR_AE_OFFSET                                    31
#define AVR32_SCIF_ICR_AE_SIZE                                       1
#define AVR32_SCIF_ICR_BODDET                                        4
#define AVR32_SCIF_ICR_BODDET_MASK                          0x00000010
#define AVR32_SCIF_ICR_BODDET_OFFSET                                 4
#define AVR32_SCIF_ICR_BODDET_SIZE                                   1
#define AVR32_SCIF_ICR_MASK                                 0x8000007f
#define AVR32_SCIF_ICR_OSC0RDY                                       0
#define AVR32_SCIF_ICR_OSC0RDY_MASK                         0x00000001
#define AVR32_SCIF_ICR_OSC0RDY_OFFSET                                0
#define AVR32_SCIF_ICR_OSC0RDY_SIZE                                  1
#define AVR32_SCIF_ICR_OSC32RDY                                      1
#define AVR32_SCIF_ICR_OSC32RDY_MASK                        0x00000002
#define AVR32_SCIF_ICR_OSC32RDY_OFFSET                               1
#define AVR32_SCIF_ICR_OSC32RDY_SIZE                                 1
#define AVR32_SCIF_ICR_PLL0_LOCK                                     2
#define AVR32_SCIF_ICR_PLL0_LOCKLOST                                 5
#define AVR32_SCIF_ICR_PLL0_LOCKLOST_MASK                   0x00000020
#define AVR32_SCIF_ICR_PLL0_LOCKLOST_OFFSET                          5
#define AVR32_SCIF_ICR_PLL0_LOCKLOST_SIZE                            1
#define AVR32_SCIF_ICR_PLL0_LOCK_MASK                       0x00000004
#define AVR32_SCIF_ICR_PLL0_LOCK_OFFSET                              2
#define AVR32_SCIF_ICR_PLL0_LOCK_SIZE                                1
#define AVR32_SCIF_ICR_PLL1_LOCK                                     3
#define AVR32_SCIF_ICR_PLL1_LOCKLOST                                 6
#define AVR32_SCIF_ICR_PLL1_LOCKLOST_MASK                   0x00000040
#define AVR32_SCIF_ICR_PLL1_LOCKLOST_OFFSET                          6
#define AVR32_SCIF_ICR_PLL1_LOCKLOST_SIZE                            1
#define AVR32_SCIF_ICR_PLL1_LOCK_MASK                       0x00000008
#define AVR32_SCIF_ICR_PLL1_LOCK_OFFSET                              3
#define AVR32_SCIF_ICR_PLL1_LOCK_SIZE                                1
#define AVR32_SCIF_ICR_RESETVALUE                           0x00000000
#define AVR32_SCIF_IDR                                      0x00000004
#define AVR32_SCIF_IDR_AE                                           31
#define AVR32_SCIF_IDR_AE_MASK                              0x80000000
#define AVR32_SCIF_IDR_AE_OFFSET                                    31
#define AVR32_SCIF_IDR_AE_SIZE                                       1
#define AVR32_SCIF_IDR_BODDET                                        4
#define AVR32_SCIF_IDR_BODDET_MASK                          0x00000010
#define AVR32_SCIF_IDR_BODDET_OFFSET                                 4
#define AVR32_SCIF_IDR_BODDET_SIZE                                   1
#define AVR32_SCIF_IDR_MASK                                 0x8000007f
#define AVR32_SCIF_IDR_OSC0RDY                                       0
#define AVR32_SCIF_IDR_OSC0RDY_MASK                         0x00000001
#define AVR32_SCIF_IDR_OSC0RDY_OFFSET                                0
#define AVR32_SCIF_IDR_OSC0RDY_SIZE                                  1
#define AVR32_SCIF_IDR_OSC32RDY                                      1
#define AVR32_SCIF_IDR_OSC32RDY_MASK                        0x00000002
#define AVR32_SCIF_IDR_OSC32RDY_OFFSET                               1
#define AVR32_SCIF_IDR_OSC32RDY_SIZE                                 1
#define AVR32_SCIF_IDR_PLL0_LOCK                                     2
#define AVR32_SCIF_IDR_PLL0_LOCKLOST                                 5
#define AVR32_SCIF_IDR_PLL0_LOCKLOST_MASK                   0x00000020
#define AVR32_SCIF_IDR_PLL0_LOCKLOST_OFFSET                          5
#define AVR32_SCIF_IDR_PLL0_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IDR_PLL0_LOCK_MASK                       0x00000004
#define AVR32_SCIF_IDR_PLL0_LOCK_OFFSET                              2
#define AVR32_SCIF_IDR_PLL0_LOCK_SIZE                                1
#define AVR32_SCIF_IDR_PLL1_LOCK                                     3
#define AVR32_SCIF_IDR_PLL1_LOCKLOST                                 6
#define AVR32_SCIF_IDR_PLL1_LOCKLOST_MASK                   0x00000040
#define AVR32_SCIF_IDR_PLL1_LOCKLOST_OFFSET                          6
#define AVR32_SCIF_IDR_PLL1_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IDR_PLL1_LOCK_MASK                       0x00000008
#define AVR32_SCIF_IDR_PLL1_LOCK_OFFSET                              3
#define AVR32_SCIF_IDR_PLL1_LOCK_SIZE                                1
#define AVR32_SCIF_IDR_RESETVALUE                           0x00000000
#define AVR32_SCIF_IER                                      0x00000000
#define AVR32_SCIF_IER_AE                                           31
#define AVR32_SCIF_IER_AE_MASK                              0x80000000
#define AVR32_SCIF_IER_AE_OFFSET                                    31
#define AVR32_SCIF_IER_AE_SIZE                                       1
#define AVR32_SCIF_IER_BODDET                                        4
#define AVR32_SCIF_IER_BODDET_MASK                          0x00000010
#define AVR32_SCIF_IER_BODDET_OFFSET                                 4
#define AVR32_SCIF_IER_BODDET_SIZE                                   1
#define AVR32_SCIF_IER_MASK                                 0x8000007f
#define AVR32_SCIF_IER_OSC0RDY                                       0
#define AVR32_SCIF_IER_OSC0RDY_MASK                         0x00000001
#define AVR32_SCIF_IER_OSC0RDY_OFFSET                                0
#define AVR32_SCIF_IER_OSC0RDY_SIZE                                  1
#define AVR32_SCIF_IER_OSC32RDY                                      1
#define AVR32_SCIF_IER_OSC32RDY_MASK                        0x00000002
#define AVR32_SCIF_IER_OSC32RDY_OFFSET                               1
#define AVR32_SCIF_IER_OSC32RDY_SIZE                                 1
#define AVR32_SCIF_IER_PLL0_LOCK                                     2
#define AVR32_SCIF_IER_PLL0_LOCKLOST                                 5
#define AVR32_SCIF_IER_PLL0_LOCKLOST_MASK                   0x00000020
#define AVR32_SCIF_IER_PLL0_LOCKLOST_OFFSET                          5
#define AVR32_SCIF_IER_PLL0_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IER_PLL0_LOCK_MASK                       0x00000004
#define AVR32_SCIF_IER_PLL0_LOCK_OFFSET                              2
#define AVR32_SCIF_IER_PLL0_LOCK_SIZE                                1
#define AVR32_SCIF_IER_PLL1_LOCK                                     3
#define AVR32_SCIF_IER_PLL1_LOCKLOST                                 6
#define AVR32_SCIF_IER_PLL1_LOCKLOST_MASK                   0x00000040
#define AVR32_SCIF_IER_PLL1_LOCKLOST_OFFSET                          6
#define AVR32_SCIF_IER_PLL1_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IER_PLL1_LOCK_MASK                       0x00000008
#define AVR32_SCIF_IER_PLL1_LOCK_OFFSET                              3
#define AVR32_SCIF_IER_PLL1_LOCK_SIZE                                1
#define AVR32_SCIF_IER_RESETVALUE                           0x00000000
#define AVR32_SCIF_IMR                                      0x00000008
#define AVR32_SCIF_IMR_AE                                           31
#define AVR32_SCIF_IMR_AE_MASK                              0x80000000
#define AVR32_SCIF_IMR_AE_OFFSET                                    31
#define AVR32_SCIF_IMR_AE_SIZE                                       1
#define AVR32_SCIF_IMR_BODDET                                        4
#define AVR32_SCIF_IMR_BODDET_MASK                          0x00000010
#define AVR32_SCIF_IMR_BODDET_OFFSET                                 4
#define AVR32_SCIF_IMR_BODDET_SIZE                                   1
#define AVR32_SCIF_IMR_MASK                                 0x8000007f
#define AVR32_SCIF_IMR_OSC0RDY                                       0
#define AVR32_SCIF_IMR_OSC0RDY_MASK                         0x00000001
#define AVR32_SCIF_IMR_OSC0RDY_OFFSET                                0
#define AVR32_SCIF_IMR_OSC0RDY_SIZE                                  1
#define AVR32_SCIF_IMR_OSC32RDY                                      1
#define AVR32_SCIF_IMR_OSC32RDY_MASK                        0x00000002
#define AVR32_SCIF_IMR_OSC32RDY_OFFSET                               1
#define AVR32_SCIF_IMR_OSC32RDY_SIZE                                 1
#define AVR32_SCIF_IMR_PLL0_LOCK                                     2
#define AVR32_SCIF_IMR_PLL0_LOCKLOST                                 5
#define AVR32_SCIF_IMR_PLL0_LOCKLOST_MASK                   0x00000020
#define AVR32_SCIF_IMR_PLL0_LOCKLOST_OFFSET                          5
#define AVR32_SCIF_IMR_PLL0_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IMR_PLL0_LOCK_MASK                       0x00000004
#define AVR32_SCIF_IMR_PLL0_LOCK_OFFSET                              2
#define AVR32_SCIF_IMR_PLL0_LOCK_SIZE                                1
#define AVR32_SCIF_IMR_PLL1_LOCK                                     3
#define AVR32_SCIF_IMR_PLL1_LOCKLOST                                 6
#define AVR32_SCIF_IMR_PLL1_LOCKLOST_MASK                   0x00000040
#define AVR32_SCIF_IMR_PLL1_LOCKLOST_OFFSET                          6
#define AVR32_SCIF_IMR_PLL1_LOCKLOST_SIZE                            1
#define AVR32_SCIF_IMR_PLL1_LOCK_MASK                       0x00000008
#define AVR32_SCIF_IMR_PLL1_LOCK_OFFSET                              3
#define AVR32_SCIF_IMR_PLL1_LOCK_SIZE                                1
#define AVR32_SCIF_IMR_RESETVALUE                           0x00000000
#define AVR32_SCIF_ISR                                      0x0000000c
#define AVR32_SCIF_ISR_AE                                           31
#define AVR32_SCIF_ISR_AE_MASK                              0x80000000
#define AVR32_SCIF_ISR_AE_OFFSET                                    31
#define AVR32_SCIF_ISR_AE_SIZE                                       1
#define AVR32_SCIF_ISR_BODDET                                        4
#define AVR32_SCIF_ISR_BODDET_MASK                          0x00000010
#define AVR32_SCIF_ISR_BODDET_OFFSET                                 4
#define AVR32_SCIF_ISR_BODDET_SIZE                                   1
#define AVR32_SCIF_ISR_MASK                                 0x8000007f
#define AVR32_SCIF_ISR_OSC0RDY                                       0
#define AVR32_SCIF_ISR_OSC0RDY_MASK                         0x00000001
#define AVR32_SCIF_ISR_OSC0RDY_OFFSET                                0
#define AVR32_SCIF_ISR_OSC0RDY_SIZE                                  1
#define AVR32_SCIF_ISR_OSC32RDY                                      1
#define AVR32_SCIF_ISR_OSC32RDY_MASK                        0x00000002
#define AVR32_SCIF_ISR_OSC32RDY_OFFSET                               1
#define AVR32_SCIF_ISR_OSC32RDY_SIZE                                 1
#define AVR32_SCIF_ISR_PLL0_LOCK                                     2
#define AVR32_SCIF_ISR_PLL0_LOCKLOST                                 5
#define AVR32_SCIF_ISR_PLL0_LOCKLOST_MASK                   0x00000020
#define AVR32_SCIF_ISR_PLL0_LOCKLOST_OFFSET                          5
#define AVR32_SCIF_ISR_PLL0_LOCKLOST_SIZE                            1
#define AVR32_SCIF_ISR_PLL0_LOCK_MASK                       0x00000004
#define AVR32_SCIF_ISR_PLL0_LOCK_OFFSET                              2
#define AVR32_SCIF_ISR_PLL0_LOCK_SIZE                                1
#define AVR32_SCIF_ISR_PLL1_LOCK                                     3
#define AVR32_SCIF_ISR_PLL1_LOCKLOST                                 6
#define AVR32_SCIF_ISR_PLL1_LOCKLOST_MASK                   0x00000040
#define AVR32_SCIF_ISR_PLL1_LOCKLOST_OFFSET                          6
#define AVR32_SCIF_ISR_PLL1_LOCKLOST_SIZE                            1
#define AVR32_SCIF_ISR_PLL1_LOCK_MASK                       0x00000008
#define AVR32_SCIF_ISR_PLL1_LOCK_OFFSET                              3
#define AVR32_SCIF_ISR_PLL1_LOCK_SIZE                                1
#define AVR32_SCIF_ISR_RESETVALUE                           0x00000000
#define AVR32_SCIF_KEY                                              24
#define AVR32_SCIF_KEY_MASK                                 0xff000000
#define AVR32_SCIF_KEY_OFFSET                                       24
#define AVR32_SCIF_KEY_SIZE                                          8
#define AVR32_SCIF_LEVEL                                             0
#define AVR32_SCIF_LEVEL_MASK                               0x0000003f
#define AVR32_SCIF_LEVEL_OFFSET                                      0
#define AVR32_SCIF_LEVEL_SIZE                                        6
#define AVR32_SCIF_LOCK                                              3
#define AVR32_SCIF_LOCK_MASK                                0x00000008
#define AVR32_SCIF_LOCK_OFFSET                                       3
#define AVR32_SCIF_LOCK_SIZE                                         1
#define AVR32_SCIF_MODE_CRYSTAL                             0x00000001
#define AVR32_SCIF_MODE_CRYSTAL_ACG                         0x00000001
#define AVR32_SCIF_MODE_CRYSTAL_NO_ACG                      0x00000002
#define AVR32_SCIF_MODE_EXT_CLOCK                           0x00000000
#define AVR32_SCIF_NOLOCK                                            4
#define AVR32_SCIF_NOLOCK_MASK                              0x00000010
#define AVR32_SCIF_NOLOCK_OFFSET                                     4
#define AVR32_SCIF_NOLOCK_SIZE                                       1
#define AVR32_SCIF_OFF1                                     0x00000000
#define AVR32_SCIF_OFF2                                     0x00000003
#define AVR32_SCIF_OSC0                                     0x00000000
#define AVR32_SCIF_OSC0RDY                                           0
#define AVR32_SCIF_OSC0RDY_MASK                             0x00000001
#define AVR32_SCIF_OSC0RDY_OFFSET                                    0
#define AVR32_SCIF_OSC0RDY_SIZE                                      1
#define AVR32_SCIF_OSC1                                     0x00000001
#define AVR32_SCIF_OSC32_FREQUENCY                               32768
#define AVR32_SCIF_OSC32EN                                           0
#define AVR32_SCIF_OSC32EN_MASK                             0x00000001
#define AVR32_SCIF_OSC32EN_OFFSET                                    0
#define AVR32_SCIF_OSC32EN_SIZE                                      1
#define AVR32_SCIF_OSC32RDY                                          1
#define AVR32_SCIF_OSC32RDY_MASK                            0x00000002
#define AVR32_SCIF_OSC32RDY_OFFSET                                   1
#define AVR32_SCIF_OSC32RDY_SIZE                                     1
#define AVR32_SCIF_OSC32VERSION                             0x000003e8
#define AVR32_SCIF_OSC32VERSION_MASK                        0x000f0fff
#define AVR32_SCIF_OSC32VERSION_RESETVALUE                  0x00000100
#define AVR32_SCIF_OSC32VERSION_VARIANT                             16
#define AVR32_SCIF_OSC32VERSION_VARIANT_MASK                0x000f0000
#define AVR32_SCIF_OSC32VERSION_VARIANT_OFFSET                      16
#define AVR32_SCIF_OSC32VERSION_VARIANT_SIZE                         4
#define AVR32_SCIF_OSC32VERSION_VERSION                              0
#define AVR32_SCIF_OSC32VERSION_VERSION_MASK                0x00000fff
#define AVR32_SCIF_OSC32VERSION_VERSION_OFFSET                       0
#define AVR32_SCIF_OSC32VERSION_VERSION_SIZE                        12
#define AVR32_SCIF_OSCCTRL                                  0x00000024
#define AVR32_SCIF_OSCCTRL0_GAIN_G0                         0x00000000
#define AVR32_SCIF_OSCCTRL0_GAIN_G1                         0x00000001
#define AVR32_SCIF_OSCCTRL0_GAIN_G2                         0x00000002
#define AVR32_SCIF_OSCCTRL0_GAIN_G3                         0x00000003
#define AVR32_SCIF_OSCCTRL0_MODE_CRYSTAL                    0x00000001
#define AVR32_SCIF_OSCCTRL0_MODE_EXTCLK                     0x00000000
#define AVR32_SCIF_OSCCTRL0_STARTUP_0_RCOSC                 0x00000000
#define AVR32_SCIF_OSCCTRL0_STARTUP_128_RCOSC               0x00000002
#define AVR32_SCIF_OSCCTRL0_STARTUP_16384_RCOSC             0x00000006
#define AVR32_SCIF_OSCCTRL0_STARTUP_2048_RCOSC              0x00000003
#define AVR32_SCIF_OSCCTRL0_STARTUP_4096_RCOSC              0x00000004
#define AVR32_SCIF_OSCCTRL0_STARTUP_64_RCOSC                0x00000001
#define AVR32_SCIF_OSCCTRL0_STARTUP_8192_RCOSC              0x00000005
#define AVR32_SCIF_OSCCTRL0_STARTUP_32768_RCOSC             0x00000007
#define AVR32_SCIF_OSCCTRL0_STARTUP_4_RCOSC                 0x00000008
#define AVR32_SCIF_OSCCTRL0_STARTUP_8_RCOSC                 0x00000009
#define AVR32_SCIF_OSCCTRL0_STARTUP_16_RCOSC                0x0000000a
#define AVR32_SCIF_OSCCTRL0_STARTUP_32_RCOSC                0x0000000b
#define AVR32_SCIF_OSCCTRL0_STARTUP_256_RCOSC               0x0000000c
#define AVR32_SCIF_OSCCTRL0_STARTUP_512_RCOSC               0x0000000d
#define AVR32_SCIF_OSCCTRL0_STARTUP_1024_RCOSC              0x0000000e
#define AVR32_SCIF_OSCCTRL32                                0x0000003c
#define AVR32_SCIF_OSCCTRL32_MASK                           0x00070301
#define AVR32_SCIF_OSCCTRL32_MODE                                    8
#define AVR32_SCIF_OSCCTRL32_MODE_CRYSTAL_ACG               0x00000001
#define AVR32_SCIF_OSCCTRL32_MODE_CRYSTAL_NO_ACG            0x00000002
#define AVR32_SCIF_OSCCTRL32_MODE_EXT_CLOCK                 0x00000000
#define AVR32_SCIF_OSCCTRL32_MODE_MASK                      0x00000300
#define AVR32_SCIF_OSCCTRL32_MODE_OFFSET                             8
#define AVR32_SCIF_OSCCTRL32_MODE_SIZE                               2
#define AVR32_SCIF_OSCCTRL32_OSC32EN                                 0
#define AVR32_SCIF_OSCCTRL32_OSC32EN_MASK                   0x00000001
#define AVR32_SCIF_OSCCTRL32_OSC32EN_OFFSET                          0
#define AVR32_SCIF_OSCCTRL32_OSC32EN_SIZE                            1
#define AVR32_SCIF_OSCCTRL32_RESETVALUE                     0x00000000
#define AVR32_SCIF_OSCCTRL32_STARTUP                                16
#define AVR32_SCIF_OSCCTRL32_STARTUP_0_RCOSC                0x00000000
#define AVR32_SCIF_OSCCTRL32_STARTUP_128_RCOSC              0x00000001
#define AVR32_SCIF_OSCCTRL32_STARTUP_8192_RCOSC             0x00000002
#define AVR32_SCIF_OSCCTRL32_STARTUP_16384_RCOSC            0x00000003
#define AVR32_SCIF_OSCCTRL32_STARTUP_65536_RCOSC            0x00000004
#define AVR32_SCIF_OSCCTRL32_STARTUP_131072_RCOSC           0x00000005
#define AVR32_SCIF_OSCCTRL32_STARTUP_262144_RCOSC           0x00000006
#define AVR32_SCIF_OSCCTRL32_STARTUP_524288_RCOSC           0x00000007
#define AVR32_SCIF_OSCCTRL32_STARTUP_MASK                   0x00070000
#define AVR32_SCIF_OSCCTRL32_STARTUP_OFFSET                         16
#define AVR32_SCIF_OSCCTRL32_STARTUP_SIZE                            3
#define AVR32_SCIF_OSCCTRL_ACG                                       3
#define AVR32_SCIF_OSCCTRL_ACG_MASK                         0x00000008
#define AVR32_SCIF_OSCCTRL_ACG_OFFSET                                3
#define AVR32_SCIF_OSCCTRL_ACG_SIZE                                  1
#define AVR32_SCIF_OSCCTRL_GAIN                                      1
#define AVR32_SCIF_OSCCTRL_GAIN_MASK                        0x00000006
#define AVR32_SCIF_OSCCTRL_GAIN_OFFSET                               1
#define AVR32_SCIF_OSCCTRL_GAIN_SIZE                                 2
#define AVR32_SCIF_OSCCTRL_MASK                             0x00010f0f
#define AVR32_SCIF_OSCCTRL_MODE                                      0
#define AVR32_SCIF_OSCCTRL_MODE_CRYSTAL                     0x00000001
#define AVR32_SCIF_OSCCTRL_MODE_EXT_CLOCK                   0x00000000
#define AVR32_SCIF_OSCCTRL_MODE_MASK                        0x00000001
#define AVR32_SCIF_OSCCTRL_MODE_OFFSET                               0
#define AVR32_SCIF_OSCCTRL_MODE_SIZE                                 1
#define AVR32_SCIF_OSCCTRL_OSCEN                                    16
#define AVR32_SCIF_OSCCTRL_OSCEN_MASK                       0x00010000
#define AVR32_SCIF_OSCCTRL_OSCEN_OFFSET                             16
#define AVR32_SCIF_OSCCTRL_OSCEN_SIZE                                1
#define AVR32_SCIF_OSCCTRL_RESETVALUE                       0x00000000
#define AVR32_SCIF_OSCCTRL_STARTUP                                   8
#define AVR32_SCIF_OSCCTRL_STARTUP_MASK                     0x00000f00
#define AVR32_SCIF_OSCCTRL_STARTUP_OFFSET                            8
#define AVR32_SCIF_OSCCTRL_STARTUP_SIZE                              4
#define AVR32_SCIF_OSCEN                                            16
#define AVR32_SCIF_OSCEN_MASK                               0x00010000
#define AVR32_SCIF_OSCEN_OFFSET                                     16
#define AVR32_SCIF_OSCEN_SIZE                                        1
#define AVR32_SCIF_OSCSEL                                            8
#define AVR32_SCIF_OSCSEL_MASK                              0x00000f00
#define AVR32_SCIF_OSCSEL_OFFSET                                     8
#define AVR32_SCIF_OSCSEL_SIZE                                       4
#define AVR32_SCIF_OSCVERSION                               0x000003d8
#define AVR32_SCIF_OSCVERSION_MASK                          0x000f0fff
#define AVR32_SCIF_OSCVERSION_RESETVALUE                    0x00000110
#define AVR32_SCIF_OSCVERSION_VARIANT                               16
#define AVR32_SCIF_OSCVERSION_VARIANT_MASK                  0x000f0000
#define AVR32_SCIF_OSCVERSION_VARIANT_OFFSET                        16
#define AVR32_SCIF_OSCVERSION_VARIANT_SIZE                           4
#define AVR32_SCIF_OSCVERSION_VERSION                                0
#define AVR32_SCIF_OSCVERSION_VERSION_MASK                  0x00000fff
#define AVR32_SCIF_OSCVERSION_VERSION_OFFSET                         0
#define AVR32_SCIF_OSCVERSION_VERSION_SIZE                          12
#define AVR32_SCIF_PCLKSR                                   0x00000014
#define AVR32_SCIF_PCLKSR_AE                                        31
#define AVR32_SCIF_PCLKSR_AE_MASK                           0x80000000
#define AVR32_SCIF_PCLKSR_AE_OFFSET                                 31
#define AVR32_SCIF_PCLKSR_AE_SIZE                                    1
#define AVR32_SCIF_PCLKSR_BODDET                                     4
#define AVR32_SCIF_PCLKSR_BODDET_MASK                       0x00000010
#define AVR32_SCIF_PCLKSR_BODDET_OFFSET                              4
#define AVR32_SCIF_PCLKSR_BODDET_SIZE                                1
#define AVR32_SCIF_PCLKSR_MASK                              0x8000007f
#define AVR32_SCIF_PCLKSR_OSC0RDY                                    0
#define AVR32_SCIF_PCLKSR_OSC0RDY_MASK                      0x00000001
#define AVR32_SCIF_PCLKSR_OSC0RDY_OFFSET                             0
#define AVR32_SCIF_PCLKSR_OSC0RDY_SIZE                               1
#define AVR32_SCIF_PCLKSR_OSC32RDY                                   1
#define AVR32_SCIF_PCLKSR_OSC32RDY_MASK                     0x00000002
#define AVR32_SCIF_PCLKSR_OSC32RDY_OFFSET                            1
#define AVR32_SCIF_PCLKSR_OSC32RDY_SIZE                              1
#define AVR32_SCIF_PCLKSR_PLL0_LOCK                                  2
#define AVR32_SCIF_PCLKSR_PLL0_LOCKLOST                              5
#define AVR32_SCIF_PCLKSR_PLL0_LOCKLOST_MASK                0x00000020
#define AVR32_SCIF_PCLKSR_PLL0_LOCKLOST_OFFSET                       5
#define AVR32_SCIF_PCLKSR_PLL0_LOCKLOST_SIZE                         1
#define AVR32_SCIF_PCLKSR_PLL0_LOCK_MASK                    0x00000004
#define AVR32_SCIF_PCLKSR_PLL0_LOCK_OFFSET                           2
#define AVR32_SCIF_PCLKSR_PLL0_LOCK_SIZE                             1
#define AVR32_SCIF_PCLKSR_PLL1_LOCK                                  3
#define AVR32_SCIF_PCLKSR_PLL1_LOCKLOST                              6
#define AVR32_SCIF_PCLKSR_PLL1_LOCKLOST_MASK                0x00000040
#define AVR32_SCIF_PCLKSR_PLL1_LOCKLOST_OFFSET                       6
#define AVR32_SCIF_PCLKSR_PLL1_LOCKLOST_SIZE                         1
#define AVR32_SCIF_PCLKSR_PLL1_LOCK_MASK                    0x00000008
#define AVR32_SCIF_PCLKSR_PLL1_LOCK_OFFSET                           3
#define AVR32_SCIF_PCLKSR_PLL1_LOCK_SIZE                             1
#define AVR32_SCIF_PCLKSR_RESETVALUE                        0x00000000
#define AVR32_SCIF_PLL                                      0x0000001c
#define AVR32_SCIF_PLL0_LOCK                                         2
#define AVR32_SCIF_PLL0_LOCKLOST                                     5
#define AVR32_SCIF_PLL0_LOCKLOST_MASK                       0x00000020
#define AVR32_SCIF_PLL0_LOCKLOST_OFFSET                              5
#define AVR32_SCIF_PLL0_LOCKLOST_SIZE                                1
#define AVR32_SCIF_PLL0_LOCK_MASK                           0x00000004
#define AVR32_SCIF_PLL0_LOCK_OFFSET                                  2
#define AVR32_SCIF_PLL0_LOCK_SIZE                                    1
#define AVR32_SCIF_PLL1_LOCK                                         3
#define AVR32_SCIF_PLL1_LOCKLOST                                     6
#define AVR32_SCIF_PLL1_LOCKLOST_MASK                       0x00000040
#define AVR32_SCIF_PLL1_LOCKLOST_OFFSET                              6
#define AVR32_SCIF_PLL1_LOCKLOST_SIZE                                1
#define AVR32_SCIF_PLL1_LOCK_MASK                           0x00000008
#define AVR32_SCIF_PLL1_LOCK_OFFSET                                  3
#define AVR32_SCIF_PLL1_LOCK_SIZE                                    1
#define AVR32_SCIF_PLLBPL                                            7
#define AVR32_SCIF_PLLBPL_MASK                              0x00000080
#define AVR32_SCIF_PLLBPL_OFFSET                                     7
#define AVR32_SCIF_PLLBPL_SIZE                                       1
#define AVR32_SCIF_PLLCOUNT                                         24
#define AVR32_SCIF_PLLCOUNT_MASK                            0x3f000000
#define AVR32_SCIF_PLLCOUNT_OFFSET                                  24
#define AVR32_SCIF_PLLCOUNT_SIZE                                     6
#define AVR32_SCIF_PLLDIV                                            8
#define AVR32_SCIF_PLLDIV_MASK                              0x00000f00
#define AVR32_SCIF_PLLDIV_OFFSET                                     8
#define AVR32_SCIF_PLLDIV_SIZE                                       4
#define AVR32_SCIF_PLLEN                                             0
#define AVR32_SCIF_PLLEN_MASK                               0x00000001
#define AVR32_SCIF_PLLEN_OFFSET                                      0
#define AVR32_SCIF_PLLEN_SIZE                                        1
#define AVR32_SCIF_PLLIOTESTEN                                      30
#define AVR32_SCIF_PLLIOTESTEN_MASK                         0x40000000
#define AVR32_SCIF_PLLIOTESTEN_OFFSET                               30
#define AVR32_SCIF_PLLIOTESTEN_SIZE                                  1
#define AVR32_SCIF_PLLMUL                                           16
#define AVR32_SCIF_PLLMUL_MASK                              0x000f0000
#define AVR32_SCIF_PLLMUL_OFFSET                                    16
#define AVR32_SCIF_PLLMUL_SIZE                                       4
#define AVR32_SCIF_PLLOPT                                            3
#define AVR32_SCIF_PLLOPT_MASK                              0x00000038
#define AVR32_SCIF_PLLOPT_OFFSET                                     3
#define AVR32_SCIF_PLLOPT_SIZE                                       3
#define AVR32_SCIF_PLLOSC                                            1
#define AVR32_SCIF_PLLOSC_MASK                              0x00000002
#define AVR32_SCIF_PLLOSC_OFFSET                                     1
#define AVR32_SCIF_PLLOSC_OSC0                              0x00000000
#define AVR32_SCIF_PLLOSC_OSC1                              0x00000001
#define AVR32_SCIF_PLLOSC_SIZE                                       1
#define AVR32_SCIF_PLLTEST                                          31
#define AVR32_SCIF_PLLTEST_MASK                             0x80000000
#define AVR32_SCIF_PLLTEST_OFFSET                                   31
#define AVR32_SCIF_PLLTEST_SIZE                                      1
#define AVR32_SCIF_PLLVERSION                               0x000003d4
#define AVR32_SCIF_PLLVERSION_MASK                          0x000f0fff
#define AVR32_SCIF_PLLVERSION_RESETVALUE                    0x00000101
#define AVR32_SCIF_PLLVERSION_VARIANT                               16
#define AVR32_SCIF_PLLVERSION_VARIANT_MASK                  0x000f0000
#define AVR32_SCIF_PLLVERSION_VARIANT_OFFSET                        16
#define AVR32_SCIF_PLLVERSION_VARIANT_SIZE                           4
#define AVR32_SCIF_PLLVERSION_VERSION                                0
#define AVR32_SCIF_PLLVERSION_VERSION_MASK                  0x00000fff
#define AVR32_SCIF_PLLVERSION_VERSION_OFFSET                         0
#define AVR32_SCIF_PLLVERSION_VERSION_SIZE                          12
#define AVR32_SCIF_PLL_MASK                                 0xff0f0fbb
#define AVR32_SCIF_PLL_PLLBPL                                        7
#define AVR32_SCIF_PLL_PLLBPL_MASK                          0x00000080
#define AVR32_SCIF_PLL_PLLBPL_OFFSET                                 7
#define AVR32_SCIF_PLL_PLLBPL_SIZE                                   1
#define AVR32_SCIF_PLL_PLLCOUNT                                     24
#define AVR32_SCIF_PLL_PLLCOUNT_MASK                        0x3f000000
#define AVR32_SCIF_PLL_PLLCOUNT_OFFSET                              24
#define AVR32_SCIF_PLL_PLLCOUNT_SIZE                                 6
#define AVR32_SCIF_PLL_PLLDIV                                        8
#define AVR32_SCIF_PLL_PLLDIV_MASK                          0x00000f00
#define AVR32_SCIF_PLL_PLLDIV_OFFSET                                 8
#define AVR32_SCIF_PLL_PLLDIV_SIZE                                   4
#define AVR32_SCIF_PLL_PLLEN                                         0
#define AVR32_SCIF_PLL_PLLEN_MASK                           0x00000001
#define AVR32_SCIF_PLL_PLLEN_OFFSET                                  0
#define AVR32_SCIF_PLL_PLLEN_SIZE                                    1
#define AVR32_SCIF_PLL_PLLIOTESTEN                                  30
#define AVR32_SCIF_PLL_PLLIOTESTEN_MASK                     0x40000000
#define AVR32_SCIF_PLL_PLLIOTESTEN_OFFSET                           30
#define AVR32_SCIF_PLL_PLLIOTESTEN_SIZE                              1
#define AVR32_SCIF_PLL_PLLMUL                                       16
#define AVR32_SCIF_PLL_PLLMUL_MASK                          0x000f0000
#define AVR32_SCIF_PLL_PLLMUL_OFFSET                                16
#define AVR32_SCIF_PLL_PLLMUL_SIZE                                   4
#define AVR32_SCIF_PLL_PLLOPT                                        3
#define AVR32_SCIF_PLL_PLLOPT_MASK                          0x00000038
#define AVR32_SCIF_PLL_PLLOPT_OFFSET                                 3
#define AVR32_SCIF_PLL_PLLOPT_SIZE                                   3
#define AVR32_SCIF_PLL_PLLOSC                                        1
#define AVR32_SCIF_PLL_PLLOSC_MASK                          0x00000002
#define AVR32_SCIF_PLL_PLLOSC_OFFSET                                 1
#define AVR32_SCIF_PLL_PLLOSC_OSC0                          0x00000000
#define AVR32_SCIF_PLL_PLLOSC_OSC1                          0x00000001
#define AVR32_SCIF_PLL_PLLOSC_SIZE                                   1
#define AVR32_SCIF_PLL_PLLTEST                                      31
#define AVR32_SCIF_PLL_PLLTEST_MASK                         0x80000000
#define AVR32_SCIF_PLL_PLLTEST_OFFSET                               31
#define AVR32_SCIF_PLL_PLLTEST_SIZE                                  1
#define AVR32_SCIF_PLL_RESETVALUE                           0x00000000
#define AVR32_SCIF_RATIO                                            20
#define AVR32_SCIF_RATIO_MASK                               0x3ff00000
#define AVR32_SCIF_RATIO_OFFSET                                     20
#define AVR32_SCIF_RATIO_SIZE                                       10
#define AVR32_SCIF_RC120MCR                                 0x00000044
#define AVR32_SCIF_RC120MCR_EN                                       0
#define AVR32_SCIF_RC120MCR_EN_MASK                         0x00000001
#define AVR32_SCIF_RC120MCR_EN_OFFSET                                0
#define AVR32_SCIF_RC120MCR_EN_SIZE                                  1
#define AVR32_SCIF_RC120MCR_MASK                            0x00000001
#define AVR32_SCIF_RC120MCR_RESETVALUE                      0x00000000
#define AVR32_SCIF_RC120MVERSION                            0x000003f0
#define AVR32_SCIF_RC120MVERSION_MASK                       0x000f0fff
#define AVR32_SCIF_RC120MVERSION_RESETVALUE                 0x00000110
#define AVR32_SCIF_RC120MVERSION_VARIANT                            16
#define AVR32_SCIF_RC120MVERSION_VARIANT_MASK               0x000f0000
#define AVR32_SCIF_RC120MVERSION_VARIANT_OFFSET                     16
#define AVR32_SCIF_RC120MVERSION_VARIANT_SIZE                        4
#define AVR32_SCIF_RC120MVERSION_VERSION                             0
#define AVR32_SCIF_RC120MVERSION_VERSION_MASK               0x00000fff
#define AVR32_SCIF_RC120MVERSION_VERSION_OFFSET                      0
#define AVR32_SCIF_RC120MVERSION_VERSION_SIZE                       12
#define AVR32_SCIF_RCCR                                     0x00000038
#define AVR32_SCIF_RCCRVERSION                              0x000003e4
#define AVR32_SCIF_RCCRVERSION_MASK                         0x000f0fff
#define AVR32_SCIF_RCCRVERSION_RESETVALUE                   0x00000110
#define AVR32_SCIF_RCCRVERSION_VARIANT                              16
#define AVR32_SCIF_RCCRVERSION_VARIANT_MASK                 0x000f0000
#define AVR32_SCIF_RCCRVERSION_VARIANT_OFFSET                       16
#define AVR32_SCIF_RCCRVERSION_VARIANT_SIZE                          4
#define AVR32_SCIF_RCCRVERSION_VERSION                               0
#define AVR32_SCIF_RCCRVERSION_VERSION_MASK                 0x00000fff
#define AVR32_SCIF_RCCRVERSION_VERSION_OFFSET                        0
#define AVR32_SCIF_RCCRVERSION_VERSION_SIZE                         12
#define AVR32_SCIF_RCCR_CALIB                                        0
#define AVR32_SCIF_RCCR_CALIB_MASK                          0x000003ff
#define AVR32_SCIF_RCCR_CALIB_OFFSET                                 0
#define AVR32_SCIF_RCCR_CALIB_SIZE                                  10
#define AVR32_SCIF_RCCR_FCD                                         16
#define AVR32_SCIF_RCCR_FCD_MASK                            0x00010000
#define AVR32_SCIF_RCCR_FCD_OFFSET                                  16
#define AVR32_SCIF_RCCR_FCD_SIZE                                     1
#define AVR32_SCIF_RCCR_MASK                                0x000103ff
#define AVR32_SCIF_RCCR_RESETVALUE                          0x00000000
#define AVR32_SCIF_RCOSC_FREQUENCY                               115200
#define AVR32_SCIF_SEL                                               8
#define AVR32_SCIF_SEL_MASK                                 0x0000ff00
#define AVR32_SCIF_SEL_OFFSET                                        8
#define AVR32_SCIF_SEL_SIZE                                          8
#define AVR32_SCIF_SFV                                              31
#define AVR32_SCIF_SFV_MASK                                 0x80000000
#define AVR32_SCIF_SFV_OFFSET                                       31
#define AVR32_SCIF_SFV_SIZE                                          1
#define AVR32_SCIF_SLEEPCALIB                                        8
#define AVR32_SCIF_SLEEPCALIB_MASK                          0x00000700
#define AVR32_SCIF_SLEEPCALIB_OFFSET                                 8
#define AVR32_SCIF_SLEEPCALIB_SIZE                                   3
#define AVR32_SCIF_STILO                                    0x00000040
#define AVR32_SCIF_STILOVERSION                             0x000003ec
#define AVR32_SCIF_STILOVERSION_MASK                        0x000f0003
#define AVR32_SCIF_STILOVERSION_RESETVALUE                  0x00000110
#define AVR32_SCIF_STILOVERSION_VARIANT                             16
#define AVR32_SCIF_STILOVERSION_VARIANT_MASK                0x000f0000
#define AVR32_SCIF_STILOVERSION_VARIANT_OFFSET                      16
#define AVR32_SCIF_STILOVERSION_VARIANT_SIZE                         4
#define AVR32_SCIF_STILOVERSION_VERSION                              0
#define AVR32_SCIF_STILOVERSION_VERSION_MASK                0x00000003
#define AVR32_SCIF_STILOVERSION_VERSION_OFFSET                       0
#define AVR32_SCIF_STILOVERSION_VERSION_SIZE                         2
#define AVR32_SCIF_STILO_EN                                          0
#define AVR32_SCIF_STILO_EN_MASK                            0x00000001
#define AVR32_SCIF_STILO_EN_OFFSET                                   0
#define AVR32_SCIF_STILO_EN_SIZE                                     1
#define AVR32_SCIF_STILO_FCD                                        16
#define AVR32_SCIF_STILO_FCD_MASK                           0x00010000
#define AVR32_SCIF_STILO_FCD_OFFSET                                 16
#define AVR32_SCIF_STILO_FCD_SIZE                                    1
#define AVR32_SCIF_STILO_LOCK                                        3
#define AVR32_SCIF_STILO_LOCK_MASK                          0x00000008
#define AVR32_SCIF_STILO_LOCK_OFFSET                                 3
#define AVR32_SCIF_STILO_LOCK_SIZE                                   1
#define AVR32_SCIF_STILO_MASK                               0xbff1ff1d
#define AVR32_SCIF_STILO_NOLOCK                                      4
#define AVR32_SCIF_STILO_NOLOCK_MASK                        0x00000010
#define AVR32_SCIF_STILO_NOLOCK_OFFSET                               4
#define AVR32_SCIF_STILO_NOLOCK_SIZE                                 1
#define AVR32_SCIF_STILO_RATIO                                      20
#define AVR32_SCIF_STILO_RATIO_MASK                         0x3ff00000
#define AVR32_SCIF_STILO_RATIO_OFFSET                               20
#define AVR32_SCIF_STILO_RATIO_SIZE                                 10
#define AVR32_SCIF_STILO_RESETVALUE                         0x0000ff00
#define AVR32_SCIF_STILO_SEL                                         8
#define AVR32_SCIF_STILO_SEL_MASK                           0x0000ff00
#define AVR32_SCIF_STILO_SEL_OFFSET                                  8
#define AVR32_SCIF_STILO_SEL_SIZE                                    8
#define AVR32_SCIF_STILO_SFV                                        31
#define AVR32_SCIF_STILO_SFV_MASK                           0x80000000
#define AVR32_SCIF_STILO_SFV_OFFSET                                 31
#define AVR32_SCIF_STILO_SFV_SIZE                                    1
#define AVR32_SCIF_STILO_TUNE_EN                                     2
#define AVR32_SCIF_STILO_TUNE_EN_MASK                       0x00000004
#define AVR32_SCIF_STILO_TUNE_EN_OFFSET                              2
#define AVR32_SCIF_STILO_TUNE_EN_SIZE                                1
#define AVR32_SCIF_TUNE_EN                                           2
#define AVR32_SCIF_TUNE_EN_MASK                             0x00000004
#define AVR32_SCIF_TUNE_EN_OFFSET                                    2
#define AVR32_SCIF_TUNE_EN_SIZE                                      1
#define AVR32_SCIF_UNLOCK                                   0x00000018
#define AVR32_SCIF_UNLOCK_ADDR                                       0
#define AVR32_SCIF_UNLOCK_ADDR_MASK                         0x000003ff
#define AVR32_SCIF_UNLOCK_ADDR_OFFSET                                0
#define AVR32_SCIF_UNLOCK_ADDR_SIZE                                 10
#define AVR32_SCIF_UNLOCK_KEY                                       24
#define AVR32_SCIF_UNLOCK_KEY_MASK                          0xff000000
#define AVR32_SCIF_UNLOCK_KEY_OFFSET                                24
#define AVR32_SCIF_UNLOCK_KEY_SIZE                                   8
#define AVR32_SCIF_UNLOCK_MASK                              0xff0003ff
#define AVR32_SCIF_UNLOCK_RESETVALUE                        0x00000000
#define AVR32_SCIF_VARIANT                                          16
#define AVR32_SCIF_VARIANT_MASK                             0x000f0000
#define AVR32_SCIF_VARIANT_OFFSET                                   16
#define AVR32_SCIF_VARIANT_SIZE                                      4
#define AVR32_SCIF_VERSION                                  0x000003fc
#define AVR32_SCIF_VERSION_MASK                             0x000f0fff
#define AVR32_SCIF_VERSION_OFFSET                                    0
#define AVR32_SCIF_VERSION_RESETVALUE                       0x00000102
#define AVR32_SCIF_VERSION_VARIANT                                  16
#define AVR32_SCIF_VERSION_VARIANT_MASK                     0x000f0000
#define AVR32_SCIF_VERSION_VARIANT_OFFSET                           16
#define AVR32_SCIF_VERSION_VARIANT_SIZE                              4
#define AVR32_SCIF_VERSION_VERSION                                   0
#define AVR32_SCIF_VERSION_VERSION_MASK                     0x00000fff
#define AVR32_SCIF_VERSION_VERSION_OFFSET                            0
#define AVR32_SCIF_VERSION_VERSION_SIZE                             12
#define AVR32_SCIF_VREGCR                                   0x00000030
#define AVR32_SCIF_VREGCR_CALIB                                      0
#define AVR32_SCIF_VREGCR_CALIB_MASK                        0x00000007
#define AVR32_SCIF_VREGCR_CALIB_OFFSET                               0
#define AVR32_SCIF_VREGCR_CALIB_SIZE                                 3
#define AVR32_SCIF_VREGCR_FCD                                       16
#define AVR32_SCIF_VREGCR_FCD_MASK                          0x00010000
#define AVR32_SCIF_VREGCR_FCD_OFFSET                                16
#define AVR32_SCIF_VREGCR_FCD_SIZE                                   1
#define AVR32_SCIF_VREGCR_MASK                              0x80010707
#define AVR32_SCIF_VREGCR_RESETVALUE                        0x00000000
#define AVR32_SCIF_VREGCR_SFV                                       31
#define AVR32_SCIF_VREGCR_SFV_MASK                          0x80000000
#define AVR32_SCIF_VREGCR_SFV_OFFSET                                31
#define AVR32_SCIF_VREGCR_SFV_SIZE                                   1
#define AVR32_SCIF_VREGCR_SLEEPCALIB                                 8
#define AVR32_SCIF_VREGCR_SLEEPCALIB_MASK                   0x00000700
#define AVR32_SCIF_VREGCR_SLEEPCALIB_OFFSET                          8
#define AVR32_SCIF_VREGCR_SLEEPCALIB_SIZE                            3
#define AVR32_SCIF_VREGCTRL                                 0x00000034
#define AVR32_SCIF_VREGCTRL_DMD                                      9
#define AVR32_SCIF_VREGCTRL_DMD_MASK                        0x00000200
#define AVR32_SCIF_VREGCTRL_DMD_OFFSET                               9
#define AVR32_SCIF_VREGCTRL_DMD_SIZE                                 1
#define AVR32_SCIF_VREGCTRL_MASK                            0x80000200
#define AVR32_SCIF_VREGCTRL_RESETVALUE                      0x00000000
#define AVR32_SCIF_VREGCTRL_SFV                                     31
#define AVR32_SCIF_VREGCTRL_SFV_MASK                        0x80000000
#define AVR32_SCIF_VREGCTRL_SFV_OFFSET                              31
#define AVR32_SCIF_VREGCTRL_SFV_SIZE                                 1
#define AVR32_SCIF_VREGVERSION                              0x000003e0
#define AVR32_SCIF_VREGVERSION_MASK                         0x000f0fff
#define AVR32_SCIF_VREGVERSION_RESETVALUE                   0x00000110
#define AVR32_SCIF_VREGVERSION_VARIANT                              16
#define AVR32_SCIF_VREGVERSION_VARIANT_MASK                 0x000f0000
#define AVR32_SCIF_VREGVERSION_VARIANT_OFFSET                       16
#define AVR32_SCIF_VREGVERSION_VARIANT_SIZE                          4
#define AVR32_SCIF_VREGVERSION_VERSION                               0
#define AVR32_SCIF_VREGVERSION_VERSION_MASK                 0x00000fff
#define AVR32_SCIF_VREGVERSION_VERSION_OFFSET                        0
#define AVR32_SCIF_VREGVERSION_VERSION_SIZE                         12

#define AVR32_SCIF_ACCESS_KEY                          0x000000aa



#ifdef __AVR32_ABI_COMPILER__


typedef struct avr32_scif_ier_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_ier_t;



typedef struct avr32_scif_idr_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_idr_t;



typedef struct avr32_scif_imr_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_imr_t;



typedef struct avr32_scif_isr_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_isr_t;



typedef struct avr32_scif_icr_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_icr_t;



typedef struct avr32_scif_pclksr_t {
    unsigned int ae              : 1;
    unsigned int                 :24;
    unsigned int pll1_locklost   : 1;
    unsigned int pll0_locklost   : 1;
    unsigned int boddet          : 1;
    unsigned int pll1_lock       : 1;
    unsigned int pll0_lock       : 1;
    unsigned int osc32rdy        : 1;
    unsigned int osc0rdy         : 1;
} avr32_scif_pclksr_t;



typedef struct avr32_scif_unlock_t {
    unsigned int key             : 8;
    unsigned int                 :14;
    unsigned int addr            :10;
} avr32_scif_unlock_t;



typedef struct avr32_scif_pll_t {
    unsigned int plltest         : 1;
    unsigned int plliotesten     : 1;
    unsigned int pllcount        : 6;
    unsigned int                 : 4;
    unsigned int pllmul          : 4;
    unsigned int                 : 4;
    unsigned int plldiv          : 4;
    unsigned int pllbpl          : 1;
    unsigned int                 : 1;
    unsigned int pllopt          : 3;
    unsigned int                 : 1;
    unsigned int pllosc          : 1;
    unsigned int pllen           : 1;
} avr32_scif_pll_t;



typedef struct avr32_scif_oscctrl_t {
    unsigned int                 :15;
    unsigned int oscen           : 1;
    unsigned int                 : 4;
    unsigned int startup         : 4;
    unsigned int                 : 4;
    unsigned int acg             : 1;
    unsigned int gain            : 2;
    unsigned int mode            : 1;
} avr32_scif_oscctrl_t;



typedef struct avr32_scif_bod_t {
    unsigned int sfv             : 1;
    unsigned int                 :14;
    unsigned int fcd             : 1;
    unsigned int                 : 6;
    unsigned int ctrl            : 2;
    unsigned int                 : 1;
    unsigned int hyst            : 1;
    unsigned int level           : 6;
} avr32_scif_bod_t;



typedef struct avr32_scif_bgcr_t {
    unsigned int sfv             : 1;
    unsigned int                 :14;
    unsigned int fcd             : 1;
    unsigned int                 :13;
    unsigned int calib           : 3;
} avr32_scif_bgcr_t;



typedef struct avr32_scif_vregcr_t {
    unsigned int sfv             : 1;
    unsigned int                 :14;
    unsigned int fcd             : 1;
    unsigned int                 : 5;
    unsigned int sleepcalib      : 3;
    unsigned int                 : 5;
    unsigned int calib           : 3;
} avr32_scif_vregcr_t;



typedef struct avr32_scif_vregctrl_t {
    unsigned int sfv             : 1;
    unsigned int                 :21;
    unsigned int dmd             : 1;
    unsigned int                 : 9;
} avr32_scif_vregctrl_t;



typedef struct avr32_scif_rccr_t {
    unsigned int                 :15;
    unsigned int fcd             : 1;
    unsigned int                 : 6;
    unsigned int calib           :10;
} avr32_scif_rccr_t;



typedef struct avr32_scif_oscctrl32_t {
    unsigned int                 :13;
    unsigned int startup         : 3;
    unsigned int                 : 6;
    unsigned int mode            : 2;
    unsigned int                 : 7;
    unsigned int osc32en         : 1;
} avr32_scif_oscctrl32_t;



typedef struct avr32_scif_stilo_t {
    unsigned int sfv             : 1;
    unsigned int                 : 1;
    unsigned int ratio           :10;
    unsigned int                 : 3;
    unsigned int fcd             : 1;
    unsigned int sel             : 8;
    unsigned int                 : 3;
    unsigned int nolock          : 1;
    unsigned int lock            : 1;
    unsigned int tune_en         : 1;
    unsigned int                 : 1;
    unsigned int en              : 1;
} avr32_scif_stilo_t;



typedef struct avr32_scif_rc120mcr_t {
    unsigned int                 :31;
    unsigned int en              : 1;
} avr32_scif_rc120mcr_t;



typedef struct avr32_scif_hrpcr_t {
    unsigned int hrcount         :24;
    unsigned int                 : 4;
    unsigned int cksel           : 3;
    unsigned int hrpen           : 1;
} avr32_scif_hrpcr_t;



typedef struct avr32_scif_fpcr_t {
    unsigned int                 :28;
    unsigned int cksel           : 3;
    unsigned int fpen            : 1;
} avr32_scif_fpcr_t;



typedef struct avr32_scif_fpmul_t {
    unsigned int                 :12;
    unsigned int fpmul           :20;
} avr32_scif_fpmul_t;



typedef struct avr32_scif_fpdiv_t {
    unsigned int                 :12;
    unsigned int fpdiv           :20;
} avr32_scif_fpdiv_t;



typedef struct avr32_scif_gcctrl_t {
    unsigned int                 : 8;
    unsigned int div             : 8;
    unsigned int                 : 4;
    unsigned int oscsel          : 4;
    unsigned int                 : 6;
    unsigned int diven           : 1;
    unsigned int cen             : 1;
} avr32_scif_gcctrl_t;



typedef struct avr32_scif_cmversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_cmversion_t;



typedef struct avr32_scif_gclkprescversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_gclkprescversion_t;



typedef struct avr32_scif_pllversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_pllversion_t;



typedef struct avr32_scif_oscversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_oscversion_t;



typedef struct avr32_scif_bodversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_bodversion_t;



typedef struct avr32_scif_vregversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_vregversion_t;



typedef struct avr32_scif_rccrversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_rccrversion_t;



typedef struct avr32_scif_osc32version_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_osc32version_t;



typedef struct avr32_scif_stiloversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 :14;
    unsigned int version         : 2;
} avr32_scif_stiloversion_t;



typedef struct avr32_scif_rc120mversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_rc120mversion_t;



typedef struct avr32_scif_gplpversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_gplpversion_t;



typedef struct avr32_scif_gclkversion_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_gclkversion_t;



typedef struct avr32_scif_version_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_scif_version_t;



typedef struct avr32_scif_t {
  union {
          unsigned long                  ier       ;//0x0000
          avr32_scif_ier_t               IER       ;
  };
  union {
          unsigned long                  idr       ;//0x0004
          avr32_scif_idr_t               IDR       ;
  };
  union {
    const unsigned long                  imr       ;//0x0008
    const avr32_scif_imr_t               IMR       ;
  };
  union {
    const unsigned long                  isr       ;//0x000c
    const avr32_scif_isr_t               ISR       ;
  };
  union {
          unsigned long                  icr       ;//0x0010
          avr32_scif_icr_t               ICR       ;
  };
  union {
    const unsigned long                  pclksr    ;//0x0014
    const avr32_scif_pclksr_t            PCLKSR    ;
  };
  union {
          unsigned long                  unlock    ;//0x0018
          avr32_scif_unlock_t            UNLOCK    ;
  };
  union {
          unsigned long                  pll       [2];//0x001c
          avr32_scif_pll_t               PLL       [2];
  };
  union {
          unsigned long                  oscctrl   [1];//0x0024
          avr32_scif_oscctrl_t           OSCCTRL   [1];
  };
  union {
          unsigned long                  bod       ;//0x0028
          avr32_scif_bod_t               BOD       ;
  };
  union {
          unsigned long                  bgcr      ;//0x002c
          avr32_scif_bgcr_t              BGCR      ;
  };
  union {
          unsigned long                  vregcr    ;//0x0030
          avr32_scif_vregcr_t            VREGCR    ;
  };
  union {
          unsigned long                  vregctrl  ;//0x0034
          avr32_scif_vregctrl_t          VREGCTRL  ;
  };
  union {
          unsigned long                  rccr      ;//0x0038
          avr32_scif_rccr_t              RCCR      ;
  };
  union {
          unsigned long                  oscctrl32 ;//0x003c
          avr32_scif_oscctrl32_t         OSCCTRL32 ;
  };
  union {
          unsigned long                  stilo     ;//0x0040
          avr32_scif_stilo_t             STILO     ;
  };
  union {
          unsigned long                  rc120mcr  ;//0x0044
          avr32_scif_rc120mcr_t          RC120MCR  ;
  };
          unsigned long                  gplp      [2];//0x0048
  union {
          unsigned long                  hrpcr     ;//0x0050
          avr32_scif_hrpcr_t             HRPCR     ;
  };
  union {
          unsigned long                  fpcr      ;//0x0054
          avr32_scif_fpcr_t              FPCR      ;
  };
  union {
          unsigned long                  fpmul     ;//0x0058
          avr32_scif_fpmul_t             FPMUL     ;
  };
  union {
          unsigned long                  fpdiv     ;//0x005c
          avr32_scif_fpdiv_t             FPDIV     ;
  };
  union {
          unsigned long                  gcctrl    [10];//0x0060
          avr32_scif_gcctrl_t            GCCTRL    [10];
  };
          unsigned int                   :32       ;//0x0088
          unsigned int                   :32       ;//0x008c
          unsigned int                   :32       ;//0x0090
          unsigned int                   :32       ;//0x0094
          unsigned int                   :32       ;//0x0098
          unsigned int                   :32       ;//0x009c
          unsigned int                   :32       ;//0x00a0
          unsigned int                   :32       ;//0x00a4
          unsigned int                   :32       ;//0x00a8
          unsigned int                   :32       ;//0x00ac
          unsigned int                   :32       ;//0x00b0
          unsigned int                   :32       ;//0x00b4
          unsigned int                   :32       ;//0x00b8
          unsigned int                   :32       ;//0x00bc
          unsigned int                   :32       ;//0x00c0
          unsigned int                   :32       ;//0x00c4
          unsigned int                   :32       ;//0x00c8
          unsigned int                   :32       ;//0x00cc
          unsigned int                   :32       ;//0x00d0
          unsigned int                   :32       ;//0x00d4
          unsigned int                   :32       ;//0x00d8
          unsigned int                   :32       ;//0x00dc
          unsigned int                   :32       ;//0x00e0
          unsigned int                   :32       ;//0x00e4
          unsigned int                   :32       ;//0x00e8
          unsigned int                   :32       ;//0x00ec
          unsigned int                   :32       ;//0x00f0
          unsigned int                   :32       ;//0x00f4
          unsigned int                   :32       ;//0x00f8
          unsigned int                   :32       ;//0x00fc
          unsigned int                   :32       ;//0x0100
          unsigned int                   :32       ;//0x0104
          unsigned int                   :32       ;//0x0108
          unsigned int                   :32       ;//0x010c
          unsigned int                   :32       ;//0x0110
          unsigned int                   :32       ;//0x0114
          unsigned int                   :32       ;//0x0118
          unsigned int                   :32       ;//0x011c
          unsigned int                   :32       ;//0x0120
          unsigned int                   :32       ;//0x0124
          unsigned int                   :32       ;//0x0128
          unsigned int                   :32       ;//0x012c
          unsigned int                   :32       ;//0x0130
          unsigned int                   :32       ;//0x0134
          unsigned int                   :32       ;//0x0138
          unsigned int                   :32       ;//0x013c
          unsigned int                   :32       ;//0x0140
          unsigned int                   :32       ;//0x0144
          unsigned int                   :32       ;//0x0148
          unsigned int                   :32       ;//0x014c
          unsigned int                   :32       ;//0x0150
          unsigned int                   :32       ;//0x0154
          unsigned int                   :32       ;//0x0158
          unsigned int                   :32       ;//0x015c
          unsigned int                   :32       ;//0x0160
          unsigned int                   :32       ;//0x0164
          unsigned int                   :32       ;//0x0168
          unsigned int                   :32       ;//0x016c
          unsigned int                   :32       ;//0x0170
          unsigned int                   :32       ;//0x0174
          unsigned int                   :32       ;//0x0178
          unsigned int                   :32       ;//0x017c
          unsigned int                   :32       ;//0x0180
          unsigned int                   :32       ;//0x0184
          unsigned int                   :32       ;//0x0188
          unsigned int                   :32       ;//0x018c
          unsigned int                   :32       ;//0x0190
          unsigned int                   :32       ;//0x0194
          unsigned int                   :32       ;//0x0198
          unsigned int                   :32       ;//0x019c
          unsigned int                   :32       ;//0x01a0
          unsigned int                   :32       ;//0x01a4
          unsigned int                   :32       ;//0x01a8
          unsigned int                   :32       ;//0x01ac
          unsigned int                   :32       ;//0x01b0
          unsigned int                   :32       ;//0x01b4
          unsigned int                   :32       ;//0x01b8
          unsigned int                   :32       ;//0x01bc
          unsigned int                   :32       ;//0x01c0
          unsigned int                   :32       ;//0x01c4
          unsigned int                   :32       ;//0x01c8
          unsigned int                   :32       ;//0x01cc
          unsigned int                   :32       ;//0x01d0
          unsigned int                   :32       ;//0x01d4
          unsigned int                   :32       ;//0x01d8
          unsigned int                   :32       ;//0x01dc
          unsigned int                   :32       ;//0x01e0
          unsigned int                   :32       ;//0x01e4
          unsigned int                   :32       ;//0x01e8
          unsigned int                   :32       ;//0x01ec
          unsigned int                   :32       ;//0x01f0
          unsigned int                   :32       ;//0x01f4
          unsigned int                   :32       ;//0x01f8
          unsigned int                   :32       ;//0x01fc
          unsigned int                   :32       ;//0x0200
          unsigned int                   :32       ;//0x0204
          unsigned int                   :32       ;//0x0208
          unsigned int                   :32       ;//0x020c
          unsigned int                   :32       ;//0x0210
          unsigned int                   :32       ;//0x0214
          unsigned int                   :32       ;//0x0218
          unsigned int                   :32       ;//0x021c
          unsigned int                   :32       ;//0x0220
          unsigned int                   :32       ;//0x0224
          unsigned int                   :32       ;//0x0228
          unsigned int                   :32       ;//0x022c
          unsigned int                   :32       ;//0x0230
          unsigned int                   :32       ;//0x0234
          unsigned int                   :32       ;//0x0238
          unsigned int                   :32       ;//0x023c
          unsigned int                   :32       ;//0x0240
          unsigned int                   :32       ;//0x0244
          unsigned int                   :32       ;//0x0248
          unsigned int                   :32       ;//0x024c
          unsigned int                   :32       ;//0x0250
          unsigned int                   :32       ;//0x0254
          unsigned int                   :32       ;//0x0258
          unsigned int                   :32       ;//0x025c
          unsigned int                   :32       ;//0x0260
          unsigned int                   :32       ;//0x0264
          unsigned int                   :32       ;//0x0268
          unsigned int                   :32       ;//0x026c
          unsigned int                   :32       ;//0x0270
          unsigned int                   :32       ;//0x0274
          unsigned int                   :32       ;//0x0278
          unsigned int                   :32       ;//0x027c
          unsigned int                   :32       ;//0x0280
          unsigned int                   :32       ;//0x0284
          unsigned int                   :32       ;//0x0288
          unsigned int                   :32       ;//0x028c
          unsigned int                   :32       ;//0x0290
          unsigned int                   :32       ;//0x0294
          unsigned int                   :32       ;//0x0298
          unsigned int                   :32       ;//0x029c
          unsigned int                   :32       ;//0x02a0
          unsigned int                   :32       ;//0x02a4
          unsigned int                   :32       ;//0x02a8
          unsigned int                   :32       ;//0x02ac
          unsigned int                   :32       ;//0x02b0
          unsigned int                   :32       ;//0x02b4
          unsigned int                   :32       ;//0x02b8
          unsigned int                   :32       ;//0x02bc
          unsigned int                   :32       ;//0x02c0
          unsigned int                   :32       ;//0x02c4
          unsigned int                   :32       ;//0x02c8
          unsigned int                   :32       ;//0x02cc
          unsigned int                   :32       ;//0x02d0
          unsigned int                   :32       ;//0x02d4
          unsigned int                   :32       ;//0x02d8
          unsigned int                   :32       ;//0x02dc
          unsigned int                   :32       ;//0x02e0
          unsigned int                   :32       ;//0x02e4
          unsigned int                   :32       ;//0x02e8
          unsigned int                   :32       ;//0x02ec
          unsigned int                   :32       ;//0x02f0
          unsigned int                   :32       ;//0x02f4
          unsigned int                   :32       ;//0x02f8
          unsigned int                   :32       ;//0x02fc
          unsigned int                   :32       ;//0x0300
          unsigned int                   :32       ;//0x0304
          unsigned int                   :32       ;//0x0308
          unsigned int                   :32       ;//0x030c
          unsigned int                   :32       ;//0x0310
          unsigned int                   :32       ;//0x0314
          unsigned int                   :32       ;//0x0318
          unsigned int                   :32       ;//0x031c
          unsigned int                   :32       ;//0x0320
          unsigned int                   :32       ;//0x0324
          unsigned int                   :32       ;//0x0328
          unsigned int                   :32       ;//0x032c
          unsigned int                   :32       ;//0x0330
          unsigned int                   :32       ;//0x0334
          unsigned int                   :32       ;//0x0338
          unsigned int                   :32       ;//0x033c
          unsigned int                   :32       ;//0x0340
          unsigned int                   :32       ;//0x0344
          unsigned int                   :32       ;//0x0348
          unsigned int                   :32       ;//0x034c
          unsigned int                   :32       ;//0x0350
          unsigned int                   :32       ;//0x0354
          unsigned int                   :32       ;//0x0358
          unsigned int                   :32       ;//0x035c
          unsigned int                   :32       ;//0x0360
          unsigned int                   :32       ;//0x0364
          unsigned int                   :32       ;//0x0368
          unsigned int                   :32       ;//0x036c
          unsigned int                   :32       ;//0x0370
          unsigned int                   :32       ;//0x0374
          unsigned int                   :32       ;//0x0378
          unsigned int                   :32       ;//0x037c
          unsigned int                   :32       ;//0x0380
          unsigned int                   :32       ;//0x0384
          unsigned int                   :32       ;//0x0388
          unsigned int                   :32       ;//0x038c
          unsigned int                   :32       ;//0x0390
          unsigned int                   :32       ;//0x0394
          unsigned int                   :32       ;//0x0398
          unsigned int                   :32       ;//0x039c
          unsigned int                   :32       ;//0x03a0
          unsigned int                   :32       ;//0x03a4
          unsigned int                   :32       ;//0x03a8
          unsigned int                   :32       ;//0x03ac
          unsigned int                   :32       ;//0x03b0
          unsigned int                   :32       ;//0x03b4
          unsigned int                   :32       ;//0x03b8
          unsigned int                   :32       ;//0x03bc
          unsigned int                   :32       ;//0x03c0
          unsigned int                   :32       ;//0x03c4
          unsigned int                   :32       ;//0x03c8
  union {
    const unsigned long                  cmversion ;//0x03cc
    const avr32_scif_cmversion_t         CMVERSION ;
  };
  union {
    const unsigned long                  gclkprescversion;//0x03d0
    const avr32_scif_gclkprescversion_t  GCLKPRESCVERSION;
  };
  union {
    const unsigned long                  pllversion;//0x03d4
    const avr32_scif_pllversion_t        PLLVERSION;
  };
  union {
    const unsigned long                  oscversion;//0x03d8
    const avr32_scif_oscversion_t        OSCVERSION;
  };
  union {
    const unsigned long                  bodversion;//0x03dc
    const avr32_scif_bodversion_t        BODVERSION;
  };
  union {
    const unsigned long                  vregversion;//0x03e0
    const avr32_scif_vregversion_t       VREGVERSION;
  };
  union {
    const unsigned long                  rccrversion;//0x03e4
    const avr32_scif_rccrversion_t       RCCRVERSION;
  };
  union {
    const unsigned long                  osc32version;//0x03e8
    const avr32_scif_osc32version_t      OSC32VERSION;
  };
  union {
    const unsigned long                  stiloversion;//0x03ec
    const avr32_scif_stiloversion_t      STILOVERSION;
  };
  union {
    const unsigned long                  rc120mversion;//0x03f0
    const avr32_scif_rc120mversion_t     RC120MVERSION;
  };
  union {
    const unsigned long                  gplpversion;//0x03f4
    const avr32_scif_gplpversion_t       GPLPVERSION;
  };
  union {
    const unsigned long                  gclkversion;//0x03f8
    const avr32_scif_gclkversion_t       GCLKVERSION;
  };
  union {
    const unsigned long                  version   ;//0x03fc
    const avr32_scif_version_t           VERSION   ;
  };
} avr32_scif_t;



/*#ifdef __AVR32_ABI_COMPILER__*/
#endif

/*#ifdef AVR32_SCIF_1022_H_INCLUDED*/
#endif

