#!/bin/bash

chmod +x "scripts/build.sh"
"scripts/build.sh"
cd ./build
ctest
