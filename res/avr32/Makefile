# Universal AVR32 Makefile for firmware without operating system.
# Wolfgang Wieser 07/2008.

# VARIABLES.

PART=BUILD_INSERTS_MCU_CODE_HERE
TARGET=BUILD_INSERTS_PROJECT_NAME_HERE

# Optimization level, use s (size opt), 1, 2, 3 or 0 (off).
OPTLEVEL=2

# Executables.
CC=BUILD_INSERTS_C_COMPILER_HERE
PC=BUILD_INSERTS_P_COMPILER_HERE

# Compiler flags.
CFLAGS= -g -O$(OPTLEVEL) -Wall -ffunction-sections -mpart=$(PART)
PFLAGS= $(CFLAGS)
AFLAGS= -I. $(INC) -mmcu=$(MCU) -x assembler-with-cpp -Wa -gstabs #-ahlms=$(firstword $(<:.S=.lst) $(<.s=.lst))

# Linker flags.
LFLAGS= -g -Wl,--gc-sections -mpart=$(PART)

# Project source files.
PRJSRC_C=BUILD_INSERTS_C_FILES_HERE
PRJSRC_P=BUILD_INSERTS_P_FILES_HERE
PRJSRC_S=BUILD_INSERTS_S_FILES_HERE

# Library source files.
LIBSRC_C=BUILD_INSERTS_LIBRARY_C_SOURCE_FILES_HERE
LIBSRC_P=BUILD_INSERTS_LIBRARY_P_SOURCE_FILES_HERE
LIBSRC_S=BUILD_INSERTS_LIBRARY_S_SOURCE_FILES_HERE

# Library object files.
LIBOBJ=BUILD_INSERTS_LIBRARY_OBJECT_FILES_HERE

# Required object files.
OBJECTS=$(PRJSRC_C:.c=.o) $(PRJSRC_P:.cpp=.o) $(PRJSRC_S:.s=.o) $(LIBSRC_C:.c=.o) $(LIBSRC_P:.cpp=.o) $(LIBSRC_S:.s=.o) $(LIBOBJ)

# PSEUDO-TARGETS.

.PHONY: all

all: $(TARGET).elf

# ACTUAL TARGETS.

# Target from objects.
$(TARGET).elf: $(OBJECTS)
	@echo "******** Linking target ${TARGET} from object files. ********"
	$(CC) $(LFLAGS) -o $(TARGET).elf $(OBJECTS)

#### Generating object files. ####

# Object from C.
%.o : %.c
	@echo "******** Compiling $@ from $^. ********"
	$(CC) -c $(CFLAGS) -o $*.o $<

# Object from C++.
%.o : %.cpp
	@echo "******** Compiling $@ from $^. ********"
	$(PC) -c $(PFLAGS) -o $*.o $<

#Object from ASM
%.o : %.s
	@echo "******** Assembling $@ from $^. ********"
	$(CC) $(AFLAGS) -c $< -o $@

