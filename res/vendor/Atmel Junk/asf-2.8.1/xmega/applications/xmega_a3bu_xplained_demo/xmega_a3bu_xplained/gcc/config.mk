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
PRJ_PATH = ../../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega256a3bu

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = xmega_applications_xmega_a3bu_xplained_demo_xmega_a3bu_xplained.elf

# C source files located from the top-level source directory
CSRCS = \
       xmega/applications/xmega_a3bu_xplained_demo/timezone.c \
       xmega/applications/xmega_a3bu_xplained_demo/production_date.c \
       xmega/drivers/usart/usart.c                        \
       xmega/drivers/usb/usb_device.c                     \
       xmega/applications/xmega_a3bu_xplained_demo/date_time.c \
       xmega/drivers/adc/adc.c                            \
       common/services/gfx_mono/gfx_mono_framebuffer.c    \
       common/services/usb/udc/udc.c                      \
       common/services/usb/class/cdc/device/udi_cdc_desc.c \
       common/services/clock/xmega/sysclk.c               \
       common/services/gfx_mono/gfx_mono_c12832_a1z.c     \
       xmega/applications/xmega_a3bu_xplained_demo/main.c \
       common/services/sleepmgr/xmega/sleepmgr.c          \
       xmega/boards/xmega_a3bu_xplained/init.c            \
       xmega/applications/xmega_a3bu_xplained_demo/ntc_sensor.c \
       xmega/applications/xmega_a3bu_xplained_demo/cdc.c  \
       xmega/drivers/nvm/nvm.c                            \
       common/services/calendar/calendar.c                \
       common/services/spi/xmega_usart_spi/usart_spi.c    \
       xmega/drivers/ioport/ioport.c                      \
       common/services/gfx_mono/gfx_mono_text.c           \
       common/services/gfx_mono/sysfont.c                 \
       common/services/gfx_mono/gfx_mono_spinctrl.c       \
       xmega/applications/xmega_a3bu_xplained_demo/bitmaps.c \
       common/components/display/st7565r/st7565r.c        \
       common/services/usb/class/cdc/device/udi_cdc.c     \
       xmega/applications/xmega_a3bu_xplained_demo/adc_sensors.c \
       common/services/gfx_mono/gfx_mono_generic.c        \
       common/services/gfx_mono/gfx_mono_menu.c           \
       xmega/applications/xmega_a3bu_xplained_demo/qtouch/touch.c \
       xmega/applications/xmega_a3bu_xplained_demo/lightsensor.c \
       xmega/drivers/rtc32/rtc32.c                        \
       xmega/applications/xmega_a3bu_xplained_demo/keyboard.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/nvm/nvm_asm.s                        \
       xmega/drivers/cpu/ccp.s                            \
       xmega/applications/xmega_a3bu_xplained_demo/qtouch/qt_asm_xmega.s

# Include path located from the top-level source directory
INC_PATH = \
       common/services/usb/class/cdc/device               \
       xmega/drivers/pmic                                 \
       xmega/drivers/ioport                               \
       xmega/utils                                        \
       common/services/gfx_mono                           \
       common/services/calendar                           \
       common/services/gpio                               \
       xmega/drivers/usart                                \
       xmega/drivers/nvm                                  \
       common/services/sleepmgr                           \
       common/utils                                       \
       xmega/drivers/rtc32                                \
       xmega/drivers/adc                                  \
       common/components/display/st7565r                  \
       common/services/usb/class/cdc                      \
       xmega/applications/xmega_a3bu_xplained_demo/qtouch \
       common/services/clock                              \
       xmega/applications/xmega_a3bu_xplained_demo/xmega_a3bu_xplained \
       common/services/usb/udc                            \
       common/services/usb                                \
       xmega/boards                                       \
       xmega/applications/xmega_a3bu_xplained_demo        \
       xmega/boards/xmega_a3bu_xplained                   \
       xmega/drivers/usb                                  \
       common/services/spi                                \
       common/boards                                      \
       xmega/utils/preprocessor                           \
       xmega/drivers/sleep                                \
       xmega/drivers/cpu \
       ./xmega/applications/xmega_a3bu_xplained_demo/xmega_a3bu_xplained/gcc

# Library paths from the top-level source directory
LIB_PATH =  \
       xmega/applications/xmega_a3bu_xplained_demo/qtouch

# Libraries to link with the project
LIBS =  \
       avrxmega6g1-4qt-k-0rs                              \
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
       -D SNS=F                                           \
       -D _SNS1_SNSK1_SAME_PORT_                          \
       -D QTOUCH_STUDIO_MASKS=1                           \
       -D GFX_MONO_C12832_A1Z=1                           \
       -D NUMBER_OF_PORTS=1                               \
       -D SNSK=F                                          \
       -D BOARD=XMEGA_A3BU_XPLAINED                       \
       -D QT_NUM_CHANNELS=4                               \
       -D _QTOUCH_                                        \
       -D QT_DELAY_CYCLES=1

# Extra flags to use when linking
LDFLAGS =  \
       -Wl,--section-start=.BOOT=0x40000                 
