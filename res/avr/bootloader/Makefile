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

# Component & Filename Details.
COMPONENT=BUILD_INSERTS_COMPONENT_HERE
OUTFILE=${COMPONENT}.out # The output file which generally needs to be created.
MAINFILE=BUILD_INSERTS_MAINFILE_HERE # The executable source file which needs to be built (usually contains main).

# Target Details.
MCU=BUILD_INSERTS_MCU_CODE_HERE # The name/type of the target controller (as used by the compiler).
HEXFORMAT=ihex # The hex file format to use.
BOOTSTART=BUILD_INSERTS_BOOTLOADER_ADDRESS_HERE # Where to put the bootloader in memory.

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
AFLAGS=	-I . -mmcu=$(MCU) -x assembler-with-cpp -Wa -gstabs BUILD_INSERTS_AFLAGS_HERE # The assember flags to apply.
LFLAGS= -Wl,-Map,$(COMPONENT).map -mmcu=$(MCU) -Wl,--section-start=.text=$(BOOTSTART) BUILD_INSERTS_LFLAGS_HERE # The linker flags to apply.

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

%.out: bootloader.o
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
	@echo "******** Assembling $@. ********"
	$(CC) $(AFLAGS) -c $< -o $@

#	ASSEMBLY FILES.

# ASM from (hand coded) asm
%.S: %.s
	$(CC) -S $(AFLAGS) $< > $@

# DEPENDENCY TARGETS.

# Header file dependencies are calculated directly by the compiler, they are easy.  Object file dependencies are more complicated; in this
# implementation, we assume that if a required header file has a matching source file in the same folder, then that will probably be an object
# dependency (and hence the source should be compiled).  Then, to produce the final executable, we just link together all the object files that
# we created.

# Dependency from C.
%.d: %.c
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
%.dpp: %.cpp
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

# IMPORT EXTERNAL DEPENDENCIES.

# Dependencies are calculated for all the source files, even if they might not be needed, because there isn't an option to go back and include
# additional rules later, so we have to include all the rules we might possibly need right from the start.

# Include dependencies for C files.
-include ${patsubst %.c, %.d, ${wildcard *.c}}
-include ${patsubst %.c, %.d, ${wildcard **/*.c}}

# Include dependencies for C++ files.
-include ${patsubst %.cpp, %.dpp, ${wildcard *.cpp}}
-include ${patsubst %.cpp, %.dpp, ${wildcard **/*.cpp}}

