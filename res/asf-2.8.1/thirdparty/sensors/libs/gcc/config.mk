# Copyright (C) 2011 Atmel Corporation. All rights reserved.
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


# ASF platform & MCU driver definitions

mems_drv_path := common/services/sensors/drivers

ifeq ($(mcu_arch),avr)
  MCU  = $(mcu_series)
endif

ifeq ($(mcu_series),at32uc3a)
  ARCH = ucr2
  PART = uc3a0512
endif

ifeq ($(mcu_series),at32uc3a3)
  ARCH = ucr2
  PART = uc3a3256
endif

ifeq ($(mcu_series),at32uc3b)
  ARCH = ucr1
  PART = uc3b0256
endif

ifeq ($(mcu_series),at32uc3c)
  ARCH = ucr3fp
  PART = uc3c0512c
endif

ifeq ($(mcu_series),at32uc3l)
  ARCH = ucr3
  PART = uc3l064
endif

# MCU-Specific driver header file paths
ifeq ($(strip $(mcu_family)),xmega)
INC_PATH = \
  common/services/gpio/                \
  xmega/drivers/cpu/                   \
  xmega/drivers/ioport/                \
  xmega/drivers/nvm/
endif

ifeq ($(strip $(mcu_family)),avr32)
INC_PATH = \
  avr32/drivers/gpio/                  \
  avr32/drivers/intc/                  \
  avr32/drivers/cpu/cycle_counter/     \
  avr32/drivers/flashc/                \
  avr32/drivers/flashcdw/
endif

# Common API header file paths
INC_PATH += \
  $(mcu_family)/utils/                 \
  $(mcu_family)/utils/preprocessor/    \
  common/interrupt/                    \
  common/utils/                        \
  common/services/

# MEMS sensor driver source files
CSRCS += \
  common/services/sensors/sensor.c       \
  $(mems_drv_path)/akm/ak8975.c          \
  $(mems_drv_path)/bosch/bma020.c        \
  $(mems_drv_path)/bosch/bma150.c        \
  $(mems_drv_path)/bosch/bma180.c        \
  $(mems_drv_path)/bosch/bmp085.c        \
  $(mems_drv_path)/honeywell/hmc5883l.c  \
  $(mems_drv_path)/invensense/imu3000.c  \
  $(mems_drv_path)/invensense/itg3200.c  \
  $(mems_drv_path)/kionix/kxtf9.c
# $(mems_drv_path)/osram/sfh7770.c

# Base GCC optimization levels for all library builds
ifeq ($(strip $(mcu_arch)),avr32)
  OPTIMIZATION = -fno-common -ffunction-sections
else
# OPTIMIZATION = -fpack-struct -fshort-enums
endif

# Extra flags to use when archiving.
ARFLAGS =

# Extra flags to use when preprocessing.
CPPFLAGS = -D CONFIG_NVM_IGNORE_XMEGA_A3_D3_REVB_ERRATA

# MEMS sensor driver library targets
ifdef debug
  OPTIMIZATION += -O0
  TARGET        = libsensors-$(mcu_series)-debug.a
else
  OPTIMIZATION += -O3
  TARGET        = libsensors-$(mcu_series)-release.a
endif
