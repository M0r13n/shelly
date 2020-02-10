#!/bin/bash
if [ -d ./build ] && [ -e ./build/shelly ]
then
    ./build/shelly
else
   chmod +x "./build.sh"
    "./build.sh"
    ./build/shelly
fi