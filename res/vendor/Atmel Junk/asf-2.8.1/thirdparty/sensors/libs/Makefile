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


tool       := gcc


avr32_mcu  := at32uc3a at32uc3a3 at32uc3b at32uc3c at32uc3l
xmega_mcu  := atxmega32a4 atxmega128a1 atxmega256a3 atxmega256a3b \
              atxmega32a4u atxmega256a3u atxmega256a3bu
mega_mcu   := atmega1284p


ifeq ($(strip $(shell uname -o)),Cygwin)
ewavr_build   := "$$PROGRAMFILES/IAR Systems/Embedded Workbench 6.0/common/bin/IarBuild.exe"
ewavr32_build := "$$PROGRAMFILES/IAR Systems/Embedded Workbench 5.6/common/bin/IarBuild.exe"
else
ewavr_build   := "%PROGRAMFILES%/IAR Systems/Embedded Workbench 6.0/common/bin/IarBuild.exe"
ewavr32_build := "%PROGRAMFILES%/IAR Systems/Embedded Workbench 5.6/common/bin/IarBuild.exe"
endif


.PHONY: all
all: $(avr32_mcu) $(xmega_mcu)


.PHONY: clean
clean:
ifeq ($(tool),iar)
	rm -rf iar/release iar/debug iar/Settings iar/*.dep
else
	rm -rf gcc/avr32 gcc/xmega gcc/mega gcc/common gcc/*.lss gcc/*.sym
endif


.PHONY: release
release: all clean


$(avr32_mcu):
ifeq ($(tool),iar)
	$(ewavr32_build) iar/libsensors-$@.ewp -clean release
	$(ewavr32_build) iar/libsensors-$@.ewp -build release
	$(ewavr32_build) iar/libsensors-$@.ewp -clean debug
	$(ewavr32_build) iar/libsensors-$@.ewp -build debug
else
	$(MAKE) -C gcc mcu_family=avr32 mcu_series=$@ rebuild
	avr32-strip --strip-unneeded gcc/libsensors-$@-release.a
	$(MAKE) -C gcc mcu_family=avr32 mcu_series=$@ debug=1 rebuild
endif

$(xmega_mcu):
ifeq ($(tool),iar)
	$(ewavr_build) iar/libsensors-$@.ewp -clean release
	$(ewavr_build) iar/libsensors-$@.ewp -build release
	$(ewavr_build) iar/libsensors-$@.ewp -clean debug
	$(ewavr_build) iar/libsensors-$@.ewp -build debug
else
	$(MAKE) -C gcc mcu_family=xmega mcu_series=$@ rebuild
	avr-strip --strip-unneeded gcc/libsensors-$@-release.a
	$(MAKE) -C gcc mcu_family=xmega mcu_series=$@ debug=1 rebuild
endif

$(mega_mcu):
	$(MAKE) -C gcc mcu_family=mega mcu_series=$@ rebuild
	avr-strip --strip-unneeded gcc/libsensors-$@-release.a
	$(MAKE) -C gcc mcu_family=mega mcu_series=$@ debug=1 rebuild
