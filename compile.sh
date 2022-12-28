#!/bin/bash

g++ -DSTANDALONE test/src/SharedMemoryWrite.cpp -std=c++11 -pthread -o test/binary/SharedMemoryWrite.out
g++ -DSTANDALONE test/src/SharedMemoryRead.cpp -std=c++11 -pthread -o test/binary/SharedMemoryRead.out
