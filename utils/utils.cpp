#include <vector>

int multiply(std::vector<int> data)
{
    if (data.size() == 0)
    {
        return 0;
    }
    int size = data.size();
    int count = 1;
    for (int i = 0; i < size; i++)
    {
        count *= data[i];
    }
    return count;
}

template <typename T>
void printVector(std::vector<T> data)
{
    for (unsigned int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << " ";
    }
}
