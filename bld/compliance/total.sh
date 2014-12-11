#!/bin/bash
count=0
while read line
do
    name=$line
    count=$((count+1))
if sed -n "$count s://:c:" $1; then
echo "$count contains //"
fi
done < $1



//trying out for arrays


#!/bin/bash
count=0
while read line
do
    name=$line
    count=$((count+1))
    countval=($(grep -n "//" sample.cpp |cut -f1 -d:))
for i in "${countval[@]}"
do
if [ $count ==  "${countval[$i]}" ]
then
echo "$count contains //"
fi
done
done < $1



//working one without arrays


#!/bin/bash
count=0
while read line
do
    name=$line
    count=$((count+1))
    countval=($(grep -n "//" sample.cpp |cut -f1 -d:))

if [ $count ==  ${countval[0]} ] || [ $count ==  ${countval[1]} ]
then
echo "$count contains //"
fi

done < $1



//array working


