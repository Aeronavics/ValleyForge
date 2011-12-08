# Universal AVR32 Makefile for firmware without operating system.
# Wolfgang Wieser 07/2008.

# VARIABLES.

PART=BUILD_WILL_INSERT_MCU_CODE_HERE
CFLAGS=-g -O2 -Wall -ffunction-sections
LDFLAGS=-g -Wl,--gc-sections
CC=BUILD_WILL_INSERT_COMPILER_HERE
PROGRAMMER = ../res/avr32comp/bin/avr32program

HEADERS=BUILD_WILL_INSERT_H_FILES_HERE
PRJSRC=BUILD_WILL_INSERT_H_FILES_HERE
OBJECTS=$(PRJSRC:.c=.o)
TARGET=BUILD_WILL_INSERT_PROJECT_NAME_HERE

# PSEUDO-TARGETS.

.PHONY: all

all: $(TARGET).elf

# ACTUAL TARGETS.

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -mpart=$(PART) -o $(TARGET).elf $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) -mpart=$(PART) -o $*.o $<

$(OBJECTS): $(HEADERS)
