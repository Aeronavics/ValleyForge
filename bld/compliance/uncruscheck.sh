#!/bin/bash

uncrustify -c my.cfg -f kevin_can.cpp -o kevin_can.cpp
sed -i 's:\(.*\)/[*]\(.*\)[*]/:\1 // \2:' kevin_can.cpp
