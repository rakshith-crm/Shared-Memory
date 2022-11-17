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
#include "../utils/utils.cpp"

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
    ;
    void write(std::vector<T>, std::vector<int>);
    void append(std::vector<T>, std::vector<int>);
    std::vector<int> getShape();
};

#include "../src/SharedMemory.cpp"