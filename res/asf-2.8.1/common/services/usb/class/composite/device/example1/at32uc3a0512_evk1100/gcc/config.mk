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
PRJ_PATH = ../../../../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr2

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3a0512

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = common_services_usb_class_composite_device_example_hidms_msc_evk1100.elf

# List of C source files.
CSRCS = \
       avr32/drivers/pm/power_clocks_lib.c                \
       common/services/usb/class/composite/device/example1/at32uc3a0512_evk1100/ui.c \
       avr32/drivers/spi/spi.c                            \
       common/components/memory/data_flash/at45dbx/at45dbx_mem.c \
       common/services/usb/udc/udc.c                      \
       common/services/usb/class/composite/device/udi_composite_desc.c \
       avr32/drivers/eic/eic.c                            \
       common/components/memory/data_flash/at45dbx/at45dbx.c \
       common/services/sleepmgr/uc3/sleepmgr.c            \
       common/services/clock/uc3a0_a1/sysclk.c            \
       avr32/drivers/intc/intc.c                          \
       common/services/usb/class/hid/device/mouse/udi_hid_mouse.c \
       avr32/drivers/gpio/gpio.c                          \
       avr32/boards/evk1100/led.c                         \
       avr32/drivers/pm/pm.c                              \
       avr32/boards/evk1100/init.c                        \
       avr32/drivers/flashc/flashc.c                      \
       common/services/storage/ctrl_access/ctrl_access.c  \
       common/services/usb/class/composite/device/example1/main.c \
       avr32/drivers/pm/pm_conf_clocks.c                  \
       common/services/usb/class/msc/device/udi_msc.c     \
       common/services/usb/class/hid/device/udi_hid.c     \
       common/components/memory/virtual_mem/virtual_mem.c \
       avr32/drivers/usbb/usbb_device.c                   \
       common/services/spi/uc3_spi/spi_master.c

# List of assembler source files.
ASSRCS = \
       avr32/utils/startup/startup_uc3.S                  \
       avr32/utils/startup/trampoline_uc3.S               \
       avr32/drivers/intc/exception.S

# List of include paths.
INC_PATH = \
       common/components/memory/data_flash/at45dbx        \
       avr32/components/joystick/skrhabe010               \
       common/services/usb/class/composite/device/example1 \
       avr32/boards                                       \
       common/services/spi/uc3_spi                        \
       avr32/drivers/usbb                                 \
       avr32/drivers/pm                                   \
       avr32/drivers/eic                                  \
       common/components/memory/virtual_mem               \
       common/services/usb/class/composite/device/example1/at32uc3a0512_evk1100 \
       avr32/utils                                        \
       avr32/boards/evk1100                               \
       avr32/drivers/gpio                                 \
       common/services/sleepmgr                           \
       common/utils                                       \
       common/services/usb/class/composite/device         \
       avr32/drivers/spi                                  \
       common/services/usb/class/hid/device/mouse         \
       common/services/usb/class/msc/device               \
       common/services/clock                              \
       common/services/usb/udc                            \
       common/services/usb                                \
       common/services/usb/class/hid/device               \
       common/services/spi                                \
       common/boards                                      \
       avr32/drivers/flashc                               \
       common/services/usb/class/msc                      \
       avr32/utils/preprocessor                           \
       common/services/usb/class/hid                      \
       avr32/drivers/intc                                 \
       common/services/storage/ctrl_access \
       ./common/services/usb/class/composite/device/example1/at32uc3a0512_evk1100/gcc

# Additional search paths for libraries.
LIB_PATH = 

# List of libraries to use during linking.
LIBS = 

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3a/0512/gcc/link_uc3a0512.lds

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
       -D ACCESS_USB_ENABLED                              \
       -D VIRTUAL_MEMORY_ENABLE                           \
       -D BOARD=EVK1100                                   \
       -D AT45DBX_ENABLE

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles -Wl,-e,_trampoline
