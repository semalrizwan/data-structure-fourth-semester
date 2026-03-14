#pragma once
#include<iostream>
using namespace std;
class Stack
{
protected:
    int currentIndex;   // represents the top of the stack
    int* values;        // dynamic array to store stack values
    int maxCapacity;    // maximum size of stack

public:

    Stack(int _maxCapacity = 0)
    {
        // stack initially empty
        currentIndex = -1;

        // set maximum capacity
        maxCapacity = _maxCapacity;

        // allocate memory for stack values and initialize with 0
        values = new int[maxCapacity] {0};
    }

    Stack(const Stack& AA)
    {
        // copy constructor copies stack information
        currentIndex = AA.currentIndex;
        maxCapacity = AA.maxCapacity;

        values = new int[maxCapacity] {0};

        // copy all elements from old stack
        for (int i = 0; i <= currentIndex; i++)
            values[i] = AA.values[i];
    }

    // pure virtual functions
    // derived class must implement them
    virtual void push(int v) = 0;
    virtual bool pop(int& value) = 0;

    bool isEmpty()
    {
        // if top is -1 stack is empty
        return currentIndex < 0;
    }

    bool isFull()
    {
        // if top reaches last index stack is full
        return currentIndex == maxCapacity - 1;
    }

    int size()
    {
        // number of elements stored in stack
        return currentIndex + 1;
    }
};
