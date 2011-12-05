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
PRJ_PATH = ../../../../../../../../../..

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
TARGET = common_services_usb_class_dfu_atmel_device_bootloader_avr32_uc3c.elf

# List of C source files.
CSRCS = \
       avr32/drivers/pm/power_clocks_lib.c                \
       common/services/clock/uc3c/osc.c                   \
       avr32/services/freq_detect/freq_detect.c           \
       avr32/drivers/ast/ast.c                            \
       avr32/drivers/flashc/flashc.c                      \
       common/services/isp/flip/uc3/isp.c                 \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/at32uc3c/sysclk_auto.c \
       common/services/usb/class/dfu_flip/device/udi_dfu_atmel.c \
       avr32/drivers/usbc/usbc_device.c                   \
       common/services/clock/uc3c/sysclk.c                \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/intc/intc.c \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/main.c \
       avr32/drivers/pm/pm_uc3c.c                         \
       common/services/clock/uc3c/pll.c                   \
       avr32/drivers/scif/scif_uc3c.c                     \
       common/services/usb/udc/udc.c                      \
       common/services/usb/class/dfu_flip/device/udi_dfu_atmel_desc.c

# List of assembler source files.
ASSRCS = \
       common/services/isp/flip/uc3/boot.S

# List of include paths.
INC_PATH = \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/intc \
       avr32/boards/dummy                                 \
       avr32/drivers/scif                                 \
       common/services/usb/class/dfu_flip/device          \
       avr32/boards                                       \
       avr32/drivers/usbc                                 \
       avr32/drivers/pm                                   \
       common/services/usb/class/dfu_flip                 \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/conf \
       avr32/drivers/flashc                               \
       avr32/drivers/ast                                  \
       avr32/utils                                        \
       common/utils                                       \
       avr32/services/freq_detect                         \
       common/services/clock                              \
       common/services/usb/udc                            \
       common/services/usb                                \
       avr32/drivers/cpu/cycle_counter                    \
       common/services/isp/flip/uc3                       \
       common/services/usb/class/dfu_flip/device/bootloader/avr32/at32uc3c/iar \
       common/boards                                      \
       common/services/usb/class/dfu_flip/device/bootloader/avr32 \
       avr32/utils/preprocessor                           \
       common/services/isp/flip \
       ./common/services/usb/class/dfu_flip/device/bootloader/avr32/at32uc3c/gcc

# Additional search paths for libraries.
LIB_PATH = 

# List of libraries to use during linking.
LIBS = 

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = common/services/usb/class/dfu_flip/device/bootloader/avr32/at32uc3c/gcc/link_at32uc3c-isp.lds

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
       -D BOARD=DUMMY_BOARD

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles
