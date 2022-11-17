#!/bin/bash

cd test/
c++ SharedMemoryWrite.cpp -pthread -lrt -o SharedMemoryWrite.out
c++ SharedMemoryRead.cpp -pthread -lrt -o SharedMemoryRead.out