#include "../../include/SharedMemory.hpp"

int main()
{
    SharedMemory<long double> sharedMemory("DOG");
    std::vector<long double> appendData(4 * 4, 44);
    sharedMemory.append(appendData, {1, 4, 4});

    std::vector<long double> data(32, 111);
    sharedMemory.append(data, {2, 4, 4});
    
    int temp;
    std::cin >> temp;
}