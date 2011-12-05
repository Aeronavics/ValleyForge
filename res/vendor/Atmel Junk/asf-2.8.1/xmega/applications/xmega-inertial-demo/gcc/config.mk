# Copyright (C) 2010 Atmel Corporation. All rights reserved.
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
PRJ_PATH = ../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega256a3bu

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = xmega_applications_xmega-a3bu_avrsbin1-demo.elf

# C source files located from the top-level source directory
CSRCS = \
       common/services/clock/xmega/sysclk.c               \
       common/applications/sensors/inertial_demo/main.c   \
       xmega/drivers/twi/twis.c                           \
       common/services/usb/class/cdc/device/udi_cdc.c     \
       xmega/drivers/ioport/ioport.c                      \
       common/services/sensors/sensor_bus.c               \
       common/boards/sensors_xplained/sensors_xplained.c  \
       common/utils/stdio/read.c                          \
       common/services/sleepmgr/xmega/sleepmgr.c          \
       xmega/boards/xmega_a3bu_xplained/init.c            \
       common/services/sensors/sensor_nvram.c             \
       xmega/drivers/usb/usb_device.c                     \
       xmega/drivers/twi/twim.c                           \
       xmega/drivers/nvm/nvm.c                            \
       common/services/sensors/sensor_platform.c          \
       common/services/usb/class/cdc/device/udi_cdc_desc.c \
       common/utils/stdio/write.c                         \
       common/services/sensors/physics/physics.c          \
       common/services/usb/udc/udc.c                      \
       common/utils/stdio/stdio_usb/stdio_usb.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/cpu/ccp.s                            \
       xmega/drivers/nvm/nvm_asm.s

# Include path located from the top-level source directory
INC_PATH = \
       common/services/usb/class/cdc/device               \
       xmega/drivers/ioport                               \
       common/services/sensors                            \
       xmega/utils                                        \
       common/services                                    \
       common/services/twi                                \
       common/utils/stdio/stdio_usb                       \
       xmega/drivers/nvm                                  \
       common/services/sleepmgr                           \
       common/utils                                       \
       common/services/usb/class/cdc                      \
       common/services/clock                              \
       xmega/applications/xmega-inertial-demo/conf        \
       common/services/usb/udc                            \
       common/services/usb                                \
       xmega/boards                                       \
       common/services/gpio                               \
       xmega/drivers/twi                                  \
       xmega/boards/xmega_a3bu_xplained                   \
       xmega/drivers/usb                                  \
       common/boards                                      \
       xmega/utils/preprocessor                           \
       xmega/drivers/sleep                                \
       common/services/sensors/module_config              \
       xmega/drivers/cpu \
       ./xmega/applications/xmega-inertial-demo/gcc      

# Library paths from the top-level source directory
LIB_PATH =  \
       thirdparty/sensors/libs/gcc                       

# Libraries to link with the project
LIBS =  \
       sensors-atxmega256a3bu-debug                       \
       m                                                 

# Additional options for debugging. By default the common Makefile.in will
# add -gdwarf-2.
DBGFLAGS = 

# Optimization settings
OPTIMIZATION = -Os

# Extra flags used when creating an EEPROM Intel HEX file. By default the
# common Makefile.in will add -j .eeprom
# --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0.
EEPROMFLAGS = 

# Extra flags used when creating an Intel HEX file. By default the common
# Makefile.in will add -R .eeprom -R .usb_descriptor_table.
FLASHFLAGS = 

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
       -D CONFIG_NVM_IGNORE_XMEGA_A3_D3_REVB_ERRATA       \
       -D BOARD=XMEGA_A3BU_XPLAINED                       \
       -D EXT_BOARD=SENSORS_XPLAINED_INERTIAL_1           \
       -D CONF_STDIO_REDIRECT

# Extra flags to use when linking
LDFLAGS =  \
       -Wl,-u,vfprintf -lprintf_flt                       \
       -Wl,--section-start=.BOOT=0x40000                 
