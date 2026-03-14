#pragma once
#include<iostream>
#include"Stack.h"
using namespace std;
class MyStack : public Stack
{
public:

    // constructor calls base class constructor
    MyStack(int _maxCapacity = 0) : Stack(_maxCapacity) {}

    // copy constructor
    MyStack(const MyStack& ms) : Stack(ms) {}

    void push(int v)
    {
        // push adds element at top of stack

        if (!isFull())
            values[++currentIndex] = v;

        else
            cout << "Stack is full\n";
    }

    bool pop(int& v)
    {
        // pop removes element from top

        if (!isEmpty())
        {
            v = values[currentIndex];
            currentIndex--;
            return true;
        }

        return false;
    }
};
// read values from user and push them into stack
void read(MyStack& S, istream& in, int n)
{
    int x;

    for (int i = 0; i < n; i++)
    {
        in >> x;
        S.push(x);
    }
}
// display stack values without losing original data
// move values to temporary stack
// print them while restoring original stack
void display(MyStack& S, ostream& out)
{
    MyStack temp(S.size());
    int x;

    while (S.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        out << x << " ";
        S.push(x);
    }

    out << endl;
}
// copy one stack into another without destroying source stack
// move src to temp stack
// restore src while pushing values to destination
void copy(MyStack& src, MyStack& dst)
{
    MyStack temp(src.size());
    int x;

    while (src.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        src.push(x);
        dst.push(x);
    }
}
// insert src stack into dst stack at given position
// position counted from bottom
void insert(MyStack& src, MyStack& dst, int pos)
{
    MyStack tempDst(dst.size());
    MyStack tempSrc(src.size());
    MyStack newDst(dst.size() + src.size());

    int x;
    int count = 0;
    bool inserted = false;

    // reverse dst so bottom element can be accessed first
    while (dst.pop(x))
        tempDst.push(x);

    while (tempDst.pop(x))
    {
        if (count == pos)
        {
            // copy src stack values
            while (src.pop(x))
                tempSrc.push(x);

            while (tempSrc.pop(x))
            {
                src.push(x);
                newDst.push(x);
            }

            inserted = true;
        }

        newDst.push(x);
        count++;
    }

    // if position is at end
    if (!inserted)
    {
        while (src.pop(x))
            tempSrc.push(x);

        while (tempSrc.pop(x))
        {
            src.push(x);
            newDst.push(x);
        }
    }

    // restore correct order
    while (newDst.pop(x))
        tempDst.push(x);

    while (tempDst.pop(x))
        dst.push(x);
}
// shift stack values up from given position
// means elements above pos move upward
void shiftUp(MyStack& S, int pos)
{
    MyStack temp(S.size() + 1);
    MyStack newStack(S.size() + 1);

    int x;
    int count = 0;

    if (S.isFull() || pos < 0 || pos > S.size())
        return;

    // reverse stack
    while (S.pop(x))
        temp.push(x);

    // rebuild stack
    while (temp.pop(x))
    {
        if (count == pos)
            newStack.push(0);

        newStack.push(x);
        count++;
    }

    if (pos == count)
        newStack.push(0);

    while (newStack.pop(x))
        temp.push(x);

    while (temp.pop(x))
        S.push(x);
}
// shift stack values down from given position
// element at pos removed and others move down
void shiftDown(MyStack& S, int pos)
{
    MyStack temp(S.size());
    MyStack newStack(S.size());

    int x;
    int count = 0;

    if (pos < 0 || pos >= S.size())
        return;

    while (S.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        if (count != pos)
            newStack.push(x);

        count++;
    }

    while (newStack.pop(x))
        temp.push(x);

    while (temp.pop(x))
        S.push(x);
}
// calculate maximum and average values stored in stack
// stack restored after calculation
void stats(MyStack& S, int& max, float& average)
{
    MyStack temp(S.size());

    int x;
    int sum = 0;
    int count = 0;

    if (S.isEmpty())
    {
        max = 0;
        average = 0;
        return;
    }

    S.pop(x);

    max = x;
    sum = x;
    count = 1;

    temp.push(x);

    while (S.pop(x))
    {
        temp.push(x);

        sum += x;
        count++;

        if (x > max)
            max = x;
    }

    // restore stack
    while (temp.pop(x))
        S.push(x);

    average = (float)sum / count;
}

