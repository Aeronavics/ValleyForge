#!/bin/bash
count=0
while read line
do
    name=$line
    count=$((count+1))
if sed "$count s://://:" $1
then
echo "$count contains //"
fi
    echo "$count Text read from file - $name"
done < $1
