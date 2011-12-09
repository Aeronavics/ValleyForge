# Universal AVR32 Makefile for firmware without operating system.
# Wolfgang Wieser 07/2008.

# VARIABLES.

PART=BUILD_INSERTS_MCU_CODE_HERE
TARGET=BUILD_INSERTS_PROJECT_NAME_HERE

# Optimization level, use s (size opt), 1, 2, 3 or 0 (off).
OPTLEVEL=2

# Executables.
CC=BUILD_INSERTS_COMPILER_HERE

# Compiler flags.
CFLAGS=-g -O$(OPTLEVEL) -Wall -ffunction-sections

# Linker flags.
LDFLAGS=-g -Wl,--gc-sections

# Project source files.
PRJSRC=BUILD_INSERTS_C_FILES_HERE

# Library source files.
LIBSRC=BUILD_INSERTS_LIBRARY_SOURCE_FILES_HERE

# Library object files.
LIBOBJ=BUILD_INSERTS_LIBRARY_OBJECT_FILES_HERE

# Required object files.
OBJECTS=$(PRJSRC:.c=.o) $(LIBSRC:.c=.o) $(LIBOBJ)

# PSEUDO-TARGETS.

.PHONY: all

all: $(TARGET).elf

# ACTUAL TARGETS.

# Target from objects.
$(TARGET).elf: $(OBJECTS)
	@echo "******** Linking target ${TARGET} from object files. ********"
	$(CC) $(LDFLAGS) -mpart=$(PART) -o $(TARGET).elf $(OBJECTS)

#### Generating object files. ####

# Object from C++.
%.o : %.c
	@echo "******** Compiling $@ from $^. ********"
	$(CC) -c $(CFLAGS) -mpart=$(PART) -o $*.o $<

