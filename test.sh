#!/bin/bash

chmod +x "./build.sh"
"./build.sh"
cd ./build
ctest
