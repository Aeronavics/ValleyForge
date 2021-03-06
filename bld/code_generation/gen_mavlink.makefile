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
# MAKEFILE FOR CODE GENERATION OF MAVLINK LIBRARY.
#
#	Author:		Edwin Hayes
#
#	Created:	17th May 2013
#

# VARIABLES.

# Make Configuration Details.
SHELL=/usr/bin/env bash # Need to use bash, since we use some non-posix features.
	# Disable implicit rules, since they will screw dependency detection up.
.SUFFIXES:

# Shell colours.
NO_COLOUR=\033[0m
BOLD_WHITE=\033[1;37m

# MAVlink generator files.
MAVLINK_GENERATOR=BUILD_INSERTS_MAVLINK_GENERATOR_HERE
MAVLINK_DEFINITIONS=BUILD_INSERTS_MAVLINK_DEFINITIONS_HERE
MAVLINK_SANDPIT=BUILD_INSERTS_MAVLINK_SANDPIT_HERE

# FUNCTIONS.

# Make does not offer a recursive wildcard function, so we create one.
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# PSEUDO-TARGETS

# All the pseudo-targets are phony: they don't correspond with real files.
.PHONY: all

all: ./mavlink

# TARGETS.

./mavlink: $(call rwildcard,$(MAVLINK_SANDPIT)/,*)
	@rm -rf $@
	@mkdir $@
	@python $(MAVLINK_GENERATOR) --lang=C --output=$@ $(MAVLINK_DEFINITIONS) --wire-protocol=2.0
	@python $(MAVLINK_GENERATOR) --lang=Python --output=$@ $(MAVLINK_DEFINITIONS) --wire-protocol=2.0

# DEPENDENCY TARGETS.

# IMPORT EXTERNAL DEPENDENCIES.


