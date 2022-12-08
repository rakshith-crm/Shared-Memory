#!/bin/bash

c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) shmbind.cpp -o shmbind$(python3-config --extension-suffix) -pthread -lrt