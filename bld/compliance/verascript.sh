#!/bin/sh

# FIGURE OUT WHERE WE ARE.

# Determine what the absolute path to the root of the toolchain is.
SCRIPT=`readlink -f $0`
SCRIPTPATH=`dirname $SCRIPT`
TCPATH=$(echo $SCRIPTPATH | sed 's/\/bld.*//')

# DEFINE CONSTANTS.

# Define file names.

USER_CONFIG_FILE="var/config.cfg"
LIB_SOURCE_PATH="lib"
TMP_SRC_DIR="tmp/tmp_src"
OUTPUT_DIR="bin"

for FILE in $(find $TCPATH/src/$COMPONENT -name "*.cpp" -o -name "*.hpp"); do
vera++ $FILE -profile profvera.tcl
done
