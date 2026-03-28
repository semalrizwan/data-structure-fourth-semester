#include <iostream>
using namespace std;

#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

// myqueue function definitions
void MyQueue::enqueue(const int& value)
{
    // check if queue is full
    if (isFull())
    {
        cout << "Queue is full\n";
        return;
    }

    // first element case
    if (isEmpty())
    {
        startOfQIndex = 0;
        topOfQIndex = 0;
        values[topOfQIndex] = value;
        count++;
        return;
    }

    // move rear forward in circular way
    topOfQIndex = (topOfQIndex + 1) % maxCapacity;
    values[topOfQIndex] = value;
    count++;
}

int MyQueue::dequeue()
{
    // check if queue is empty
    if (isEmpty())
    {
        cout << "Queue is empty\n";
        return 0;
    }

    // take front value
    int value = values[startOfQIndex];

    // if only one element
    if (count == 1)
    {
        startOfQIndex = -1;
        topOfQIndex = -1;
        count = 0;
        return value;
    }

    // move front forward
    startOfQIndex = (startOfQIndex + 1) % maxCapacity;
    count--;
    return value;
}

void MyQueue::display(ostream& out) const
{
    // check if queue empty
    if (isEmpty())
    {
        out << "Empty";
        return;
    }

    int idx = startOfQIndex;

    // print all elements
    for (int i = 0; i < count; i++)
    {
        out << values[idx] << " ";
        idx = (idx + 1) % maxCapacity;
    }
}

// function prototypes
void read(Queue*, istream&);
void display(Queue*, ostream&);
void append(Queue* src, Queue* dst);
void append(Queue* src, Queue* dst, int no);
void reverseAppend(Queue* src, Queue* dst);
int getSize(Queue* q);
void stats(Queue* q, int& sum, float& average);
bool isEqual(Queue*, Queue*);

const int MAX_SIZE = 5;

int main()
{
    Queue* A = new MyQueue(MAX_SIZE);
    int n = 0;

    // read values into queue
    read(A, cin);

    cout << " Queue A Values: ";
    display(A, cout);

    Queue* B = new MyQueue(MAX_SIZE);

    // copy all values from A to B
    append(A, B);

    cout << " Queue B Values: ";
    display(B, cout);

    Queue* C = new MyQueue(MAX_SIZE);

    // add initial values in C
    C->enqueue(9);
    C->enqueue(7);
    C->enqueue(5);

    // append first 2 values from A into C
    append(A, C, 2);

    cout << "Queue C Values after append of 2 values from A: ";
    display(C, cout);

    Queue* D = new MyQueue(MAX_SIZE);

    // append values of C into D in reverse order
    reverseAppend(C, D);

    cout << "Queue D Values after reverse append from V: ";
    display(D, cout);

    int mx = 0;
    float ag = 0.0;

    // calculate max and average
    stats(A, mx, ag);

    cout << "Queue A Values: ";
    display(A, cout);

    cout << "Average is " << ag << " maximum is " << mx << endl;

    Queue* M = new MyQueue(MAX_SIZE);
    Queue* N = new MyQueue(MAX_SIZE);
    Queue* P = new MyQueue(MAX_SIZE);

    // test equality
    append(A, M);
    append(N, M);
    append(N, P);
    P->enqueue(111);

    if (!isEqual(A, M))
    {
        cout << "Not Equal:\n";
    }
    else
    {
        cout << "Equal:\n";
    }

    if (!isEqual(A, P))
    {
        cout << "Not Equal:\n";
    }
    else
    {
        cout << "Equal:\n";
    }

    delete A;
    delete B;
    delete C;
    delete D;
    delete M;
    delete N;
    delete P;

    return 0;
}

void read(Queue* q, istream& in)
{
    int value;

    // keep taking input until queue is full
    while (!q->isFull())
    {
        in >> value;
        q->enqueue(value);
    }
}

void display(Queue* q, ostream& out)
{
    int size = getSize(q);

    // remove each element and reinsert to keep order same
    for (int i = 0; i < size; i++)
    {
        int value = q->dequeue();
        out << value << " ";
        q->enqueue(value);
    }

    out << endl;
}

int getSize(Queue* q)
{
    int size = 0;

    Queue* temp = new MyQueue(MAX_SIZE);

    // move elements to temp and count
    while (!q->isEmpty())
    {
        int value = q->dequeue();
        temp->enqueue(value);
        size++;
    }

    // move back to original queue
    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
    return size;
}

void append(Queue* src, Queue* dst)
{
    int size = getSize(src);

    // copy all elements and restore src
    for (int i = 0; i < size; i++)
    {
        int value = src->dequeue();

        if (!dst->isFull())
        {
            dst->enqueue(value);
        }

        src->enqueue(value);
    }
}

void append(Queue* src, Queue* dst, int no)
{
    int size = getSize(src);

    if (no > size)
    {
        no = size;
    }

    // copy only first no elements
    for (int i = 0; i < size; i++)
    {
        int value = src->dequeue();

        if (i < no && !dst->isFull())
        {
            dst->enqueue(value);
        }

        src->enqueue(value);
    }
}

void reverseAppend(Queue* src, Queue* dst)
{
    // stack is used to reverse order

    int size = getSize(src);

    MyStack s(size);
    Queue* temp = new MyQueue(MAX_SIZE);

    // move values to stack and temp
    for (int i = 0; i < size; i++)
    {
        int value = src->dequeue();
        s.push(value);
        temp->enqueue(value);
    }

    // restore original queue
    while (!temp->isEmpty())
    {
        src->enqueue(temp->dequeue());
    }

    // pop from stack and add to dst
    for (int i = 0; i < size; i++)
    {
        int value;

        if (s.pop(value))
        {
            if (!dst->isFull())
            {
                dst->enqueue(value);
            }
        }
    }

    delete temp;
}

void stats(Queue* q, int& sum, float& average)
{
    int size = getSize(q);

    if (size == 0)
    {
        sum = 0;
        average = 0;
        return;
    }

    int value = q->dequeue();

    int maximum = value;
    int total = value;

    q->enqueue(value);

    // find max and total
    for (int i = 1; i < size; i++)
    {
        value = q->dequeue();

        if (value > maximum)
        {
            maximum = value;
        }

        total += value;

        q->enqueue(value);
    }

    // store max in sum variable as used in main
    sum = maximum;

    average = (float)total / size;
}

bool isEqual(Queue* q1, Queue* q2)
{
    int size1 = getSize(q1);
    int size2 = getSize(q2);

    if (size1 != size2)
    {
        return false;
    }

    // compare each element
    for (int i = 0; i < size1; i++)
    {
        int v1 = q1->dequeue();
        int v2 = q2->dequeue();

        q1->enqueue(v1);
        q2->enqueue(v2);

        if (v1 != v2)
        {
            return false;
        }
    }

    return true;
}