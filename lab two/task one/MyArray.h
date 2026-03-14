#pragma once
#include<iostream>
#include"AbstractArray.h"
using namespace std;

class MyArray : public AbstractArray
{
public:
    MyArray(int _maxCapacity = 0) : AbstractArray(_maxCapacity) {}
    MyArray(const MyArray& ma) : AbstractArray(ma) {}

    void add(int v)
    {
        // add value at next position if array is not full
        if (!isFull())
            values[++currentIndex] = v;
        else
            cout << "Array is full\n";
    }

    bool remove(int& v)
    {
        // remove last element and return it through reference variable
        if (!isEmpty())
        {
            v = values[currentIndex];
            currentIndex--;
            return true;
        }
        return false;
    }

    bool get(int index, int& v)
    {
        // FIX FROM LAB SAMPLE:
        // In the lab manual, get() condition was written in a way
        // that could skip index 0 in the sample logic.
        // Here index >= 0 is used so first element can also be accessed.
        if (index >= 0 && index <= currentIndex)
        {
            v = values[index];
            return true;
        }
        return false;
    }

    void insert(int index, int value)
    {
        // This function replaces value at a valid index
        // It does not create extra space, it only updates existing position
        // This is how insert was used in the provided class design
        if (index >= 0 && index <= currentIndex)
            values[index] = value;
        else
            cout << index << " is invalid\n";
    }
};

// reads n values from user and stores them in array using add()
void read(MyArray& A, istream& in, int n)
{
    int x;
    for (int i = 0; i < n; i++)
    {
        in >> x;
        A.add(x);
    }
}

// displays all values one by one using get()
void display(MyArray& A, ostream& out)
{
    int x;
    for (int i = 0; i < A.size(); i++)
    {
        A.get(i, x);
        out << x << " ";
    }
    out << endl;
}

// copies all elements from src to dst using get() and add()
void copy(MyArray& src, MyArray& dst)
{
    int x;
    for (int i = 0; i < src.size(); i++)
    {
        src.get(i, x);
        dst.add(x);
    }
}

// inserts src values into dst starting from given position
void insert(MyArray& src, MyArray& dst, int pos)
{
    int x;

    // if destination already has that position, replace value there
    // otherwise loop will keep adding values at the end
    for (int i = 0; i < src.size(); i++)
    {
        src.get(i, x);

        if (pos + i < dst.size())
            dst.insert(pos + i, x);
        else
            dst.add(x);
    }
}

// shifts all values one position left starting from given pos
void shiftLeft(MyArray& A, int pos)
{
    int x;

    // invalid position check
    if (pos < 0 || pos >= A.size())
        return;

    // overwrite current position with next position value
    for (int i = pos; i < A.size() - 1; i++)
    {
        A.get(i + 1, x);
        A.insert(i, x);
    }

    // after left shift, last duplicate element is removed
    A.remove(x);
}

// shifts values one position right starting from given pos
void shiftRight(MyArray& A, int pos)
{
    int x;

    // if array is full or position invalid then do nothing
    if (A.isFull() || pos < 0 || pos > A.size())
        return;

    // first create one extra space at the end
    A.add(0);

    // then move values from right to left backward
    for (int i = A.size() - 1; i > pos; i--)
    {
        A.get(i - 1, x);
        A.insert(i, x);
    }

    // place 0 or empty placeholder at given position
    A.insert(pos, 0);
}

// calculates maximum and average of values in array
void stats(MyArray& A, int& max, float& average)
{
    int x;
    int sum = 0;

    // if array is empty then both answers are 0
    if (A.isEmpty())
    {
        max = 0;
        average = 0;
        return;
    }

    // assume first element is maximum in start
    A.get(0, max);

    for (int i = 0; i < A.size(); i++)
    {
        A.get(i, x);
        sum = sum + x;

        if (x > max)
            max = x;
    }

    average = (float)sum / A.size();
}