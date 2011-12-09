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
CC=BUILD_INSERTS_COMPILER_HERE
AS=BUILD_INSERTS_ASSEMBLER_HERE
LD=BUILD_INSERTS_LINKER_HERE

# Flags.
CFLAGS=-mcpu=${MCPU} -Wall BUILD_INSERTS_CFLAGS_HERE
AFLAGS= BUILD_INSERTS_AFLAGS_HERE
LFLAGS= BUILD_INSERTS_LFLAGS_HERE

TARGET=BUILD_INSERTS_COMPONENT_HERE

# Source files.
SRC_C=BUILD_INSERTS_C_FILES_HERE
SRC_H=BUILD_INSERTS_H_FILES_HERE
SRC_S=BUILD_INSERTS_S_FILES_HERE

# Library source files.
LIBSRC_C=BUILD_INSERTS_LIBRARY_C_FILES_HERE
LIBSRC_H=BUILD_INSERTS_LIBRARY_H_FILES_HERE
LIBSRC_S=BUILD_INSERTS_LIBRARY_S_FILES_HERE
LIBSRC_O=BUILD_INSERTS_LIBRARY_O_FILES_HERE

# Determine required object files.
OBJ_C=${SRC_C:.c=.o} ${LIBSRC_C:.c=.o}
OBJ_S=${SRC_S:.s=.o} ${LIBSRC_S:.s=.o}

# Pseudo Targets.

# 'make all' produces an executable of the target.
all : ${TARGET}

# Real Targets.

# To produce the executable of the target, link together the object files.
${TARGET} : ${OBJ_C} ${OBJ_S} ${LIBSRC_O}
	@echo "******** Linking target ${TARGET} from object files. ********"
	${LD} ${LFLAGS} $^ -o $@

# Compile C files into object files.
%.o : %.c
	@echo "******** Compiling $@ from $^. ********"
	${CC} ${CFLAGS} -c $^ -o $@

# Assemble S files into object files.
%.o : %.s
	@echo "******** Assembling $@ from $^. ********"
	${AS} ${AFLAGS} -c $^ -o $@







