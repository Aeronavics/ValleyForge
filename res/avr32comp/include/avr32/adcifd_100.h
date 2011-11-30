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
#ifndef AVR32_ADCIFD_100_H_INCLUDED
#define AVR32_ADCIFD_100_H_INCLUDED

#include "avr32/abi.h"


/*
 Note to user:

 The following defines are always generated:
 - Register offset: AVR32_ADCIFD_<register>
 - Bitfield mask:   AVR32_ADCIFD_<register>_<bitfield>
 - Bitfield offset: AVR32_ADCIFD_<register>_<bitfield>_OFFSET
 - Bitfield size:   AVR32_ADCIFD_<register>_<bitfield>_SIZE
 - Bitfield values: AVR32_ADCIFD_<register>_<bitfield>_<value name>

 The following defines are generated if they don't cause ambiguities,
 i.e. the name is unique, or all values with that name are the same.
 - Bitfield mask:   AVR32_ADCIFD_<bitfield>
 - Bitfield offset: AVR32_ADCIFD_<bitfield>_OFFSET
 - Bitfield size:   AVR32_ADCIFD_<bitfield>_SIZE
 - Bitfield values: AVR32_ADCIFD_<bitfield>_<value name>
 - Bitfield values: AVR32_ADCIFD_<value name>

 All defines are sorted alphabetically.
*/


#define AVR32_ADCIFD_CBUSY                                            27
#define AVR32_ADCIFD_CBUSY_MASK                               0x08000000
#define AVR32_ADCIFD_CBUSY_OFFSET                                     27
#define AVR32_ADCIFD_CBUSY_SIZE                                        1
#define AVR32_ADCIFD_CFG                                      0x00000004
#define AVR32_ADCIFD_CFG_MASK                                 0x00000001
#define AVR32_ADCIFD_CFG_PRM                                           0
#define AVR32_ADCIFD_CFG_PRM_MASK                             0x00000001
#define AVR32_ADCIFD_CFG_PRM_OFFSET                                    0
#define AVR32_ADCIFD_CFG_PRM_SIZE                                      1
#define AVR32_ADCIFD_CFG_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_CNV0                                              0
#define AVR32_ADCIFD_CNV0_MASK                                0x0000000f
#define AVR32_ADCIFD_CNV0_OFFSET                                       0
#define AVR32_ADCIFD_CNV0_SIZE                                         4
#define AVR32_ADCIFD_CNV1                                              4
#define AVR32_ADCIFD_CNV10                                             8
#define AVR32_ADCIFD_CNV10_MASK                               0x00000f00
#define AVR32_ADCIFD_CNV10_OFFSET                                      8
#define AVR32_ADCIFD_CNV10_SIZE                                        4
#define AVR32_ADCIFD_CNV11                                            12
#define AVR32_ADCIFD_CNV11_MASK                               0x0000f000
#define AVR32_ADCIFD_CNV11_OFFSET                                     12
#define AVR32_ADCIFD_CNV11_SIZE                                        4
#define AVR32_ADCIFD_CNV12                                            16
#define AVR32_ADCIFD_CNV12_MASK                               0x000f0000
#define AVR32_ADCIFD_CNV12_OFFSET                                     16
#define AVR32_ADCIFD_CNV12_SIZE                                        4
#define AVR32_ADCIFD_CNV13                                            20
#define AVR32_ADCIFD_CNV13_MASK                               0x00f00000
#define AVR32_ADCIFD_CNV13_OFFSET                                     20
#define AVR32_ADCIFD_CNV13_SIZE                                        4
#define AVR32_ADCIFD_CNV14                                            24
#define AVR32_ADCIFD_CNV14_MASK                               0x0f000000
#define AVR32_ADCIFD_CNV14_OFFSET                                     24
#define AVR32_ADCIFD_CNV14_SIZE                                        4
#define AVR32_ADCIFD_CNV15                                            28
#define AVR32_ADCIFD_CNV15_MASK                               0xf0000000
#define AVR32_ADCIFD_CNV15_OFFSET                                     28
#define AVR32_ADCIFD_CNV15_SIZE                                        4
#define AVR32_ADCIFD_CNV1_MASK                                0x000000f0
#define AVR32_ADCIFD_CNV1_OFFSET                                       4
#define AVR32_ADCIFD_CNV1_SIZE                                         4
#define AVR32_ADCIFD_CNV2                                              8
#define AVR32_ADCIFD_CNV2_MASK                                0x00000f00
#define AVR32_ADCIFD_CNV2_OFFSET                                       8
#define AVR32_ADCIFD_CNV2_SIZE                                         4
#define AVR32_ADCIFD_CNV3                                             12
#define AVR32_ADCIFD_CNV3_MASK                                0x0000f000
#define AVR32_ADCIFD_CNV3_OFFSET                                      12
#define AVR32_ADCIFD_CNV3_SIZE                                         4
#define AVR32_ADCIFD_CNV4                                             16
#define AVR32_ADCIFD_CNV4_MASK                                0x000f0000
#define AVR32_ADCIFD_CNV4_OFFSET                                      16
#define AVR32_ADCIFD_CNV4_SIZE                                         4
#define AVR32_ADCIFD_CNV5                                             20
#define AVR32_ADCIFD_CNV5_MASK                                0x00f00000
#define AVR32_ADCIFD_CNV5_OFFSET                                      20
#define AVR32_ADCIFD_CNV5_SIZE                                         4
#define AVR32_ADCIFD_CNV6                                             24
#define AVR32_ADCIFD_CNV6_MASK                                0x0f000000
#define AVR32_ADCIFD_CNV6_OFFSET                                      24
#define AVR32_ADCIFD_CNV6_SIZE                                         4
#define AVR32_ADCIFD_CNV7                                             28
#define AVR32_ADCIFD_CNV7_MASK                                0xf0000000
#define AVR32_ADCIFD_CNV7_OFFSET                                      28
#define AVR32_ADCIFD_CNV7_SIZE                                         4
#define AVR32_ADCIFD_CNV8                                              0
#define AVR32_ADCIFD_CNV8_MASK                                0x0000000f
#define AVR32_ADCIFD_CNV8_OFFSET                                       0
#define AVR32_ADCIFD_CNV8_SIZE                                         4
#define AVR32_ADCIFD_CNV9                                              4
#define AVR32_ADCIFD_CNV9_MASK                                0x000000f0
#define AVR32_ADCIFD_CNV9_OFFSET                                       4
#define AVR32_ADCIFD_CNV9_SIZE                                         4
#define AVR32_ADCIFD_CNVNB                                            16
#define AVR32_ADCIFD_CNVNB_MASK                               0x000f0000
#define AVR32_ADCIFD_CNVNB_OFFSET                                     16
#define AVR32_ADCIFD_CNVNB_SIZE                                        4
#define AVR32_ADCIFD_CR                                       0x00000000
#define AVR32_ADCIFD_CR_DIS                                            9
#define AVR32_ADCIFD_CR_DIS_MASK                              0x00000200
#define AVR32_ADCIFD_CR_DIS_OFFSET                                     9
#define AVR32_ADCIFD_CR_DIS_SIZE                                       1
#define AVR32_ADCIFD_CR_EN                                             8
#define AVR32_ADCIFD_CR_EN_MASK                               0x00000100
#define AVR32_ADCIFD_CR_EN_OFFSET                                      8
#define AVR32_ADCIFD_CR_EN_SIZE                                        1
#define AVR32_ADCIFD_CR_MASK                                  0x0000030f
#define AVR32_ADCIFD_CR_RESETVALUE                            0x00000000
#define AVR32_ADCIFD_CR_STRIG                                          1
#define AVR32_ADCIFD_CR_STRIG_MASK                            0x00000002
#define AVR32_ADCIFD_CR_STRIG_OFFSET                                   1
#define AVR32_ADCIFD_CR_STRIG_SIZE                                     1
#define AVR32_ADCIFD_CR_SWRST                                          0
#define AVR32_ADCIFD_CR_SWRST_MASK                            0x00000001
#define AVR32_ADCIFD_CR_SWRST_OFFSET                                   0
#define AVR32_ADCIFD_CR_SWRST_SIZE                                     1
#define AVR32_ADCIFD_CR_TSTART                                         3
#define AVR32_ADCIFD_CR_TSTART_MASK                           0x00000008
#define AVR32_ADCIFD_CR_TSTART_OFFSET                                  3
#define AVR32_ADCIFD_CR_TSTART_SIZE                                    1
#define AVR32_ADCIFD_CR_TSTOP                                          2
#define AVR32_ADCIFD_CR_TSTOP_MASK                            0x00000004
#define AVR32_ADCIFD_CR_TSTOP_OFFSET                                   2
#define AVR32_ADCIFD_CR_TSTOP_SIZE                                     1
#define AVR32_ADCIFD_CSCNV                                            16
#define AVR32_ADCIFD_CSCNV_MASK                               0x000f0000
#define AVR32_ADCIFD_CSCNV_OFFSET                                     16
#define AVR32_ADCIFD_CSCNV_SIZE                                        4
#define AVR32_ADCIFD_CSPHC                                    0x0000001c
#define AVR32_ADCIFD_CSPHC_CNV10                                       8
#define AVR32_ADCIFD_CSPHC_CNV10_MASK                         0x00000f00
#define AVR32_ADCIFD_CSPHC_CNV10_OFFSET                                8
#define AVR32_ADCIFD_CSPHC_CNV10_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV11                                      12
#define AVR32_ADCIFD_CSPHC_CNV11_MASK                         0x0000f000
#define AVR32_ADCIFD_CSPHC_CNV11_OFFSET                               12
#define AVR32_ADCIFD_CSPHC_CNV11_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV12                                      16
#define AVR32_ADCIFD_CSPHC_CNV12_MASK                         0x000f0000
#define AVR32_ADCIFD_CSPHC_CNV12_OFFSET                               16
#define AVR32_ADCIFD_CSPHC_CNV12_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV13                                      20
#define AVR32_ADCIFD_CSPHC_CNV13_MASK                         0x00f00000
#define AVR32_ADCIFD_CSPHC_CNV13_OFFSET                               20
#define AVR32_ADCIFD_CSPHC_CNV13_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV14                                      24
#define AVR32_ADCIFD_CSPHC_CNV14_MASK                         0x0f000000
#define AVR32_ADCIFD_CSPHC_CNV14_OFFSET                               24
#define AVR32_ADCIFD_CSPHC_CNV14_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV15                                      28
#define AVR32_ADCIFD_CSPHC_CNV15_MASK                         0xf0000000
#define AVR32_ADCIFD_CSPHC_CNV15_OFFSET                               28
#define AVR32_ADCIFD_CSPHC_CNV15_SIZE                                  4
#define AVR32_ADCIFD_CSPHC_CNV8                                        0
#define AVR32_ADCIFD_CSPHC_CNV8_MASK                          0x0000000f
#define AVR32_ADCIFD_CSPHC_CNV8_OFFSET                                 0
#define AVR32_ADCIFD_CSPHC_CNV8_SIZE                                   4
#define AVR32_ADCIFD_CSPHC_CNV9                                        4
#define AVR32_ADCIFD_CSPHC_CNV9_MASK                          0x000000f0
#define AVR32_ADCIFD_CSPHC_CNV9_OFFSET                                 4
#define AVR32_ADCIFD_CSPHC_CNV9_SIZE                                   4
#define AVR32_ADCIFD_CSPHC_MASK                               0xffffffff
#define AVR32_ADCIFD_CSPHC_RESETVALUE                         0x00000000
#define AVR32_ADCIFD_CSPLC                                    0x00000018
#define AVR32_ADCIFD_CSPLC_CNV0                                        0
#define AVR32_ADCIFD_CSPLC_CNV0_MASK                          0x0000000f
#define AVR32_ADCIFD_CSPLC_CNV0_OFFSET                                 0
#define AVR32_ADCIFD_CSPLC_CNV0_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV1                                        4
#define AVR32_ADCIFD_CSPLC_CNV1_MASK                          0x000000f0
#define AVR32_ADCIFD_CSPLC_CNV1_OFFSET                                 4
#define AVR32_ADCIFD_CSPLC_CNV1_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV2                                        8
#define AVR32_ADCIFD_CSPLC_CNV2_MASK                          0x00000f00
#define AVR32_ADCIFD_CSPLC_CNV2_OFFSET                                 8
#define AVR32_ADCIFD_CSPLC_CNV2_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV3                                       12
#define AVR32_ADCIFD_CSPLC_CNV3_MASK                          0x0000f000
#define AVR32_ADCIFD_CSPLC_CNV3_OFFSET                                12
#define AVR32_ADCIFD_CSPLC_CNV3_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV4                                       16
#define AVR32_ADCIFD_CSPLC_CNV4_MASK                          0x000f0000
#define AVR32_ADCIFD_CSPLC_CNV4_OFFSET                                16
#define AVR32_ADCIFD_CSPLC_CNV4_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV5                                       20
#define AVR32_ADCIFD_CSPLC_CNV5_MASK                          0x00f00000
#define AVR32_ADCIFD_CSPLC_CNV5_OFFSET                                20
#define AVR32_ADCIFD_CSPLC_CNV5_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV6                                       24
#define AVR32_ADCIFD_CSPLC_CNV6_MASK                          0x0f000000
#define AVR32_ADCIFD_CSPLC_CNV6_OFFSET                                24
#define AVR32_ADCIFD_CSPLC_CNV6_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_CNV7                                       28
#define AVR32_ADCIFD_CSPLC_CNV7_MASK                          0xf0000000
#define AVR32_ADCIFD_CSPLC_CNV7_OFFSET                                28
#define AVR32_ADCIFD_CSPLC_CNV7_SIZE                                   4
#define AVR32_ADCIFD_CSPLC_MASK                               0xffffffff
#define AVR32_ADCIFD_CSPLC_RESETVALUE                         0x00000000
#define AVR32_ADCIFD_DIS                                               9
#define AVR32_ADCIFD_DIS_MASK                                 0x00000200
#define AVR32_ADCIFD_DIS_OFFSET                                        9
#define AVR32_ADCIFD_DIS_SIZE                                          1
#define AVR32_ADCIFD_EN_SIZE                                           1
#define AVR32_ADCIFD_HT                                               16
#define AVR32_ADCIFD_HT_MASK                                  0x03ff0000
#define AVR32_ADCIFD_HT_OFFSET                                        16
#define AVR32_ADCIFD_HT_SIZE                                          10
#define AVR32_ADCIFD_HWLA                                              1
#define AVR32_ADCIFD_HWLA_MASK                                0x00000002
#define AVR32_ADCIFD_HWLA_OFFSET                                       1
#define AVR32_ADCIFD_HWLA_SIZE                                         1
#define AVR32_ADCIFD_IDR                                      0x00000038
#define AVR32_ADCIFD_IDR_LOVR                                          3
#define AVR32_ADCIFD_IDR_LOVR_MASK                            0x00000008
#define AVR32_ADCIFD_IDR_LOVR_OFFSET                                   3
#define AVR32_ADCIFD_IDR_LOVR_SIZE                                     1
#define AVR32_ADCIFD_IDR_MASK                                 0x000000ff
#define AVR32_ADCIFD_IDR_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_IDR_SEOC                                          2
#define AVR32_ADCIFD_IDR_SEOC_MASK                            0x00000004
#define AVR32_ADCIFD_IDR_SEOC_OFFSET                                   2
#define AVR32_ADCIFD_IDR_SEOC_SIZE                                     1
#define AVR32_ADCIFD_IDR_SEOS                                          1
#define AVR32_ADCIFD_IDR_SEOS_MASK                            0x00000002
#define AVR32_ADCIFD_IDR_SEOS_OFFSET                                   1
#define AVR32_ADCIFD_IDR_SEOS_SIZE                                     1
#define AVR32_ADCIFD_IDR_SMTRG                                         5
#define AVR32_ADCIFD_IDR_SMTRG_MASK                           0x00000020
#define AVR32_ADCIFD_IDR_SMTRG_OFFSET                                  5
#define AVR32_ADCIFD_IDR_SMTRG_SIZE                                    1
#define AVR32_ADCIFD_IDR_SSOS                                          0
#define AVR32_ADCIFD_IDR_SSOS_MASK                            0x00000001
#define AVR32_ADCIFD_IDR_SSOS_OFFSET                                   0
#define AVR32_ADCIFD_IDR_SSOS_SIZE                                     1
#define AVR32_ADCIFD_IDR_SUTD                                          6
#define AVR32_ADCIFD_IDR_SUTD_MASK                            0x00000040
#define AVR32_ADCIFD_IDR_SUTD_OFFSET                                   6
#define AVR32_ADCIFD_IDR_SUTD_SIZE                                     1
#define AVR32_ADCIFD_IDR_TTO                                           7
#define AVR32_ADCIFD_IDR_TTO_MASK                             0x00000080
#define AVR32_ADCIFD_IDR_TTO_OFFSET                                    7
#define AVR32_ADCIFD_IDR_TTO_SIZE                                      1
#define AVR32_ADCIFD_IDR_WM                                            4
#define AVR32_ADCIFD_IDR_WM_MASK                              0x00000010
#define AVR32_ADCIFD_IDR_WM_OFFSET                                     4
#define AVR32_ADCIFD_IDR_WM_SIZE                                       1
#define AVR32_ADCIFD_IER                                      0x00000034
#define AVR32_ADCIFD_IER_LOVR                                          3
#define AVR32_ADCIFD_IER_LOVR_MASK                            0x00000008
#define AVR32_ADCIFD_IER_LOVR_OFFSET                                   3
#define AVR32_ADCIFD_IER_LOVR_SIZE                                     1
#define AVR32_ADCIFD_IER_MASK                                 0x000000ff
#define AVR32_ADCIFD_IER_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_IER_SEOC                                          2
#define AVR32_ADCIFD_IER_SEOC_MASK                            0x00000004
#define AVR32_ADCIFD_IER_SEOC_OFFSET                                   2
#define AVR32_ADCIFD_IER_SEOC_SIZE                                     1
#define AVR32_ADCIFD_IER_SEOS                                          1
#define AVR32_ADCIFD_IER_SEOS_MASK                            0x00000002
#define AVR32_ADCIFD_IER_SEOS_OFFSET                                   1
#define AVR32_ADCIFD_IER_SEOS_SIZE                                     1
#define AVR32_ADCIFD_IER_SMTRG                                         5
#define AVR32_ADCIFD_IER_SMTRG_MASK                           0x00000020
#define AVR32_ADCIFD_IER_SMTRG_OFFSET                                  5
#define AVR32_ADCIFD_IER_SMTRG_SIZE                                    1
#define AVR32_ADCIFD_IER_SSOS                                          0
#define AVR32_ADCIFD_IER_SSOS_MASK                            0x00000001
#define AVR32_ADCIFD_IER_SSOS_OFFSET                                   0
#define AVR32_ADCIFD_IER_SSOS_SIZE                                     1
#define AVR32_ADCIFD_IER_SUTD                                          6
#define AVR32_ADCIFD_IER_SUTD_MASK                            0x00000040
#define AVR32_ADCIFD_IER_SUTD_OFFSET                                   6
#define AVR32_ADCIFD_IER_SUTD_SIZE                                     1
#define AVR32_ADCIFD_IER_TTO                                           7
#define AVR32_ADCIFD_IER_TTO_MASK                             0x00000080
#define AVR32_ADCIFD_IER_TTO_OFFSET                                    7
#define AVR32_ADCIFD_IER_TTO_SIZE                                      1
#define AVR32_ADCIFD_IER_WM                                            4
#define AVR32_ADCIFD_IER_WM_MASK                              0x00000010
#define AVR32_ADCIFD_IER_WM_OFFSET                                     4
#define AVR32_ADCIFD_IER_WM_SIZE                                       1
#define AVR32_ADCIFD_IMR                                      0x0000003c
#define AVR32_ADCIFD_IMR_LOVR                                          3
#define AVR32_ADCIFD_IMR_LOVR_MASK                            0x00000008
#define AVR32_ADCIFD_IMR_LOVR_OFFSET                                   3
#define AVR32_ADCIFD_IMR_LOVR_SIZE                                     1
#define AVR32_ADCIFD_IMR_MASK                                 0x000000ff
#define AVR32_ADCIFD_IMR_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_IMR_SEOC                                          2
#define AVR32_ADCIFD_IMR_SEOC_MASK                            0x00000004
#define AVR32_ADCIFD_IMR_SEOC_OFFSET                                   2
#define AVR32_ADCIFD_IMR_SEOC_SIZE                                     1
#define AVR32_ADCIFD_IMR_SEOS                                          1
#define AVR32_ADCIFD_IMR_SEOS_MASK                            0x00000002
#define AVR32_ADCIFD_IMR_SEOS_OFFSET                                   1
#define AVR32_ADCIFD_IMR_SEOS_SIZE                                     1
#define AVR32_ADCIFD_IMR_SMTRG                                         5
#define AVR32_ADCIFD_IMR_SMTRG_MASK                           0x00000020
#define AVR32_ADCIFD_IMR_SMTRG_OFFSET                                  5
#define AVR32_ADCIFD_IMR_SMTRG_SIZE                                    1
#define AVR32_ADCIFD_IMR_SSOS                                          0
#define AVR32_ADCIFD_IMR_SSOS_MASK                            0x00000001
#define AVR32_ADCIFD_IMR_SSOS_OFFSET                                   0
#define AVR32_ADCIFD_IMR_SSOS_SIZE                                     1
#define AVR32_ADCIFD_IMR_SUTD                                          6
#define AVR32_ADCIFD_IMR_SUTD_MASK                            0x00000040
#define AVR32_ADCIFD_IMR_SUTD_OFFSET                                   6
#define AVR32_ADCIFD_IMR_SUTD_SIZE                                     1
#define AVR32_ADCIFD_IMR_TTO                                           7
#define AVR32_ADCIFD_IMR_TTO_MASK                             0x00000080
#define AVR32_ADCIFD_IMR_TTO_OFFSET                                    7
#define AVR32_ADCIFD_IMR_TTO_SIZE                                      1
#define AVR32_ADCIFD_IMR_WM                                            4
#define AVR32_ADCIFD_IMR_WM_MASK                              0x00000010
#define AVR32_ADCIFD_IMR_WM_OFFSET                                     4
#define AVR32_ADCIFD_IMR_WM_SIZE                                       1
#define AVR32_ADCIFD_ITIMER                                   0x00000024
#define AVR32_ADCIFD_ITIMER_ITMC                                       0
#define AVR32_ADCIFD_ITIMER_ITMC_MASK                         0x0000ffff
#define AVR32_ADCIFD_ITIMER_ITMC_OFFSET                                0
#define AVR32_ADCIFD_ITIMER_ITMC_SIZE                                 16
#define AVR32_ADCIFD_ITIMER_MASK                              0x0000ffff
#define AVR32_ADCIFD_ITIMER_RESETVALUE                        0x00000000
#define AVR32_ADCIFD_ITMC                                              0
#define AVR32_ADCIFD_ITMC_MASK                                0x0000ffff
#define AVR32_ADCIFD_ITMC_OFFSET                                       0
#define AVR32_ADCIFD_ITMC_SIZE                                        16
#define AVR32_ADCIFD_LCV                                      0x00000030
#define AVR32_ADCIFD_LCV_LCV                                           0
#define AVR32_ADCIFD_LCV_LCV_MASK                             0x0000ffff
#define AVR32_ADCIFD_LCV_LCV_OFFSET                                    0
#define AVR32_ADCIFD_LCV_LCV_SIZE                                     16
#define AVR32_ADCIFD_LCV_MASK                                 0x0000ffff
#define AVR32_ADCIFD_LCV_OFFSET                                        0
#define AVR32_ADCIFD_LCV_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_LCV_SIZE                                         16
#define AVR32_ADCIFD_LOVR                                              3
#define AVR32_ADCIFD_LOVR_MASK                                0x00000008
#define AVR32_ADCIFD_LOVR_OFFSET                                       3
#define AVR32_ADCIFD_LOVR_SIZE                                         1
#define AVR32_ADCIFD_LT                                                0
#define AVR32_ADCIFD_LT_MASK                                  0x000003ff
#define AVR32_ADCIFD_LT_OFFSET                                         0
#define AVR32_ADCIFD_LT_SIZE                                          10
#define AVR32_ADCIFD_M                                                 0
#define AVR32_ADCIFD_MFM                                              16
#define AVR32_ADCIFD_MFM_MASK                                 0x00010000
#define AVR32_ADCIFD_MFM_OFFSET                                       16
#define AVR32_ADCIFD_MFM_SIZE                                          1
#define AVR32_ADCIFD_M_MASK                                   0x000000ff
#define AVR32_ADCIFD_M_OFFSET                                          0
#define AVR32_ADCIFD_M_SIZE                                            8
#define AVR32_ADCIFD_N                                                 8
#define AVR32_ADCIFD_N_MASK                                   0x0000ff00
#define AVR32_ADCIFD_N_OFFSET                                          8
#define AVR32_ADCIFD_N_SIZE                                            8
#define AVR32_ADCIFD_PARAMETER                                0x00000044
#define AVR32_ADCIFD_PARAMETER_M                                       0
#define AVR32_ADCIFD_PARAMETER_MASK                           0x0000ffff
#define AVR32_ADCIFD_PARAMETER_M_MASK                         0x000000ff
#define AVR32_ADCIFD_PARAMETER_M_OFFSET                                0
#define AVR32_ADCIFD_PARAMETER_M_SIZE                                  8
#define AVR32_ADCIFD_PARAMETER_N                                       8
#define AVR32_ADCIFD_PARAMETER_N_MASK                         0x0000ff00
#define AVR32_ADCIFD_PARAMETER_N_OFFSET                                8
#define AVR32_ADCIFD_PARAMETER_N_SIZE                                  8
#define AVR32_ADCIFD_PARAMETER_RESETVALUE                     0x00000000
#define AVR32_ADCIFD_PRM                                               0
#define AVR32_ADCIFD_PRM_MASK                                 0x00000001
#define AVR32_ADCIFD_PRM_OFFSET                                        0
#define AVR32_ADCIFD_PRM_SIZE                                          1
#define AVR32_ADCIFD_SA                                                0
#define AVR32_ADCIFD_SA_MASK                                  0x00000001
#define AVR32_ADCIFD_SA_OFFSET                                         0
#define AVR32_ADCIFD_SA_SIZE                                           1
#define AVR32_ADCIFD_SBUSY                                            26
#define AVR32_ADCIFD_SBUSY_MASK                               0x04000000
#define AVR32_ADCIFD_SBUSY_OFFSET                                     26
#define AVR32_ADCIFD_SBUSY_SIZE                                        1
#define AVR32_ADCIFD_SCR                                      0x0000000c
#define AVR32_ADCIFD_SCR_LOVR                                          3
#define AVR32_ADCIFD_SCR_LOVR_MASK                            0x00000008
#define AVR32_ADCIFD_SCR_LOVR_OFFSET                                   3
#define AVR32_ADCIFD_SCR_LOVR_SIZE                                     1
#define AVR32_ADCIFD_SCR_MASK                                 0x000000ff
#define AVR32_ADCIFD_SCR_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_SCR_SEOC                                          2
#define AVR32_ADCIFD_SCR_SEOC_MASK                            0x00000004
#define AVR32_ADCIFD_SCR_SEOC_OFFSET                                   2
#define AVR32_ADCIFD_SCR_SEOC_SIZE                                     1
#define AVR32_ADCIFD_SCR_SEOS                                          1
#define AVR32_ADCIFD_SCR_SEOS_MASK                            0x00000002
#define AVR32_ADCIFD_SCR_SEOS_OFFSET                                   1
#define AVR32_ADCIFD_SCR_SEOS_SIZE                                     1
#define AVR32_ADCIFD_SCR_SMTRG                                         5
#define AVR32_ADCIFD_SCR_SMTRG_MASK                           0x00000020
#define AVR32_ADCIFD_SCR_SMTRG_OFFSET                                  5
#define AVR32_ADCIFD_SCR_SMTRG_SIZE                                    1
#define AVR32_ADCIFD_SCR_SSOS                                          0
#define AVR32_ADCIFD_SCR_SSOS_MASK                            0x00000001
#define AVR32_ADCIFD_SCR_SSOS_OFFSET                                   0
#define AVR32_ADCIFD_SCR_SSOS_SIZE                                     1
#define AVR32_ADCIFD_SCR_SUTD                                          6
#define AVR32_ADCIFD_SCR_SUTD_MASK                            0x00000040
#define AVR32_ADCIFD_SCR_SUTD_OFFSET                                   6
#define AVR32_ADCIFD_SCR_SUTD_SIZE                                     1
#define AVR32_ADCIFD_SCR_TTO                                           7
#define AVR32_ADCIFD_SCR_TTO_MASK                             0x00000080
#define AVR32_ADCIFD_SCR_TTO_OFFSET                                    7
#define AVR32_ADCIFD_SCR_TTO_SIZE                                      1
#define AVR32_ADCIFD_SCR_WM                                            4
#define AVR32_ADCIFD_SCR_WM_MASK                              0x00000010
#define AVR32_ADCIFD_SCR_WM_OFFSET                                     4
#define AVR32_ADCIFD_SCR_WM_SIZE                                       1
#define AVR32_ADCIFD_SEOC                                              2
#define AVR32_ADCIFD_SEOC_MASK                                0x00000004
#define AVR32_ADCIFD_SEOC_OFFSET                                       2
#define AVR32_ADCIFD_SEOC_SIZE                                         1
#define AVR32_ADCIFD_SEOS                                              1
#define AVR32_ADCIFD_SEOS_MASK                                0x00000002
#define AVR32_ADCIFD_SEOS_OFFSET                                       1
#define AVR32_ADCIFD_SEOS_SIZE                                         1
#define AVR32_ADCIFD_SEQCFG                                   0x00000014
#define AVR32_ADCIFD_SEQCFG_CNVNB                                     16
#define AVR32_ADCIFD_SEQCFG_CNVNB_MASK                        0x000f0000
#define AVR32_ADCIFD_SEQCFG_CNVNB_OFFSET                              16
#define AVR32_ADCIFD_SEQCFG_CNVNB_SIZE                                 4
#define AVR32_ADCIFD_SEQCFG_HWLA                                       1
#define AVR32_ADCIFD_SEQCFG_HWLA_MASK                         0x00000002
#define AVR32_ADCIFD_SEQCFG_HWLA_OFFSET                                1
#define AVR32_ADCIFD_SEQCFG_HWLA_SIZE                                  1
#define AVR32_ADCIFD_SEQCFG_MASK                              0x000f1707
#define AVR32_ADCIFD_SEQCFG_RESETVALUE                        0x00000000
#define AVR32_ADCIFD_SEQCFG_SA                                         0
#define AVR32_ADCIFD_SEQCFG_SA_MASK                           0x00000001
#define AVR32_ADCIFD_SEQCFG_SA_OFFSET                                  0
#define AVR32_ADCIFD_SEQCFG_SA_SIZE                                    1
#define AVR32_ADCIFD_SEQCFG_SRES                                      12
#define AVR32_ADCIFD_SEQCFG_SRES_MASK                         0x00001000
#define AVR32_ADCIFD_SEQCFG_SRES_OFFSET                               12
#define AVR32_ADCIFD_SEQCFG_SRES_SIZE                                  1
#define AVR32_ADCIFD_SEQCFG_STRGM                                      2
#define AVR32_ADCIFD_SEQCFG_STRGM_MASK                        0x00000004
#define AVR32_ADCIFD_SEQCFG_STRGM_OFFSET                               2
#define AVR32_ADCIFD_SEQCFG_STRGM_SIZE                                 1
#define AVR32_ADCIFD_SEQCFG_TRGSEL                                     8
#define AVR32_ADCIFD_SEQCFG_TRGSEL_MASK                       0x00000700
#define AVR32_ADCIFD_SEQCFG_TRGSEL_OFFSET                              8
#define AVR32_ADCIFD_SEQCFG_TRGSEL_SIZE                                3
#define AVR32_ADCIFD_SHTIM                                            16
#define AVR32_ADCIFD_SHTIM_MASK                               0x000f0000
#define AVR32_ADCIFD_SHTIM_OFFSET                                     16
#define AVR32_ADCIFD_SHTIM_SIZE                                        4
#define AVR32_ADCIFD_SMTRG                                             5
#define AVR32_ADCIFD_SMTRG_MASK                               0x00000020
#define AVR32_ADCIFD_SMTRG_OFFSET                                      5
#define AVR32_ADCIFD_SMTRG_SIZE                                        1
#define AVR32_ADCIFD_SR                                       0x00000008
#define AVR32_ADCIFD_SRC                                               8
#define AVR32_ADCIFD_SRC_MASK                                 0x00000f00
#define AVR32_ADCIFD_SRC_OFFSET                                        8
#define AVR32_ADCIFD_SRC_SIZE                                          4
#define AVR32_ADCIFD_SRES                                             12
#define AVR32_ADCIFD_SRES_MASK                                0x00001000
#define AVR32_ADCIFD_SRES_OFFSET                                      12
#define AVR32_ADCIFD_SRES_SIZE                                         1
#define AVR32_ADCIFD_SR_CBUSY                                         27
#define AVR32_ADCIFD_SR_CBUSY_MASK                            0x08000000
#define AVR32_ADCIFD_SR_CBUSY_OFFSET                                  27
#define AVR32_ADCIFD_SR_CBUSY_SIZE                                     1
#define AVR32_ADCIFD_SR_CSCNV                                         16
#define AVR32_ADCIFD_SR_CSCNV_MASK                            0x000f0000
#define AVR32_ADCIFD_SR_CSCNV_OFFSET                                  16
#define AVR32_ADCIFD_SR_CSCNV_SIZE                                     4
#define AVR32_ADCIFD_SR_EN                                            24
#define AVR32_ADCIFD_SR_EN_MASK                               0x01000000
#define AVR32_ADCIFD_SR_EN_OFFSET                                     24
#define AVR32_ADCIFD_SR_EN_SIZE                                        1
#define AVR32_ADCIFD_SR_LOVR                                           3
#define AVR32_ADCIFD_SR_LOVR_MASK                             0x00000008
#define AVR32_ADCIFD_SR_LOVR_OFFSET                                    3
#define AVR32_ADCIFD_SR_LOVR_SIZE                                      1
#define AVR32_ADCIFD_SR_MASK                                  0x0f0f00ff
#define AVR32_ADCIFD_SR_RESETVALUE                            0x00000000
#define AVR32_ADCIFD_SR_SBUSY                                         26
#define AVR32_ADCIFD_SR_SBUSY_MASK                            0x04000000
#define AVR32_ADCIFD_SR_SBUSY_OFFSET                                  26
#define AVR32_ADCIFD_SR_SBUSY_SIZE                                     1
#define AVR32_ADCIFD_SR_SEOC                                           2
#define AVR32_ADCIFD_SR_SEOC_MASK                             0x00000004
#define AVR32_ADCIFD_SR_SEOC_OFFSET                                    2
#define AVR32_ADCIFD_SR_SEOC_SIZE                                      1
#define AVR32_ADCIFD_SR_SEOS                                           1
#define AVR32_ADCIFD_SR_SEOS_MASK                             0x00000002
#define AVR32_ADCIFD_SR_SEOS_OFFSET                                    1
#define AVR32_ADCIFD_SR_SEOS_SIZE                                      1
#define AVR32_ADCIFD_SR_SMTRG                                          5
#define AVR32_ADCIFD_SR_SMTRG_MASK                            0x00000020
#define AVR32_ADCIFD_SR_SMTRG_OFFSET                                   5
#define AVR32_ADCIFD_SR_SMTRG_SIZE                                     1
#define AVR32_ADCIFD_SR_SSOS                                           0
#define AVR32_ADCIFD_SR_SSOS_MASK                             0x00000001
#define AVR32_ADCIFD_SR_SSOS_OFFSET                                    0
#define AVR32_ADCIFD_SR_SSOS_SIZE                                      1
#define AVR32_ADCIFD_SR_SUTD                                           6
#define AVR32_ADCIFD_SR_SUTD_MASK                             0x00000040
#define AVR32_ADCIFD_SR_SUTD_OFFSET                                    6
#define AVR32_ADCIFD_SR_SUTD_SIZE                                      1
#define AVR32_ADCIFD_SR_TBUSY                                         25
#define AVR32_ADCIFD_SR_TBUSY_MASK                            0x02000000
#define AVR32_ADCIFD_SR_TBUSY_OFFSET                                  25
#define AVR32_ADCIFD_SR_TBUSY_SIZE                                     1
#define AVR32_ADCIFD_SR_TTO                                            7
#define AVR32_ADCIFD_SR_TTO_MASK                              0x00000080
#define AVR32_ADCIFD_SR_TTO_OFFSET                                     7
#define AVR32_ADCIFD_SR_TTO_SIZE                                       1
#define AVR32_ADCIFD_SR_WM                                             4
#define AVR32_ADCIFD_SR_WM_MASK                               0x00000010
#define AVR32_ADCIFD_SR_WM_OFFSET                                      4
#define AVR32_ADCIFD_SR_WM_SIZE                                        1
#define AVR32_ADCIFD_SSOS                                              0
#define AVR32_ADCIFD_SSOS_MASK                                0x00000001
#define AVR32_ADCIFD_SSOS_OFFSET                                       0
#define AVR32_ADCIFD_SSOS_SIZE                                         1
#define AVR32_ADCIFD_SSR                                      0x00000010
#define AVR32_ADCIFD_SSR_LOVR                                          3
#define AVR32_ADCIFD_SSR_LOVR_MASK                            0x00000008
#define AVR32_ADCIFD_SSR_LOVR_OFFSET                                   3
#define AVR32_ADCIFD_SSR_LOVR_SIZE                                     1
#define AVR32_ADCIFD_SSR_MASK                                 0x000000ff
#define AVR32_ADCIFD_SSR_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_SSR_SEOC                                          2
#define AVR32_ADCIFD_SSR_SEOC_MASK                            0x00000004
#define AVR32_ADCIFD_SSR_SEOC_OFFSET                                   2
#define AVR32_ADCIFD_SSR_SEOC_SIZE                                     1
#define AVR32_ADCIFD_SSR_SEOS                                          1
#define AVR32_ADCIFD_SSR_SEOS_MASK                            0x00000002
#define AVR32_ADCIFD_SSR_SEOS_OFFSET                                   1
#define AVR32_ADCIFD_SSR_SEOS_SIZE                                     1
#define AVR32_ADCIFD_SSR_SMTRG                                         5
#define AVR32_ADCIFD_SSR_SMTRG_MASK                           0x00000020
#define AVR32_ADCIFD_SSR_SMTRG_OFFSET                                  5
#define AVR32_ADCIFD_SSR_SMTRG_SIZE                                    1
#define AVR32_ADCIFD_SSR_SSOS                                          0
#define AVR32_ADCIFD_SSR_SSOS_MASK                            0x00000001
#define AVR32_ADCIFD_SSR_SSOS_OFFSET                                   0
#define AVR32_ADCIFD_SSR_SSOS_SIZE                                     1
#define AVR32_ADCIFD_SSR_SUTD                                          6
#define AVR32_ADCIFD_SSR_SUTD_MASK                            0x00000040
#define AVR32_ADCIFD_SSR_SUTD_OFFSET                                   6
#define AVR32_ADCIFD_SSR_SUTD_SIZE                                     1
#define AVR32_ADCIFD_SSR_TTO                                           7
#define AVR32_ADCIFD_SSR_TTO_MASK                             0x00000080
#define AVR32_ADCIFD_SSR_TTO_OFFSET                                    7
#define AVR32_ADCIFD_SSR_TTO_SIZE                                      1
#define AVR32_ADCIFD_SSR_WM                                            4
#define AVR32_ADCIFD_SSR_WM_MASK                              0x00000010
#define AVR32_ADCIFD_SSR_WM_OFFSET                                     4
#define AVR32_ADCIFD_SSR_WM_SIZE                                       1
#define AVR32_ADCIFD_STARTUP                                           0
#define AVR32_ADCIFD_STARTUP_MASK                             0x0000001f
#define AVR32_ADCIFD_STARTUP_OFFSET                                    0
#define AVR32_ADCIFD_STARTUP_SIZE                                      5
#define AVR32_ADCIFD_STRGM                                             2
#define AVR32_ADCIFD_STRGM_MASK                               0x00000004
#define AVR32_ADCIFD_STRGM_OFFSET                                      2
#define AVR32_ADCIFD_STRGM_SIZE                                        1
#define AVR32_ADCIFD_STRIG                                             1
#define AVR32_ADCIFD_STRIG_MASK                               0x00000002
#define AVR32_ADCIFD_STRIG_OFFSET                                      1
#define AVR32_ADCIFD_STRIG_SIZE                                        1
#define AVR32_ADCIFD_SUTD                                              6
#define AVR32_ADCIFD_SUTD_MASK                                0x00000040
#define AVR32_ADCIFD_SUTD_OFFSET                                       6
#define AVR32_ADCIFD_SUTD_SIZE                                         1
#define AVR32_ADCIFD_SWRST                                             0
#define AVR32_ADCIFD_SWRST_MASK                               0x00000001
#define AVR32_ADCIFD_SWRST_OFFSET                                      0
#define AVR32_ADCIFD_SWRST_SIZE                                        1
#define AVR32_ADCIFD_TBUSY                                            25
#define AVR32_ADCIFD_TBUSY_MASK                               0x02000000
#define AVR32_ADCIFD_TBUSY_OFFSET                                     25
#define AVR32_ADCIFD_TBUSY_SIZE                                        1
#define AVR32_ADCIFD_TIM                                      0x00000020
#define AVR32_ADCIFD_TIM_MASK                                 0x000f001f
#define AVR32_ADCIFD_TIM_RESETVALUE                           0x00000000
#define AVR32_ADCIFD_TIM_SHTIM                                        16
#define AVR32_ADCIFD_TIM_SHTIM_MASK                           0x000f0000
#define AVR32_ADCIFD_TIM_SHTIM_OFFSET                                 16
#define AVR32_ADCIFD_TIM_SHTIM_SIZE                                    4
#define AVR32_ADCIFD_TIM_STARTUP                                       0
#define AVR32_ADCIFD_TIM_STARTUP_MASK                         0x0000001f
#define AVR32_ADCIFD_TIM_STARTUP_OFFSET                                0
#define AVR32_ADCIFD_TIM_STARTUP_SIZE                                  5
#define AVR32_ADCIFD_TRGSEL                                            8
#define AVR32_ADCIFD_TRGSEL_MASK                              0x00000700
#define AVR32_ADCIFD_TRGSEL_OFFSET                                     8
#define AVR32_ADCIFD_TRGSEL_SIZE                                       3
#define AVR32_ADCIFD_TSTART                                            3
#define AVR32_ADCIFD_TSTART_MASK                              0x00000008
#define AVR32_ADCIFD_TSTART_OFFSET                                     3
#define AVR32_ADCIFD_TSTART_SIZE                                       1
#define AVR32_ADCIFD_TSTOP                                             2
#define AVR32_ADCIFD_TSTOP_MASK                               0x00000004
#define AVR32_ADCIFD_TSTOP_OFFSET                                      2
#define AVR32_ADCIFD_TSTOP_SIZE                                        1
#define AVR32_ADCIFD_TTO                                               7
#define AVR32_ADCIFD_TTO_MASK                                 0x00000080
#define AVR32_ADCIFD_TTO_OFFSET                                        7
#define AVR32_ADCIFD_TTO_SIZE                                          1
#define AVR32_ADCIFD_VARIANT                                          16
#define AVR32_ADCIFD_VARIANT_MASK                             0x000f0000
#define AVR32_ADCIFD_VARIANT_OFFSET                                   16
#define AVR32_ADCIFD_VARIANT_SIZE                                      4
#define AVR32_ADCIFD_VERSION                                  0x00000040
#define AVR32_ADCIFD_VERSION_MASK                             0x000f0fff
#define AVR32_ADCIFD_VERSION_OFFSET                                    0
#define AVR32_ADCIFD_VERSION_RESETVALUE                       0x00000100
#define AVR32_ADCIFD_VERSION_SIZE                                     12
#define AVR32_ADCIFD_VERSION_VARIANT                                  16
#define AVR32_ADCIFD_VERSION_VARIANT_MASK                     0x000f0000
#define AVR32_ADCIFD_VERSION_VARIANT_OFFSET                           16
#define AVR32_ADCIFD_VERSION_VARIANT_SIZE                              4
#define AVR32_ADCIFD_VERSION_VERSION                                   0
#define AVR32_ADCIFD_VERSION_VERSION_MASK                     0x00000fff
#define AVR32_ADCIFD_VERSION_VERSION_OFFSET                            0
#define AVR32_ADCIFD_VERSION_VERSION_SIZE                             12
#define AVR32_ADCIFD_WCFG                                     0x00000028
#define AVR32_ADCIFD_WCFG_MASK                                0x00010f07
#define AVR32_ADCIFD_WCFG_MFM                                         16
#define AVR32_ADCIFD_WCFG_MFM_MASK                            0x00010000
#define AVR32_ADCIFD_WCFG_MFM_OFFSET                                  16
#define AVR32_ADCIFD_WCFG_MFM_SIZE                                     1
#define AVR32_ADCIFD_WCFG_RESETVALUE                          0x00000000
#define AVR32_ADCIFD_WCFG_SRC                                          8
#define AVR32_ADCIFD_WCFG_SRC_MASK                            0x00000f00
#define AVR32_ADCIFD_WCFG_SRC_OFFSET                                   8
#define AVR32_ADCIFD_WCFG_SRC_SIZE                                     4
#define AVR32_ADCIFD_WCFG_WM                                           0
#define AVR32_ADCIFD_WCFG_WM_MASK                             0x00000007
#define AVR32_ADCIFD_WCFG_WM_OFFSET                                    0
#define AVR32_ADCIFD_WCFG_WM_SIZE                                      3
#define AVR32_ADCIFD_WTH                                      0x0000002c
#define AVR32_ADCIFD_WTH_HT                                           16
#define AVR32_ADCIFD_WTH_HT_MASK                              0x03ff0000
#define AVR32_ADCIFD_WTH_HT_OFFSET                                    16
#define AVR32_ADCIFD_WTH_HT_SIZE                                      10
#define AVR32_ADCIFD_WTH_LT                                            0
#define AVR32_ADCIFD_WTH_LT_MASK                              0x000003ff
#define AVR32_ADCIFD_WTH_LT_OFFSET                                     0
#define AVR32_ADCIFD_WTH_LT_SIZE                                      10
#define AVR32_ADCIFD_WTH_MASK                                 0x03ff03ff
#define AVR32_ADCIFD_WTH_RESETVALUE                           0x00000000




#ifdef __AVR32_ABI_COMPILER__


typedef struct avr32_adcifd_cr_t {
    unsigned int                 :22;
    unsigned int dis             : 1;
    unsigned int en              : 1;
    unsigned int                 : 4;
    unsigned int tstart          : 1;
    unsigned int tstop           : 1;
    unsigned int strig           : 1;
    unsigned int swrst           : 1;
} avr32_adcifd_cr_t;



typedef struct avr32_adcifd_cfg_t {
    unsigned int                 :31;
    unsigned int prm             : 1;
} avr32_adcifd_cfg_t;



typedef struct avr32_adcifd_sr_t {
    unsigned int                 : 4;
    unsigned int cbusy           : 1;
    unsigned int sbusy           : 1;
    unsigned int tbusy           : 1;
    unsigned int en              : 1;
    unsigned int                 : 4;
    unsigned int cscnv           : 4;
    unsigned int                 : 8;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_sr_t;



typedef struct avr32_adcifd_scr_t {
    unsigned int                 :24;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_scr_t;



typedef struct avr32_adcifd_ssr_t {
    unsigned int                 :24;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_ssr_t;



typedef struct avr32_adcifd_seqcfg_t {
    unsigned int                 :12;
    unsigned int cnvnb           : 4;
    unsigned int                 : 3;
    unsigned int sres            : 1;
    unsigned int                 : 1;
    unsigned int trgsel          : 3;
    unsigned int                 : 5;
    unsigned int strgm           : 1;
    unsigned int hwla            : 1;
    unsigned int sa              : 1;
} avr32_adcifd_seqcfg_t;



typedef struct avr32_adcifd_csplc_t {
    unsigned int cnv7            : 4;
    unsigned int cnv6            : 4;
    unsigned int cnv5            : 4;
    unsigned int cnv4            : 4;
    unsigned int cnv3            : 4;
    unsigned int cnv2            : 4;
    unsigned int cnv1            : 4;
    unsigned int cnv0            : 4;
} avr32_adcifd_csplc_t;



typedef struct avr32_adcifd_csphc_t {
    unsigned int cnv15           : 4;
    unsigned int cnv14           : 4;
    unsigned int cnv13           : 4;
    unsigned int cnv12           : 4;
    unsigned int cnv11           : 4;
    unsigned int cnv10           : 4;
    unsigned int cnv9            : 4;
    unsigned int cnv8            : 4;
} avr32_adcifd_csphc_t;



typedef struct avr32_adcifd_tim_t {
    unsigned int                 :12;
    unsigned int shtim           : 4;
    unsigned int                 :11;
    unsigned int startup         : 5;
} avr32_adcifd_tim_t;



typedef struct avr32_adcifd_itimer_t {
    unsigned int                 :16;
    unsigned int itmc            :16;
} avr32_adcifd_itimer_t;



typedef struct avr32_adcifd_wcfg_t {
    unsigned int                 :15;
    unsigned int mfm             : 1;
    unsigned int                 : 4;
    unsigned int src             : 4;
    unsigned int                 : 5;
    unsigned int wm              : 3;
} avr32_adcifd_wcfg_t;



typedef struct avr32_adcifd_wth_t {
    unsigned int                 : 6;
    unsigned int ht              :10;
    unsigned int                 : 6;
    unsigned int lt              :10;
} avr32_adcifd_wth_t;



typedef struct avr32_adcifd_lcv_t {
    unsigned int                 :16;
    unsigned int lcv             :16;
} avr32_adcifd_lcv_t;



typedef struct avr32_adcifd_ier_t {
    unsigned int                 :24;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_ier_t;



typedef struct avr32_adcifd_idr_t {
    unsigned int                 :24;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_idr_t;



typedef struct avr32_adcifd_imr_t {
    unsigned int                 :24;
    unsigned int tto             : 1;
    unsigned int sutd            : 1;
    unsigned int smtrg           : 1;
    unsigned int wm              : 1;
    unsigned int lovr            : 1;
    unsigned int seoc            : 1;
    unsigned int seos            : 1;
    unsigned int ssos            : 1;
} avr32_adcifd_imr_t;



typedef struct avr32_adcifd_version_t {
    unsigned int                 :12;
    unsigned int variant         : 4;
    unsigned int                 : 4;
    unsigned int version         :12;
} avr32_adcifd_version_t;



typedef struct avr32_adcifd_parameter_t {
    unsigned int                 :16;
    unsigned int n               : 8;
    unsigned int m               : 8;
} avr32_adcifd_parameter_t;



typedef struct avr32_adcifd_t {
  union {
          unsigned long                  cr        ;//0x0000
          avr32_adcifd_cr_t              CR        ;
  };
  union {
          unsigned long                  cfg       ;//0x0004
          avr32_adcifd_cfg_t             CFG       ;
  };
  union {
    const unsigned long                  sr        ;//0x0008
    const avr32_adcifd_sr_t              SR        ;
  };
  union {
          unsigned long                  scr       ;//0x000c
          avr32_adcifd_scr_t             SCR       ;
  };
  union {
          unsigned long                  ssr       ;//0x0010
          avr32_adcifd_ssr_t             SSR       ;
  };
  union {
          unsigned long                  seqcfg    ;//0x0014
          avr32_adcifd_seqcfg_t          SEQCFG    ;
  };
  union {
          unsigned long                  csplc     ;//0x0018
          avr32_adcifd_csplc_t           CSPLC     ;
  };
  union {
          unsigned long                  csphc     ;//0x001c
          avr32_adcifd_csphc_t           CSPHC     ;
  };
  union {
          unsigned long                  tim       ;//0x0020
          avr32_adcifd_tim_t             TIM       ;
  };
  union {
          unsigned long                  itimer    ;//0x0024
          avr32_adcifd_itimer_t          ITIMER    ;
  };
  union {
          unsigned long                  wcfg      ;//0x0028
          avr32_adcifd_wcfg_t            WCFG      ;
  };
  union {
          unsigned long                  wth       ;//0x002c
          avr32_adcifd_wth_t             WTH       ;
  };
  union {
    const unsigned long                  lcv       ;//0x0030
    const avr32_adcifd_lcv_t             LCV       ;
  };
  union {
          unsigned long                  ier       ;//0x0034
          avr32_adcifd_ier_t             IER       ;
  };
  union {
          unsigned long                  idr       ;//0x0038
          avr32_adcifd_idr_t             IDR       ;
  };
  union {
    const unsigned long                  imr       ;//0x003c
    const avr32_adcifd_imr_t             IMR       ;
  };
  union {
    const unsigned long                  version   ;//0x0040
    const avr32_adcifd_version_t         VERSION   ;
  };
  union {
    const unsigned long                  parameter ;//0x0044
    const avr32_adcifd_parameter_t       PARAMETER ;
  };
} avr32_adcifd_t;



/*#ifdef __AVR32_ABI_COMPILER__*/
#endif

/*#ifdef AVR32_ADCIFD_100_H_INCLUDED*/
#endif

