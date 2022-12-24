#!/bin/bash

cd test/
g++ -DSTANDALONE SharedMemoryWrite.cpp -std=c++11 -pthread -o SharedMemoryWrite.out
g++ -DSTANDALONE SharedMemoryRead.cpp -std=c++11 -pthread -o SharedMemoryRead.out