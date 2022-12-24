#pragma once
#include "../include/SharedMemory.hpp"

#define SHAPE_END -INT32_MAX
#define SIZE 1048576

template <typename T>
SharedMemory<T>::SharedMemory(const char *uniqueKey)
{
    this->shm_fd = shm_open(uniqueKey, O_CREAT | O_RDWR, 0666);
    this->uniqueKey = (char *)uniqueKey;
    ftruncate(shm_fd, SIZE * sizeof(T));
    sharedData = (T *)mmap(0, SIZE * sizeof(T), PROT_WRITE, MAP_SHARED, shm_fd, 0);
}

template <typename T>
SharedMemory<T>::~SharedMemory()
{
    shm_unlink(this->uniqueKey);
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
    for (int shapeIndex = 0; shapeIndex < dimCount; shapeIndex++)
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
    if (dimCount == 0)
    {
        return std::vector<T>();
    }
    int elementCount = multiply(shape);
    if (sharedData[0] == 0)
    {
        return std::vector<T>();
    }
    std::cout << "Shape: [ ";
    printVector(shape);
    std::cout << "]" << std::endl;
    for (int i = 0; i < elementCount; i++)
    {
        data.push_back(sharedData[i + dimCount + 1]);
    }
    return data;
}

#ifndef STANDALONE
template <typename T>
py::array_t<T> SharedMemory<T>::readNumpy()
{
    std::vector<T> data = this->read();
    std::vector<int> shape = this->getShape();
    int count = (int)data.size();
    auto result = py::array_t<T>(count);

    py::buffer_info buf3 = result.request();

    T *ptr3 = static_cast<T *>(buf3.ptr);

    for (int index = 0; index < count; index++)
    {
        ptr3[index] = data[index];
    }
    return result.reshape(shape);
}
#endif

template <typename T>
void SharedMemory<T>::append(std::vector<T> appendData, std::vector<int> appendShape)
{
    sem_wait(&mutex);
    if(sharedData[0] == 0)
    {
        this->write(appendData, appendShape);
        sem_post(&mutex);
        return;
    }
    std::vector<int> currentShape = getShape();
    int dimCount = currentShape.size();
    int appendDimCount = appendShape.size();

    int appendElementCount = multiply(appendShape);
    int currentElementCount = multiply(currentShape);
    if ((int)appendData.size() != appendElementCount)
    {
        std::cout << "\ncount(data) != shape()'s info [" << appendData.size() << " != " << appendElementCount << "]" << std::endl;
        return;
    }
    if (appendDimCount != dimCount)
    {
        std::cout << "appendDimCount " << appendDimCount << " != currentData.Shape[-1:]"
                  << " " << dimCount << " " << std::endl;
        return;
    }
    for (int index = 0; index < dimCount; index++)
    {
        if (index > 0 && appendShape[index] != currentShape[index])
        {
            std::cout << "appendData.Shape != currentData.Shape[-1:]"
                      << "index: " << index << std::endl;
            return;
        }
    }
    for (int i = 0; i < appendElementCount; i++)
    {
        sharedData[dimCount + 1 + currentElementCount + i] = appendData[i];
    }
    sharedData[0] += appendShape[0];
    sem_post(&mutex);
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