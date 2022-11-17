#include "../include/SharedMemory.hpp"

int main()
{
    SharedMemory<int> sharedMemory("DOG");
    std::vector<int> data(20, 111);
    sharedMemory.write(data, {2, 10});
    std::vector<int> appendData(10, 44);
    sharedMemory.append(appendData, {10});
    int temp;
    std::cin >> temp;
}