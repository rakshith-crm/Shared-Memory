#pragma once
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "../utils/utils.cpp"

#define KEY "VECTOR"
#define MAX 1000000

template <typename T>
class SharedMemory
{
private:
    T *sharedData;
    int shm_fd;
    key_t key;
    int shmid;

public:
    SharedMemory(std::string);
    ~SharedMemory();
    std::vector<T> read();
    ;
    void write(std::vector<T>, std::vector<int>);
    void append(std::vector<T>, std::vector<int>);
    std::vector<int> getShape();
};

#include "../src/SharedMemory.cpp"