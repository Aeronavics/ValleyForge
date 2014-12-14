#!/bin/bash

if [ $(dpkg-query -W -f='${Status}' uncrustify 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
  sudo apt-get install uncrustify;
fi
uncrustify -c my.cfg -f kevin_can.cpp -o kevin_can.cpp
sed -i 's:\(.*\)/[*]\(.*\)[*]/:\1 // \2:' kevin_can.cpp
