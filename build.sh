#!/bin/bash

# STANDALONE COMPILATION
mkdir -p test/lib
mkdir -p test/binary
g++ -DSTANDALONE test/src/SharedMemoryWrite.cpp -std=c++11 -pthread -o test/binary/SharedMemoryWrite.out -lrt
g++ -DSTANDALONE test/src/SharedMemoryRead.cpp -std=c++11 -pthread -o test/binary/SharedMemoryRead.out -lrt


# PYBIND BUILD
mkdir -p build
rm -rf build/*
cd build
cmake ..
make
mv *.so ../test/lib/

