#pragma once
#include "../include/SharedMemory.hpp"

#define SHAPE_END -INT32_MAX
#define PROJECT_KEY 'b'

template <typename T>
SharedMemory<T>::SharedMemory(std::string uniqueKey)
{
    key = ftok(uniqueKey.c_str(), PROJECT_KEY);
    shmid = shmget(key, MAX * sizeof(int), 0666 | IPC_CREAT);
    sharedData = (T *)shmat(shmid, (void *)0, 0);
    std::cout << "Shmid: " << shmid << std::endl;
}

template <typename T>
SharedMemory<T>::~SharedMemory()
{
    shmdt(sharedData);
    shmctl(shmid, IPC_RMID, NULL);
}

template <typename T>
void SharedMemory<T>::write(std::vector<T> data, std::vector<int> shape)
{
    int elementCount = data.size();
    int shapeElementCount = multiply(shape);
    if (elementCount != shapeElementCount)
    {
        std::cout << "\ncount(data) != shape()'s info [" << elementCount << " != " << shapeElementCount << "]" << std::endl;
        return;
    }
    int dimCount = (int)shape.size();
    for (unsigned int shapeIndex = 0; shapeIndex < dimCount; shapeIndex++)
    {
        sharedData[shapeIndex] = shape[shapeIndex];
    }
    sharedData[dimCount] = SHAPE_END;
    for (unsigned int index = 0; index < data.size(); index++)
    {
        sharedData[index + dimCount + 1] = data[index];
    }
}

template <typename T>
std::vector<T> SharedMemory<T>::read()
{
    std::vector<T> data;
    std::vector<int> shape = getShape();
    int dimCount = shape.size();
    int elementCount = multiply(shape);
    std::cout << "\nNumber of Elements: " << elementCount << std::endl;
    for (int i = 0; i < elementCount; i++)
    {
        data.push_back(sharedData[i + dimCount + 1]);
    }
    return data;
}

template <typename T>
void SharedMemory<T>::append(std::vector<T> appendData, std::vector<int> appendShape)
{
    std::vector<int> currentShape = getShape();

    int dimCount = currentShape.size();
    int appendDimCount = appendShape.size();
    int elementCount = 1;
    if (appendDimCount != (dimCount - 1))
    {
        std::cout << "appendData.Shape != currentData.Shape[-1:]" << std::endl;
        return;
    }
    for (int index = 0; index < dimCount; index++)
    {
        if (index > 0 && appendShape[index - 1] != currentShape[index])
        {
            std::cout << "appendData.Shape != currentData.Shape[-1:]" << std::endl;
            return;
        }
        elementCount *= currentShape[index];
    }
}

template <typename T>
std::vector<int> SharedMemory<T>::getShape()
{
    std::vector<int> shape;
    int index = 0;
    while (sharedData[index] != SHAPE_END)
    {
        int value = sharedData[index++];
        shape.push_back(value);
    }
    return shape;
}