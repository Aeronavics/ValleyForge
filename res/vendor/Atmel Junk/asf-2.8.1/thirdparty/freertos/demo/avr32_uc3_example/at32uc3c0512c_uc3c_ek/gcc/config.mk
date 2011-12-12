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
PRJ_PATH = ../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr3fp

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3c0512c

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = avr32_services_freertos_example_uc3c_ek.elf

# List of C source files.
CSRCS = \
       avr32/drivers/pm/power_clocks_lib.c                \
       avr32/drivers/pm/pm_uc3c.c                         \
       thirdparty/freertos/demo/avr32_uc3_example/main.c  \
       thirdparty/freertos/demo/common/minimal/AltBlock.c \
       thirdparty/freertos/demo/common/minimal/BlockQ.c   \
       thirdparty/freertos/demo/common/minimal/dynamic.c  \
       thirdparty/freertos/demo/avr32_uc3_example/partest/ParTest.c \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/port.c \
       thirdparty/freertos/source/timers.c                \
       thirdparty/freertos/source/portable/memmang/heap_3.c \
       thirdparty/freertos/demo/common/minimal/blocktim.c \
       thirdparty/freertos/demo/common/minimal/crhook.c   \
       thirdparty/freertos/source/queue.c                 \
       thirdparty/freertos/demo/common/minimal/crflash.c  \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/read.c \
       avr32/drivers/usart/usart.c                        \
       thirdparty/freertos/demo/avr32_uc3_example/serial/serial.c \
       avr32/drivers/intc/intc.c                          \
       thirdparty/freertos/demo/common/minimal/flop.c     \
       thirdparty/freertos/demo/common/minimal/flash.c    \
       thirdparty/freertos/demo/common/minimal/countsem.c \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/tc/tc.c                              \
       thirdparty/freertos/source/list.c                  \
       avr32/drivers/flashc/flashc.c                      \
       thirdparty/freertos/demo/common/minimal/AltPollQ.c \
       thirdparty/freertos/demo/common/minimal/semtest.c  \
       thirdparty/freertos/demo/common/minimal/comtest.c  \
       thirdparty/freertos/demo/common/minimal/death.c    \
       thirdparty/freertos/demo/common/minimal/QPeek.c    \
       thirdparty/freertos/demo/common/minimal/AltQTest.c \
       avr32/boards/stk600/rcuc3l0/led.c                         \
       thirdparty/freertos/demo/common/minimal/integer.c  \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/write.c \
       thirdparty/freertos/demo/common/minimal/AltBlckQ.c \
       thirdparty/freertos/demo/common/minimal/PollQ.c    \
       thirdparty/freertos/source/croutine.c              \
       thirdparty/freertos/demo/common/minimal/GenQTest.c \
       avr32/drivers/scif/scif_uc3c.c                     \
       thirdparty/freertos/source/tasks.c                 \
       thirdparty/freertos/demo/common/minimal/recmutex.c

# List of assembler source files.
ASSRCS = \
       avr32/utils/startup/trampoline_uc3.S               \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/exception.S

# List of include paths.
INC_PATH = \
       thirdparty/freertos/demo/avr32_uc3_example         \
       thirdparty/freertos/source/include                 \
       avr32/boards/stk600/rcuc3l0                                \
       avr32/utils/preprocessor                           \
       thirdparty/freertos/demo/common/include            \
       avr32/drivers/scif                                 \
       avr32/drivers/tc                                   \
       common/boards                                      \
       avr32/boards                                       \
       avr32/drivers/usart                                \
       avr32/drivers/flashc                               \
       thirdparty/freertos/demo/avr32_uc3_example/at32uc3c0512c_uc3c_ek \
       avr32/utils                                        \
       thirdparty/freertos/source/portable/gcc/avr32_uc3  \
       avr32/drivers/gpio                                 \
       common/utils                                       \
       avr32/drivers/pm                                   \
       avr32/drivers/intc \
       ./thirdparty/freertos/demo/avr32_uc3_example/at32uc3c0512c_uc3c_ek/gcc

# Additional search paths for libraries.
LIB_PATH = 

# List of libraries to use during linking.
LIBS = 

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3c/0512c/gcc/link_uc3c0512c.lds

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
       -D BOARD=STK600_RCUC3L0

# Extra flags to use when linking
LDFLAGS = \
        -Wl,-e,_trampoline