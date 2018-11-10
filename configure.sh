#!/bin/bash

# create a build directory
echo "[INFO] Creating build directory."
mkdir -p build

# move to build directory
echo "[INFO] Changing working directory to build."
cd build

# create make file
echo "[INFO] Creating makefile based on the ../CMakeLists.txt"
cmake ../

# build the project
if [[ $? -eq 0 ]]; then
    echo "[INFO] Building the project using make."
    make
else
    echo "[ERROR] Could not create makefile"
    cd ..
fi

# cp the executable from build directory to bin
if [[ $? -eq 0 ]]; then
    echo "[INFO] Creating bin directory for installing the binary executable."
    mkdir -p ../bin
    echo "[INFO] Copying generated binary to bin directory."
    cp playmusic ../bin/
    echo "[INFO] Changing working directory back to root - playmusic."
    cd ..
    echo "[INFO] Cleaning up the build directory."
    rm -rf build
else
    echo -e "[Error] Could not build the project"
fi

