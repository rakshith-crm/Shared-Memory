#include "../../include/SharedMemory.hpp"

int main()
{
    SharedMemory<double> sharedMemory("DOG");
    std::vector<double> appendData(4 * 4, 44);
    sharedMemory.append(appendData, {1, 4, 4});

    std::vector<double> data(32, 111);
    sharedMemory.append(data, {2, 4, 4});
    
    int temp;
    std::cin >> temp;
}