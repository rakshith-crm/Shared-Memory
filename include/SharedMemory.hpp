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
#include <semaphore.h>
#include "../utils/utils.cpp"

#ifndef STANDALONE
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
#endif

template <typename T>
class SharedMemory
{
private:
    static int objectCount;
    int shm_fd;
    char *uniqueKey;
    T *sharedData;
    sem_t mutex;
    void write(std::vector<T>, std::vector<int>);

public:
    SharedMemory(const char *);
    ~SharedMemory();
    std::vector<T> read();
#ifndef STANDALONE
    py::array_t<T> readNumpy();
#endif
    void append(std::vector<T>, std::vector<int>);
    std::vector<int> getShape();
    void close();
};

#include "../src/SharedMemory.cpp"