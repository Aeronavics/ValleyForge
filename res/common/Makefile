#	Copyright (C) 2013  Unison Networks Ltd
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
# GENERIC MAKEFILE.
#
#	Author:		Edwin Hayes
#
#	Created:	2nd April 2013
#

# VARIABLES.

# Make Configuration Details.
SHELL=/usr/bin/env bash # Need to use bash, since we use some non-posix features.
	# Disable implicit rules, since they will screw dependency detection up.
.SUFFIXES:

# Shell colours.
NO_COLOUR=\033[0m
BOLD_WHITE=\033[1;37m

# Component & Filename Details.
COMPONENT=BUILD_INSERTS_COMPONENT_HERE
EXECUTABLE=BUILD_INSERTS_EXECUTABLE_HERE
LOOSE_OBJECTS=BUILD_INSERTS_LOOSE_OBJECTS_HERE

# Executables.
CC=BUILD_INSERTS_C_COMPILER_HERE # The C compiler to use.
PC=BUILD_INSERTS_P_COMPILER_HERE # The C++ compiler to use.
AS=BUILD_INSERTS_ASSEMBLER_HERE # The assembler to use.
LD=BUILD_INSERTS_LINKER_HERE # The linker to use.
OBJDUMP=BUILD_INSERTS_OBJDUMP_HERE # The object-dump (binary manipulator) to use.
OBJCOPY=BUILD_INSERTS_OBJCOPY_HERE # The object-copy (binary manipulator) to use.

# Flags.
CFLAGS=BUILD_INSERTS_CFLAGS_HERE # The C compiler flags to apply.
PFLAGS=BUILD_INSERTS_PFLAGS_HERE # The C++ compiler flags to apply.
AFLAGS=BUILD_INSERTS_AFLAGS_HERE # The assembler flags to apply.
LFLAGS=BUILD_INSERTS_LFLAGS_HERE # The linker flags to apply.

include Make.deps

.PHONY: all

all: $(EXECUTABLE)
	

$(EXECUTABLE): $(OBJS)
	@echo -e "$(BOLD_WHITE)******** Linking $@ from Object Files. ********$(NO_COLOUR)"
	$(LD) -o $@ $(OBJS) $(LIBS) $(LFLAGS)

#	OBJECT FILES.

# Object from C.
%.o: %.c
	@echo -e "$(BOLD_WHITE)******** Compiling $@. test ********$(NO_COLOUR)"
	$(CC) $(CFLAGS) -c $< -o $@

# Object from C++.
%.o: %.cpp
	@echo -e "$(BOLD_WHITE)******** Compiling $@. ********$(NO_COLOUR)"
	$(PC) $(PFLAGS) -c $< -o $@

# Object from assembly.
%.o: %.s
	@echo -e "$(BOLD_WHITE)******** Compiling $@. ********$(NO_COLOUR)"
	$(AS) $(AFLAGS) -c $< -o $@

# TODO - When using gcc as the assembler, you need '-c', but using gcc-as you don't want it.  Possibly needs to be replaced with a configured variable.

# ALL DONE.
