#	Copyright (C) 2011  Unison Networks Ltd
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#
# GENERIC AVR MAKEFILE WITH DEPENDANCY CALCULATION.
#
#	Author:		Edwin Hayes
#
#	Created:	9th Jan 2013
#

# VARIABLES.

# Make Configuration Details.
SHELL=/bin/bash # Need to use bash, since we use some non-posix features.

# Component & Filename Details.
COMPONENT=BUILD_INSERTS_COMPONENT_HERE
OUTFILE=${COMPONENT}.out # The output file which generally needs to be created.

# Target Details.
MCU=BUILD_INSERTS_MCU_CODE_HERE # The name/type of the target controller (as used by the compiler).
HEXFORMAT=ihex # The hex file format to use.

# Executables.
CC=BUILD_INSERTS_C_COMPILER_HERE # The C compiler to use.
PC=BUILD_INSERTS_P_COMPILER_HERE # The C++ compiler to use.
AS=BUILD_INSERTS_ASSEMBLER_HERE # The assembler to use.
LD=${CC} # The linker to use.
OBJDUMP=BUILD_INSERTS_OBJDUMP_HERE # The object-dump (binary manipulator) to use.
OBJCOPY=BUILD_INSERTS_OBJCOPY_HERE # The object-copy (binary manipulator) to use.
SIZE=BUILD_INSERTS_SIZE_HERE # The size utility (binary inspector) to use.

# Flags.
OPTLEVEL=s # Optimization level to use: s (for size), 1, 2, 3 (for performance) or 0 (none).
CFLAGS= -I . -g -mmcu=${MCU} -O${OPTLEVEL} BUILD_INSERTS_CFLAGS_HERE -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -fno-exceptions -Wall # The C compiler flags to apply.
PFLAGS= ${CFLAGS} BUILD_INSERTS_PFLAGS_HERE # The C++ compiler flags to apply.
AFLAGS=	-mmcu=$(MCU) -Wa BUILD_INSERTS_AFLAGS_HERE# The assember flags to apply.
LFLAGS= -Wl,-Map,$(COMPONENT).map -mmcu=$(MCU) BUILD_INSERTS_LFLAGS_HERE # The linker flags to apply.
LFLAGS+= -Wl,--section-start=.bootloader_trampoline=0x01000 -Wl,--undefined=_bootloader_trampoline

# PSEUDO-TARGETS

# All the pseudo-targets are phony: they don't correspond with real files.
.PHONY: all main stats

all: main

main: ${OUTFILE}

stats: ${MAIN}
	${OBJDUMP} -h ${OUTFILE}
	${SIZE} ${OUTFILE}

# TARGETS.

#	OUTPUT FILES.

%.out:
	@echo "******** Linking $@ from Object Files. ********"
	$(LD) $(LFLAGS) -o $@ $(shell find . -name "*.o")

#	BINARY FILES.

# Hex files from elf.
.out.hex:
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@
.out.ee.hex:
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O $(HEXFORMAT) $< $@

#	OBJECT FILES.

# Object from C.
%.o : %.c
	@echo "******** Compiling $@. ********"
	$(CC) $(CFLAGS) -c $< -o $@

# Object from C++.
%.o : %.cpp
	@echo "******** Compiling $@. ********"
	$(PC) $(PFLAGS) -c $< -o $@

# Object from assembly.
%.o : %.s
	@echo "******** Compiling $@. ********"
	$(AS) $(AFLAGS) $< -o $@

#	ASSEMBLY FILES.

# ASM from C.
%.s: %.c
	@echo "******** Assembling $@. ********"
	$(CC) $(CFLAGS) -s $< -o $@

# ASM from CPP.
%.s: %.cpp
	@echo "******** Assembling $@. ********"
	$(CC) $(CFLAGS) -s $< -o $@

# DEPENDENCY TARGETS.

# Header file dependencies are calculated directly by the compiler, they are easy.  Object file dependencies are more complicated; in this
# implementation, we assume that if a required header file has a matching source file in the same folder, then that will probably be an object
# dependency (and hence the source should be compiled).  Then, to produce the final executable, we just link together all the object files that
# we created.

# Dependency from C.
%.dc: %.c
	@echo "******** Calculating dependencies for $*. ********"
	${CC} ${CFLAGS} -MM $^ > $@
	@while read -a line; do \
		for word in "$${line[@]}"; do \
			if [[ $$word == *".h" && $$word != "$*.h" ]]; then \
				if [ -f "$${word/%.h/.c}" ]; then \
					sed -i "s^$$word^$$word $${word/%.h/.o}^g" $@; \
				fi; \
			fi; \
		done; \
	done < $@
	@cat $@

# Dependency from C++.
%.dcpp: %.cpp
	@echo "******** Calculating dependencies for $*. ********"
	${PC} ${PFLAGS} -MM $^ > $@
	@while read -a line; do \
		for word in "$${line[@]}"; do \
			if [[ $$word == *".hpp" && $$word != "$*.hpp" ]]; then \
				if [ -f "$${word/%.hpp/.cpp}" ]; then \
					sed -i "s^$$word^$$word $${word/%.hpp/.o}^g" $@; \
				fi; \
			fi; \
		done; \
	done < $@
	@cat $@

# The dependencies for the target output file are created by assuming that the target output file requires some object file (at least).  Further,
# it is assumed in this implementation that whilst the main object file will include the required chain of files for C and C++ sources, there may
# also be some assembler files required: currently, any assembler files will be listed for linking.

# Dependencies of component.
${COMPONENT}.d:
	@echo "******** Calculating component dependencies. ********"
	@# Work out what the main file is going to be, so we can build the output file.
	@echo -e "${OUTFILE}: ${COMPONENT}.o\n" >> ${COMPONENT}.d
	@# Add in any floating assembler files.
	@echo -e "${COMPONENT}.o: ${patsubst %.s, %.o, ${wildcard *.s}}" >> ${COMPONENT}.d

# IMPORT EXTERNAL DEPENDENCIES.

# Dependencies are calculated for all the source files, even if they might not be needed, because there isn't an option to go back and include
# additional rules later, so we have to include all the rules we might possibly need right from the start.

# Include dependencies for C files.
-include ${patsubst %.c, %.dc, ${wildcard *.c}}
-include ${patsubst %.c, %.dc, ${wildcard **/*.c}}

# Include dependencies for C++ files.
-include ${patsubst %.cpp, %.dcpp, ${wildcard *.cpp}}
-include ${patsubst %.cpp, %.dcpp, ${wildcard **/*.cpp}}

# Dependencies also need to be calculated for the component as a whole, so that we actually have some rules which create us the desired output
# file, using the appropriate source files.

# Include dependencies for main.
-include ${COMPONENT}.d


