#include <iostream>
#include "../include/SharedMemory.hpp"

int main()
{
    SharedMemory<float> sharedMemory("/dev/shm/file1");
    std::vector<float> data(32, 7.3);
    sharedMemory.write(data, {8, 2, 2});

    SharedMemory<float> sharedMemory2("/dev/shm/file2");
    std::vector<float> data2(10, 2.2);
    sharedMemory2.write(data2, {10});

    int temp;
    std::cin >> temp;
}