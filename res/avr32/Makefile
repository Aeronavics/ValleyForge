# Universal AVR32 Makefile for firmware without operating system.
# Wolfgang Wieser 07/2008.

PART = BUILD_WILL_INSERT_MICRO_HERE
CFLAGS = -g -O2 -Wall -ffunction-sections
LDFLAGS = -g -Wl,--gc-sections
CC = ../res/avr32comp/bin/avr32-gcc
PROGRAMMER = ../res/avr32comp/bin/avr32program

HEADERS =BUILD_WILL_INSERT_H_FILES_HERE
PRJSRC =BUILD_WILL_INSERT_SOURCE_FILES_HERE
OBJECTS = $(PRJSRC:.c=.o)
TARGET =BUILD_WILL_INSERT_PROJECT_NAME_HERE

.PHONY: all run clean program reset cont erase

all: $(TARGET).elf
run: $(TARGET).elf program

clean:
	rm -f $(OBJECTS)

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -mpart=$(PART) -o $(TARGET).elf $(OBJECTS)

program: $(TARGET).elf
	$(PROGRAMMER) -c USB -pjtagicemkii program -finternal@0x80000000 -v -e --run -R -cint $(TARGET).elf

reset:
	$(PROGRAMMER) -c USB -pjtagicemkii reset -r
cont:
	$(PROGRAMMER) -c USB -pjtagicemkii run
erase:
	$(PROGRAMMER) -c USB -pjtagicemkii erase -finternal@0x80000000
chiperase:
	$(PROGRAMMER) -c USB -pjtagicemkii chiperase

.c.o:
	$(CC) -c $(CFLAGS) -mpart=$(PART) -o $*.o $<

$(OBJECTS): $(HEADERS)