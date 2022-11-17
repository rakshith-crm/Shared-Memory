#!/bin/bash

cd test/
g++ SharedMemoryWrite.cpp -pthread -lrt -o SharedMemoryWrite.out
g++ SharedMemoryRead.cpp -pthread -lrt -o SharedMemoryRead.out