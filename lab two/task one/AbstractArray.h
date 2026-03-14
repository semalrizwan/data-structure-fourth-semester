#pragma once
class AbstractArray
{
protected:
    int currentIndex;
    int* values;
    int maxCapacity;

public:
    AbstractArray(int _maxCapacity = 0)
    {
        // currentIndex starts from -1 which means array is empty
        currentIndex = -1;
        maxCapacity = _maxCapacity;
        // dynamic array created of given capacity and initialized with 0
        values = new int[maxCapacity] {0};
    }

    AbstractArray(const AbstractArray& AA)
    {
        // copy constructor copies size information
        currentIndex = AA.currentIndex;
        maxCapacity = AA.maxCapacity;
        values = new int[maxCapacity] {0};

        // copy all existing elements from old object to new object
        for (int i = 0; i <= currentIndex; i++)
            values[i] = AA.values[i];
    }

    // pure virtual functions so derived class must define them
    virtual void add(int v) = 0;
    virtual bool remove(int& value) = 0;
    virtual bool get(int index, int& value) = 0;
    virtual void insert(int index, int value) = 0;

    bool isEmpty()
    {
        // if currentIndex is -1 then there is no element
        return currentIndex < 0;
    }

    bool isFull()
    {
        // if currentIndex reaches last valid index then array is full
        return currentIndex == maxCapacity - 1;
    }

    int size()
    {
        // actual number of elements = currentIndex + 1
        return currentIndex + 1;
    }
};