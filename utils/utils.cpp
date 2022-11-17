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