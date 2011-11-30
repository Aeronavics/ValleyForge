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
TARGET = avr32_services_freertos_lwIP_DHCP_example_evk1100.elf

# List of C source files.
CSRCS = \
       thirdparty/lwip/lwip-1.3.2/src/core/raw.c          \
       avr32/drivers/pm/power_clocks_lib.c                \
       thirdparty/lwip/lwip-1.3.2/src/api/netbuf.c        \
       thirdparty/lwip/lwip-1.3.2/src/netif/etharp.c      \
       thirdparty/lwip/lwip-1.3.2/src/core/pbuf.c         \
       avr32/drivers/usart/usart.c                        \
       avr32/drivers/pm/pm_conf_clocks.c                  \
       thirdparty/lwip/lwip-1.3.2/src/api/api_msg.c       \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp_out.c      \
       thirdparty/lwip/lwip-1.3.2/src/api/sockets.c       \
       avr32/drivers/spi/spi.c                            \
       thirdparty/freertos/source/timers.c                \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip_addr.c \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/icmp.c    \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/main.c \
       thirdparty/freertos/source/queue.c                 \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/inet.c    \
       thirdparty/lwip/lwip-1.3.2/src/core/init.c         \
       avr32/drivers/pwm/pwm.c                            \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp.c          \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/network/ethernet.c \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/read.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicsmtp/BasicSMTP.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/display/displayTask.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/partest/ParTest.c \
       common/services/clock/uc3a0_a1/sysclk.c            \
       thirdparty/lwip/lwip-1.3.2/src/core/memp.c         \
       avr32/components/display/dip204/dip204.c           \
       avr32/drivers/intc/intc.c                          \
       thirdparty/lwip/lwip-1.3.2/src/api/netifapi.c      \
       thirdparty/freertos/demo/common/minimal/flash.c    \
       avr32/drivers/gpio/gpio.c                          \
       thirdparty/lwip/lwip-1.3.2/src/core/udp.c          \
       avr32/boards/evk1100/led.c                         \
       avr32/drivers/flashc/flashc.c                      \
       avr32/drivers/pm/pm.c                              \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/printf-stdarg.c \
       thirdparty/lwip/lwip-1.3.2/src/core/stats.c        \
       avr32/drivers/tc/tc.c                              \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/inet_chksum.c \
       thirdparty/lwip/lwip-1.3.2/src/core/dhcp.c         \
       thirdparty/freertos/source/list.c                  \
       thirdparty/lwip/lwip-1.3.2/src/core/dns.c          \
       avr32/drivers/macb/macb.c                          \
       thirdparty/lwip/lwip-1.3.2/src/core/sys.c          \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/display/display_dip204.c \
       thirdparty/lwip/lwip-1.3.2/src/api/err.c           \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip_frag.c \
       thirdparty/freertos/source/portable/memmang/heap_3.c \
       thirdparty/lwip/lwip-1.3.2/src/core/netif.c        \
       thirdparty/lwip/lwip-1.3.2/src/api/api_lib.c       \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicweb/BasicWEB.c \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/netif/ethernetif.c \
       thirdparty/lwip/lwip-1.3.2/src/api/tcpip.c         \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/igmp.c    \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/sys_arch.c \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/write.c \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp_in.c       \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basictftp/BasicTFTP.c \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/autoip.c  \
       avr32/services/delay/delay.c                       \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/port.c \
       thirdparty/freertos/source/croutine.c              \
       thirdparty/lwip/lwip-1.3.2/src/core/mem.c          \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip.c      \
       thirdparty/freertos/source/tasks.c                 \
       thirdparty/lwip/lwip-1.3.2/src/api/netdb.c

# List of assembler source files.
ASSRCS = \
       avr32/utils/startup/trampoline_uc3.S               \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/exception.S

# List of include paths.
INC_PATH = \
       avr32/components/display/dip204                    \
       avr32/drivers/macb                                 \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicsmtp \
       avr32/boards                                       \
       avr32/drivers/pm                                   \
       avr32/drivers/flashc                               \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basictftp \
       thirdparty/lwip/lwip-1.3.2/src/include             \
       avr32/drivers/tc                                   \
       avr32/components/ethernet_phy/rtl8201              \
       common/services/clock                              \
       avr32/utils                                        \
       thirdparty/freertos/source/portable/gcc/avr32_uc3  \
       avr32/boards/evk1100                               \
       avr32/drivers/gpio                                 \
       common/utils                                       \
       avr32/drivers/spi                                  \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example \
       thirdparty/freertos/source/include                 \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/include    \
       thirdparty/freertos/demo/common/include            \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/at32uc3a0512_evk1100 \
       avr32/drivers/pwm                                  \
       thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/display \
       thirdparty/lwip/lwip-1.3.2/src/include/ipv4        \
       avr32/drivers/cpu/cycle_counter                    \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicweb \
       avr32/components/ethernet_phy                      \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network \
       common/boards                                      \
       avr32/drivers/usart                                \
       avr32/components/ethernet_phy/dp83848              \
       avr32/services/delay                               \
       avr32/utils/preprocessor                           \
       avr32/drivers/intc                                 \
       avr32/components/ethernet_phy/dummy_phy \
       ./thirdparty/freertos/demo/lwip_avr32_uc3_dhcp_example/at32uc3a0512_evk1100/gcc

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
       -D BOARD=EVK1100                                   \
       -D HTTP_USED=1                                     \
       -D FREERTOS_USED                                   \
       -D TFTP_USED=1                                     \
       -D CONFIG_INTERRUPT_FORCE_INTC                     \
       -D SMTP_USED=0

# Extra flags to use when linking
LDFLAGS = \
        -Wl,-e,_trampoline
