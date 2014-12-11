#!/bin/bash

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


# Define the colours used for interface output.
source $TCPATH/bld/common/def_colours

# Create directories which don't come automatically with the toolchain.
source $TCPATH/bld/common/create_empty_dirs

# PRESENT THE USER WITH THE MAIN INTERFACE.

# Loop continuously until the user exits the script.
REDRAW_TOP=1
while :
do
	# We're at the top level.

	# Check if we should redraw the banner.
	if [ $REDRAW_TOP ]; then
		# Clear the terminal to keep things tidy.
		clear

		# Print welcome message.
		echo -e "${HIGHLIGHT_BLUE}${BOLD}\n ************  Welcome to the ValleyForge Embedded Toolchain Interface for formatting code *************${NO_COLOUR}\n"

	fi
	REDRAW_TOP=
	
	# Print the prompt to the user.

	echo -e  "${GREEN}Please select an option to work on:\n${NO_COLOUR}"
	
	echo -en "\t${UNDERLINED}L${NO_COLOUR}AYOUTS (COMMENTS AND SPACING)    ${UNDERLINED}H${NO_COLOUR}EADER FILES    ${UNDERLINED}N${NO_COLOUR}AMING CONVENTIONS        ${UNDERLINED}Q${NO_COLOUR}UIT${NO_COLOUR}"

# Read a single character input from the user and select the appropriate response.
	read -s -n 1
	echo -e "\n" # NOTE - This is required since read won't add a newline after reading a single character.
	case "$REPLY" in
		"L" | "l" )
				echo "inside layout choice"
#				for FILE in $(find $TCPATH/ -name "*.cpp"-o -name "*.hpp" -o -name "*.c" -o -name "*.h" -o -name "*.pde"); do
#				uncrustify -c my.cfg -f $FILE -o $FILE
#				sed -i 's:\(.*\)/[*]\(.*\)[*]/:\1 // \2:' $FILE #used for replacing single line /*..*/ comments to //
#				sed -i 's/todo[ -: ]*/ TODO - /I' testsample2.cpp #working one
#				sed -i 's/todo  / TODO -/I' $FILE #used for replacing case insensitive todo with TODO
#				sed -i 's/note[ -: ]*/ NOTE - /I' testsample2.cpp #working one
#				sed -i 's/note/ NOTE -/I' $FILE #used for replacing case insensitive note with NOTE
#				done
				break
				;;
		"H" | "h" )
				echo "inside header files"
#				for FILE in $(find $TCPATH/ -name "*.cpp"); do
#				filename=$(basename "$FILE")
#				path="${FILE%.*}"
#				filename="${filename%.*}"
#				headerfile=$filename".hpp"
#				cppfile=$filename".cpp"
#				#filename=$(echo "${FILE%%.*}")
#				if [ ! $(find $TCPATH -type f -name $headerfile) ]; 
#				then
#				echo "no suitable header file found for " $FILE 
#				fi
#				done
				break
				;;
		"N" | "n")
				echo "inside naming conventions"
				break
				;;

		"Q" | "q" | "X" | "x")
			# The user probably wants to exit.
			break
			;;	
	esac

	break	
				
done

# All done.
echo -e "${HIGHLIGHT_BLUE}${BOLD}**********************    Closing ValleyForge Interface...    ***********************${NO_COLOUR}\n"
exit 0

