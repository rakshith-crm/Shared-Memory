#!/bin/bash

# STANDALONE COMPILATION
g++ -DSTANDALONE test/src/SharedMemoryWrite.cpp -std=c++11 -pthread -o test/binary/SharedMemoryWrite.out
g++ -DSTANDALONE test/src/SharedMemoryRead.cpp -std=c++11 -pthread -o test/binary/SharedMemoryRead.out


# PYBIND BUILD
rm -rf build/*
cd build
cmake ..
make
mv *.so ../test/lib/

