#!/bin/bash
count=0
temp=0
while read line
do
	name=$line
	count=$((count+1)) #counter value for printing the line number

	countval=($(grep -n "//" $1 |cut -f1 -d:)) #returns array of line numbers containing // (e.g. 5,21)
	
	for i in "${countval[@]}" #looping through each value to check if next line has // too
	do
		temp=$(($temp+1))
		#echo "temp -> $temp value, i -> $i" 
		echo "next element -> ${countval[$temp]}, current -> ${countval[$i]}"

		if [ "${countval[$i+1]}" ==  $i ] 
		then
			
			tempstart=$i		
			echo "$tempstart is the start of multiple line comments"
		fi
		
	done

	for i in "${countval[@]}"
	do

		if [ $count ==  $i ] 
		then
			echo "$count contains //"
		fi
	done
done < $1
