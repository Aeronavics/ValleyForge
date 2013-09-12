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
# GENERIC CHILD MAKEFILE FOR USE WITH ARDUINO-MK.
#
#	Author:		Edwin Hayes
#
#	Created:	11th September 2013
#

# VARIABLES.

# Make Configuration Details.

# Component & Filename Details.
COMPONENT=BUILD_INSERTS_COMPONENT_HERE
EXECUTABLE=BUILD_INSERTS_EXECUTABLE_HERE

# Arduino-mk configuration details.
ARDMK_DIR=BUILD_INSERTS_ARDMK_DIR_HERE
ARDMK_PATH=BUILD_INSERTS_ARDMK_PATH_HERE
ARDUINO_DIR=BUILD_INSERTS_ARDUINO_DIR_HERE

BOARD_TAG=BUILD_INSERTS_BOARD_TAG_HERE
ARDUINO_LIBS=BUILD_INSERTS_SKETCH_LIBRARIES_HERE
USER_LIB_PATH=BUILD_INSERTS_OTHER_LIBRARIES_HERE

ALTERNATE_CORE=BUILD_INSERTS_ALTERNATE_CORE_HERE
ARDUINO_VAR_PATH=BUILD_INSERTS_ARDUINO_VAR_PATH_HERE
ARDUINO_CORE_PATH=BUILD_INSERTS_ARDUINO_CORE_PATH_HERE

ARDUINO_SKETCHBOOK=BUILD_INSERTS_TMPSRC_DIRECTORY_HERE
OBJDIR=BUILD_INSERTS_TMPSRC_DIRECTORY_HERE

	# We have to located boards.txt manually, because arduino-mk hasn't been updated to deal with the fact that there are ARM types now.
BOARDS_TXT=$(ARDUINO_DIR)/hardware/arduino/avr/boards.txt

# Flags.
CPPFLAGS=BUILD_INSERTS_CFLAGS_HERE
LDFLAGS=BUILD_INSERTS_LFLAGS_HERE

# INCLUDE EXTERNAL MAKEFILES

include $(ARDMK_DIR)/arduino-mk/Arduino.mk




