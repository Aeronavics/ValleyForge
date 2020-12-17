#
# UAVCAN library
#

UAVCANFLAGS += -DUAVCAN_STM32_TIMER_NUMBER=4 \
          -DUAVCAN_STM32_NUM_IFACES=1 \
          -DUAVCAN_CPP_VERSION=UAVCAN_CPP11 \
          -DUAVCAN_STM32_BAREMETAL=1 \

CFLAGS += $(UAVCANFLAGS)
PFLAGS += $(UAVCANFLAGS)

# Add libuavcan core sources and includes
include libuavcan/libuavcan/include.mk
CPPSRC += $(LIBUAVCAN_SRC)
UINCDIR += -I$(LIBUAVCAN_INC)

# Add STM32 driver sources and includes
include libuavcan/libuavcan_drivers/stm32/driver/include.mk
CPPSRC += $(LIBUAVCAN_STM32_SRC)
UINCDIR += -I$(LIBUAVCAN_STM32_INC)

# Invoke DSDL compiler and add its default output directory to the include search path
$(info $(shell $(LIBUAVCAN_DSDLC) $(UAVCAN_DSDL_DIR)))
UINCDIR += -Idsdlc_generated      # This is where the generated headers are stored by default


CFLAGS += $(UINCDIR)
PFLAGS += $(UINCDIR)

OBJS +=  $(CPPSRC:.cpp=.o)