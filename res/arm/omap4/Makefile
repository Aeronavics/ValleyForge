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
# MAKEFILE FOR ARM TARGETS.
#
#	Author:		Edwin Hayes
#
#	Created:	7th Dec 2011
#

# VARIABLES.

MCPU=BUILD_INSERTS_MCU_CODE_HERE

# Executables.
CC=BUILD_INSERTS_C_COMPILER_HERE
PC=BUILD_INSERTS_P_COMPILER_HERE
AS=BUILD_INSERTS_ASSEMBLER_HERE
LD=BUILD_INSERTS_LINKER_HERE

# Flags.
CFLAGS= -mcpu=${MCPU} -Wall BUILD_INSERTS_CFLAGS_HERE
PFLAGS= $(CFLAGS) BUILD_INSERTS_PFLAGS_HERE
AFLAGS= BUILD_INSERTS_AFLAGS_HERE
LFLAGS= BUILD_INSERTS_LFLAGS_HERE

TARGET=BUILD_INSERTS_COMPONENT_HERE

# Source files.
SRC_C=BUILD_INSERTS_C_FILES_HERE
SRC_P=BUILD_INSERTS_P_FILES_HERE
SRC_H=BUILD_INSERTS_H_FILES_HERE
SRC_S=BUILD_INSERTS_S_FILES_HERE

# Library source files.
LIBSRC_C=BUILD_INSERTS_LIBRARY_C_FILES_HERE
LIBSRC_P=BUILD_INSERTS_LIBRARY_P_FILES_HERE
LIBSRC_H=BUILD_INSERTS_LIBRARY_H_FILES_HERE
LIBSRC_S=BUILD_INSERTS_LIBRARY_S_FILES_HERE
LIBSRC_O=BUILD_INSERTS_LIBRARY_O_FILES_HERE

# Determine required object files.
OBJ_C=${SRC_C:.c=.o} ${LIBSRC_C:.c=.o}
OBJ_P=${SRC_P:.cpp=.o} ${LIBSRC_P:.cpp=.o}
OBJ_S=${SRC_S:.s=.o} ${LIBSRC_S:.s=.o}

# Pseudo Targets.

# 'make all' produces an executable of the target.
all : ${TARGET}

# Real Targets.

# To produce the executable of the target, link together the object files.
${TARGET} : ${OBJ_C} ${OBJ_P} ${OBJ_S} ${LIBSRC_O}
	@echo "******** Linking target ${TARGET} from object files. ********"
	${LD} ${LFLAGS} $^ -o $@

# Compile CPP files into object files.
%.o : %.cpp
	@echo "******** Compiling $@ from $^. ********"
	${PC} ${PFLAGS} -c $^ -o $@

# Compile C files into object files.
%.o : %.c
	@echo "******** Compiling $@ from $^. ********"
	${CC} ${CFLAGS} -c $^ -o $@

# Assemble S files into object files.
%.o : %.s
	@echo "******** Assembling $@ from $^. ********"
	${AS} ${AFLAGS} -c $^ -o $@







