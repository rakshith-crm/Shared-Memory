#include "../include/SharedMemory.hpp"

int main()
{
    SharedMemory<int> sharedMemory("DOG");
    std::vector<int> data(32, 111);
    sharedMemory.write(data, {2, 4, 4});
    std::vector<int> appendData(4 * 4, 44);
    sharedMemory.append(appendData, {1, 4, 4});
    int temp;
    std::cin >> temp;
}