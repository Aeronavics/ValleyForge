
#########  AVR Project Makefile Template   #########
######                                        ######
######    Copyright (C) 2003-2005,Pat Deegan, ######
######            Psychogenic Inc             ######
######          All Rights Reserved           ######
######                                        ######
###### You are free to use this code as part  ######
###### of your own applications provided      ######
###### you keep this copyright notice intact  ######
###### and acknowledge its authorship with    ######
###### the words:                             ######
######                                        ######
###### "Contains software by Pat Deegan of    ######
###### Psychogenic Inc (www.psychogenic.com)" ######
######                                        ######
###### If you use it as part of a web site    ######
###### please include a link to our site,     ######
###### http://electrons.psychogenic.com  or   ######
###### http://www.psychogenic.com             ######
######                                        ######
####################################################


##### This Makefile will make compiling Atmel AVR 
##### micro controller projects simple with Linux 
##### or other Unix workstations and the AVR-GCC 
##### tools.
#####
##### It supports C, C++ and Assembly source files.
#####
##### Customize the values as indicated below and :
##### make
##### make disasm 
##### make stats 
##### make hex
##### make writeflash
##### make gdbinit
##### or make clean
#####
##### See the http://electrons.psychogenic.com/ 
##### website for detailed instructions


####################################################
#####                                          #####
#####              Configuration               #####
#####                                          #####
##### Customize the values in this section for #####
##### your project. MCU, PROJECTNAME and       #####
##### PRJSRC must be setup for all projects,   #####
##### the remaining variables are only         #####
##### relevant to those needing additional     #####
##### include dirs or libraries and those      #####
##### who wish to use the avrdude programmer   #####
#####                                          #####
##### See http://electrons.psychogenic.com/    #####
##### for further details.                     #####
#####                                          #####
####################################################

#####         Target Specific Details          #####

#####     Customize these for your project     #####

# Name of target controller .
MCU=BUILD_INSERTS_MCU_CODE_HERE

# Name of project.
PROJECTNAME=BUILD_INSERTS_PROJECT_NAME_HERE

# Source files.
PRJSRC=BUILD_INSERTS_SOURCE_FILES_HERE

# Library source files.
LIBSRC=BUILD_INSERTS_LIBRARY_SOURCE_FILES_HERE

# Library object files.
LIBOBJ=BUILD_INSERTS_LIBRARY_OBJECT_FILES_HERE

# Additional includes (e.g. -I/path/to/mydir).

# Libraries to link in (e.g. -lmylib).
LIBS=

# Optimization level, use s (size opt), 1, 2, 3 or 0 (off).
OPTLEVEL=s

####################################################
#####                Config Done               #####
#####                                          #####
##### You shouldn't need to edit anything      #####
##### below to use the makefile but may wish   #####
##### to override a few of the flags           #####
##### nonetheless                              #####
#####                                          #####
####################################################

##### Flags ####

# Format for .hex file output
HEXFORMAT=ihex

# NOTE - The assembler listings have been disabled, since this tends to flood the console with unhelpful text.

# Compiler flags.
CFLAGS= -I. $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char \
	  -fno-exceptions -Wall #-Wa,-ahlms=$(firstword $(filter %.lst, $(<:.c=.lst)))
PFLAGS= $(CFLAGS)

# Assembler flags.
AFLAGS =-I. $(INC) -mmcu=$(MCU) -x assembler-with-cpp -Wa -gstabs #-ahlms=$(firstword $(<:.S=.lst) $(<.s=.lst))

# Linker flags.
LFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU) -lm $(LIBS)

##### Executables ####

CC=BUILD_INSERTS_C_COMPILER_HERE
PC=BUILD_INSERTS_P_COMPILER_HERE
OBJCOPY=BUILD_INSERTS_OBJCOPY_HERE
OBJDUMP=BUILD_INSERTS_OBJDUMP_HERE
SIZE=avr-size

##### Automatic Target Names ####

TRG=$(PROJECTNAME).out
DUMPTRG=$(PROJECTNAME).S

HEXROMTRG=$(PROJECTNAME).hex 
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex
GDBINITFILE=gdbinit-$(PROJECTNAME)

# Define all object files.

	#  C
CFILES=$(filter %.c, $(PRJSRC))

	#  C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

	#  Assembly
ASMFILES=$(filter %.s, $(PRJSRC))

	#  C Library Files
CLIBFILES=$(filter %.c, $(LIBSRC))

	#  C++ Library Files
CPPLIBFILES=$(filter %.cpp, $(LIBSRC))

	#  Assembly Library Files
ASMLIBFILES=$(filter %.s, $(LIBSRC))

	# List all object files we need to create
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(ASMFILES:.s=.o) $(CLIBFILES:.c=.o) $(CPPLIBFILES:.cpp=.o) $(ASMLIBFILES:.s=.o)

	# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

	# All the possible generated assembly files (.s files)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.S)) 

.SUFFIXES : .c .o .out .s .S .hex .ee.hex .h

.PHONY: clean stats

##### Make pseudo-targets. #####

all: $(TRG)

disasm: $(DUMPTRG) stats

stats: $(TRG)
	$(OBJDUMP) -h $(TRG)
	$(SIZE) $(TRG) 

hex: $(HEXTRG)

$(DUMPTRG): $(TRG) 
	$(OBJDUMP) -S  $< > $@


$(TRG): $(OBJDEPS)
	@echo "******** Linking target ${PROJECTNAME} from object files. ********"
	$(CC) $(LFLAGS) -o $(TRG) $(OBJDEPS)

#### Generating assembly. ####

# ASM from (hand coded) asm

%.S: %.s
	$(CC) -S $(AFLAGS) $< > $@

#### Generating object files. ####

# Object from C.
%.o : %.c
	@echo "******** Compiling $@ from $^. ********"
	$(CC) $(CFLAGS) -c $< -o $@

# Object from C++.
%.o : %.cpp
	@echo "******** Compiling $@ from $^. ********"
	$(PC) $(PFLAGS) -c $< -o $@

# Object from assembly.
%.o : %.s
	@echo "******** Assembling $@ from $^. ********"
	$(CC) $(AFLAGS) -c $< -o $@

#### Generating hex files ####

# Hex files from elf.

.out.hex:
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

.out.ee.hex:
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O $(HEXFORMAT) $< $@
	
#####                    EOF                   #####

