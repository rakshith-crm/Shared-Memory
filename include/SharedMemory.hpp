#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include "../utils/utils.cpp"

namespace py = pybind11;

template <typename T>
class SharedMemory
{
private:
    int shm_fd;
    char *uniqueKey;
    T *sharedData;

public:
    SharedMemory(const char *);
    ~SharedMemory();
    std::vector<T> read();
    py::array_t<T> readNumpy();
    void write(std::vector<T>, std::vector<int>);
    void append(std::vector<T>, std::vector<int>);
    std::vector<int> getShape();
};

#include "../src/SharedMemory.cpp"