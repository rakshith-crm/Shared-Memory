#include <iostream>
#include "../include/SharedMemory.hpp"

int main()
{
    SharedMemory<int> sharedMemory("DOG");
    std::vector<int> data = sharedMemory.read();

    for (unsigned int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}