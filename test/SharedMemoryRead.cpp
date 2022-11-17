#include <iostream>
#include "../include/SharedMemory.hpp"

int main()
{
    SharedMemory<float> sharedMemory("sample");
    std::vector<float> data = sharedMemory.read();

    for (unsigned int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    // SharedMemory<float> sharedMemory2("hello", 2);
    // std::vector<float> data2 = sharedMemory2.read();

    // for (unsigned int i = 0; i < data2.size(); i++)
    // {
    //     std::cout << data2[i] << " ";
    // }
}