# Copyright (C) 2009 - 2010 Atmel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
# from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
# Atmel AVR product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr2

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3a3256

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = avr32_services_graphics_ijg_example_evk1104.elf

# List of C source files.
CSRCS = \
       thirdparty/ijg/jcmarker.c                          \
       thirdparty/ijg/jerror.c                            \
       avr32/drivers/pm/power_clocks_lib.c                \
       thirdparty/ijg/example/ijg_example.c               \
       thirdparty/ijg/jdapistd.c                          \
       thirdparty/ijg/jddctmgr.c                          \
       thirdparty/ijg/jidctred.c                          \
       thirdparty/ijg/jquant2.c                           \
       thirdparty/ijg/jdmerge.c                           \
       thirdparty/ijg/jfdctflt.c                          \
       thirdparty/ijg/jfdctint.c                          \
       thirdparty/ijg/jcmaster.c                          \
       thirdparty/ijg/jchuff.c                            \
       thirdparty/ijg/jcprepct.c                          \
       thirdparty/ijg/jcdctmgr.c                          \
       thirdparty/ijg/jutils.c                            \
       avr32/components/display/et024006dhu/et024006dhu.c \
       thirdparty/ijg/jmemnobs.c                          \
       thirdparty/ijg/jidctint.c                          \
       thirdparty/ijg/jccolor.c                           \
       avr32/drivers/ebi/smc/smc.c                        \
       thirdparty/ijg/jdpostct.c                          \
       avr32/drivers/usart/usart.c                        \
       thirdparty/ijg/jcinit.c                            \
       thirdparty/ijg/jidctflt.c                          \
       avr32/drivers/intc/intc.c                          \
       thirdparty/ijg/jidctfst.c                          \
       thirdparty/ijg/jdcolor.c                           \
       thirdparty/ijg/jccoefct.c                          \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/pm/pm.c                              \
       thirdparty/ijg/jcomapi.c                           \
       thirdparty/ijg/example/jdatasrc.c                  \
       thirdparty/ijg/jcparam.c                           \
       thirdparty/ijg/jctrans.c                           \
       thirdparty/ijg/jcmainct.c                          \
       avr32/drivers/flashc/flashc.c                      \
       thirdparty/ijg/jdsample.c                          \
       thirdparty/ijg/jdhuff.c                            \
       thirdparty/ijg/jdmarker.c                          \
       thirdparty/ijg/jcapistd.c                          \
       thirdparty/ijg/jcphuff.c                           \
       thirdparty/ijg/jdphuff.c                           \
       avr32/drivers/pm/pm_conf_clocks.c                  \
       thirdparty/ijg/jquant1.c                           \
       thirdparty/ijg/jdtrans.c                           \
       thirdparty/ijg/jfdctfst.c                          \
       thirdparty/ijg/jdapimin.c                          \
       thirdparty/ijg/jcsample.c                          \
       thirdparty/ijg/jmemmgr.c                           \
       thirdparty/ijg/jdmainct.c                          \
       thirdparty/ijg/jdcoefct.c                          \
       thirdparty/ijg/jdmaster.c                          \
       avr32/drivers/ebi/sdramc/sdramc.c                  \
       avr32/services/delay/delay.c                       \
       avr32/utils/debug/print_funcs.c                    \
       thirdparty/ijg/jdinput.c

# List of assembler source files.
ASSRCS = \
       avr32/drivers/intc/exception.S                     \
       avr32/utils/startup/trampoline_uc3.S               \
       thirdparty/ijg/example/crt0.S

# List of include paths.
INC_PATH = \
       avr32/components/display/et024006dhu               \
       avr32/utils/preprocessor                           \
       avr32/utils/debug                                  \
       avr32/drivers/ebi/smc                              \
       common/boards                                      \
       thirdparty/ijg/example                             \
       avr32/drivers/ebi/sdramc                           \
       avr32/drivers/usart                                \
       avr32/drivers/flashc                               \
       avr32/boards/evk1104                               \
       avr32/boards                                       \
       avr32/utils                                        \
       avr32/drivers/cpu/cycle_counter                    \
       avr32/services/delay                               \
       avr32/drivers/gpio                                 \
       avr32/drivers/intc                                 \
       avr32/drivers/pm                                   \
       common/utils                                       \
       avr32/components/memory/sdram                      \
       thirdparty/ijg \
       ./thirdparty/ijg/example/at32uc3a3256_evk1104/gcc 

# Additional search paths for libraries.
LIB_PATH = 

# List of libraries to use during linking.
LIBS = 

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = thirdparty/ijg/example/at32uc3a3256_evk1104/link_uc3a3256_extsdram.lds

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -Os

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D BOARD=EVK1104

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles -Wl,-e,_trampoline
