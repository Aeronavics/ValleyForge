#
# MAKEFILE FOR ARM TARGETS.
#
#	Author:		Edwin Hayes
#
#	Created:	7th Dec 2011
#

# Variables.

MCPU=BUILD_INSERTS_MCU_CODE_HERE

CC=BUILD_INSERTS_COMPILER_HERE

AS=BUILD_INSERTS_ASSEMBLER_HERE

LD=BUILD_INSERTS_LINKER_HERE

CFLAGS=-mcpu=${MCPU} -Wall BUILD_INSERTS_CFLAGS_HERE

AFLAGS= BUILD_INSERTS_AFLAGS_HERE

LFLAGS= BUILD_INSERTS_LFLAGS_HERE

TARGET=BUILD_INSERTS_COMPONENT_HERE

SRC_C=BUILD_INSERTS_C_FILES_HERE

SRC_H=BUILD_INSERTS_H_FILES_HERE

SRC_S=BUILD_INSERTS_S_FILES_HERE

OBJ_C=${SRC_C:.c=.o}

OBJ_S=${SRC_S:.s=.o}

# Pseudo Targets.

# 'make all' produces an executable of the target.
all : ${TARGET}

# Real Targets.

# To produce the executable of the target, link together the object files.
${TARGET} : ${OBJ_C} ${OBJ_S}
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







