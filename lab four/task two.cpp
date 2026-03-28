#include <iostream>
using namespace std;

#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

const int MAX_SIZE = 10;

// myqueue functions

void MyQueue::enqueue(const int& value)
{
    // check if queue is full
    if (isFull())
    {
        cout << "queue is full\n";
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

    // move rear in circular way
    topOfQIndex = (topOfQIndex + 1) % maxCapacity;
    values[topOfQIndex] = value;
    count++;
}

int MyQueue::dequeue()
{
    // check if queue is empty
    if (isEmpty())
    {
        cout << "queue is empty\n";
        return 0;
    }

    // store front value
    int value = values[startOfQIndex];

    // if only one element
    if (count == 1)
    {
        startOfQIndex = -1;
        topOfQIndex = -1;
        count = 0;
        return value;
    }

    // move front in circular way
    startOfQIndex = (startOfQIndex + 1) % maxCapacity;
    count--;
    return value;
}

void MyQueue::display(ostream& out) const
{
    // check if empty
    if (isEmpty())
    {
        out << "empty";
        return;
    }

    int idx = startOfQIndex;

    // print all values
    for (int i = 0; i < count; i++)
    {
        out << values[idx] << " ";
        idx = (idx + 1) % maxCapacity;
    }
}

/*
fix in myqueue:
values was used but not declared, so int * values was added in myqueue.h.
also values should be nullptr when size is 0.

1. what i understood

in this task, i have to reuse queue functions from task 1 and make new functions.
i need to insert one value in a queue at a given position.
i also need to insert one queue into another queue at a given position.
after that i need to shift part of the queue right and left from a given position.

2. how this task works

the main idea is to remove values from the queue one by one and put them in a temporary queue.
while moving values, the needed insertion or shifting is done.
after that, values are moved back to the original queue.

example for insert value:
(10 -> 20 -> 30)
insert 99 at pos 1
result:
(10 -> 99 -> 20 -> 30)

example for insert queue:
src = (1 -> 2)
dst = (10 -> 20 -> 30)
insert at pos 1
result:
(10 -> 1 -> 2 -> 20 -> 30)

example for shiftright:
(10 -> 20 -> 30 -> 40 -> 50)
from pos 2, part is:
(30 -> 40 -> 50)
after right shift:
(50 -> 30 -> 40)
final:
(10 -> 20 -> 50 -> 30 -> 40)

example for shiftleft:
(10 -> 20 -> 30 -> 40 -> 50)
from pos 2, part is:
(30 -> 40 -> 50)
after left shift:
(40 -> 50 -> 30)
final:
(10 -> 20 -> 40 -> 50 -> 30)

3. functions reused

getsize, display, append and isequal logic from task 1 is reused here.
the same dequeue and enqueue idea is used again and again to keep queue order safe.

4. what i learned

i learned how to insert and shift values in a queue without using arrays or other data types.
i also learned how to work only on the part of a queue starting from a position.

5. skills developed

now i can solve queue problems where i need to insert values,
join queues, and shift a part of queue left or right.
*/

// function prototypes from task 1
void display(Queue*, ostream&);
void append(Queue* src, Queue* dst);
void append(Queue* src, Queue* dst, int no);
void reverseAppend(Queue* src, Queue* dst);
int getSize(Queue* q);
bool isEqual(Queue*, Queue*);

// task 2 function prototypes
void insert(Queue* src, Queue* dst, int pos);
void insert(Queue* q, int v, int pos);
void shiftRight(Queue* q, int pos);
void shiftLeft(Queue* q, int pos);

int main()
{
    Queue* A = new MyQueue(MAX_SIZE);
    A->enqueue(10);
    A->enqueue(9);
    A->enqueue(2);
    A->enqueue(5);
    A->enqueue(-7);

    cout << " queue a values: ";
    display(A, cout);

    Queue* B = new MyQueue(MAX_SIZE);

    // insert one value in b
    insert(B, -100, 2);

    cout << " queue b values after insert: ";
    display(B, cout);

    // insert queue a into b
    insert(A, B, 2);

    cout << " queue b values after insert: ";
    display(B, cout);

    // shift part of b to right
    shiftRight(B, 2);

    cout << " queue b values after shiftright from pos 2";
    display(B, cout);

    // shift part of b to left
    shiftLeft(B, 2);

    cout << " queue b values after shiftleft from pos 2: ";
    display(B, cout);

    delete A;
    delete B;

    return 0;
}

// reused functions from task 1

void display(Queue* q, ostream& out)
{
    int size = getSize(q);

    // remove and reinsert each value
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

    // move values to temp and count
    while (!q->isEmpty())
    {
        int value = q->dequeue();
        temp->enqueue(value);
        size++;
    }

    // restore original queue
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

    // copy all values and restore src
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

    // copy only first no values
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
    // stack is used here to get reverse order

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

    // restore src
    while (!temp->isEmpty())
    {
        src->enqueue(temp->dequeue());
    }

    // move reverse values to dst
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

bool isEqual(Queue* q1, Queue* q2)
{
    int size1 = getSize(q1);
    int size2 = getSize(q2);

    if (size1 != size2)
    {
        return false;
    }

    // compare values one by one
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

// task 2 functions

void insert(Queue* q, int v, int pos)
{
    int size = getSize(q);

    // fix position if out of range
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos > size)
    {
        pos = size;
    }

    Queue* temp = new MyQueue(MAX_SIZE);

    // copy values and insert new value at required position
    for (int i = 0; i < size; i++)
    {
        if (i == pos && !temp->isFull())
        {
            temp->enqueue(v);
        }

        temp->enqueue(q->dequeue());
    }

    // if position is at end
    if (pos == size && !temp->isFull())
    {
        temp->enqueue(v);
    }

    // move values back to original queue
    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
}

void insert(Queue* src, Queue* dst, int pos)
{
    int dstSize = getSize(dst);
    int srcSize = getSize(src);

    // fix position if out of range
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos > dstSize)
    {
        pos = dstSize;
    }

    Queue* temp = new MyQueue(MAX_SIZE);

    // move dst values and insert src at required position
    for (int i = 0; i < dstSize; i++)
    {
        int value = dst->dequeue();

        if (i == pos)
        {
            for (int j = 0; j < srcSize; j++)
            {
                int svalue = src->dequeue();

                if (!temp->isFull())
                {
                    temp->enqueue(svalue);
                }

                src->enqueue(svalue);
            }
        }

        if (!temp->isFull())
        {
            temp->enqueue(value);
        }
    }

    // if insert position is at end
    if (pos == dstSize)
    {
        for (int j = 0; j < srcSize; j++)
        {
            int svalue = src->dequeue();

            if (!temp->isFull())
            {
                temp->enqueue(svalue);
            }

            src->enqueue(svalue);
        }
    }

    // move values back to dst
    while (!temp->isEmpty())
    {
        dst->enqueue(temp->dequeue());
    }

    delete temp;
}

void shiftRight(Queue* q, int pos)
{
    int size = getSize(q);

    // fix invalid cases
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos >= size || size - pos <= 1)
    {
        return;
    }

    Queue* temp = new MyQueue(MAX_SIZE);
    Queue* part = new MyQueue(MAX_SIZE);

    // keep first part same
    for (int i = 0; i < pos; i++)
    {
        temp->enqueue(q->dequeue());
    }

    int partSize = size - pos;

    // move second part to another queue
    for (int i = 0; i < partSize; i++)
    {
        part->enqueue(q->dequeue());
    }

    int lastValue = 0;

    // remove last value of second part
    for (int i = 0; i < partSize; i++)
    {
        int value = part->dequeue();

        if (i == partSize - 1)
        {
            lastValue = value;
        }
        else
        {
            part->enqueue(value);
        }
    }

    // put last value first
    temp->enqueue(lastValue);

    // then put remaining values
    while (!part->isEmpty())
    {
        temp->enqueue(part->dequeue());
    }

    // restore queue
    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
    delete part;
}

void shiftLeft(Queue* q, int pos)
{
    int size = getSize(q);

    // fix invalid cases
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos >= size || size - pos <= 1)
    {
        return;
    }

    Queue* temp = new MyQueue(MAX_SIZE);

    // keep first part same
    for (int i = 0; i < pos; i++)
    {
        temp->enqueue(q->dequeue());
    }

    int partSize = size - pos;

    // first value of second part goes to end
    int firstValue = q->dequeue();

    // move remaining values first
    for (int i = 1; i < partSize; i++)
    {
        temp->enqueue(q->dequeue());
    }

    // put old first value at end
    temp->enqueue(firstValue);

    // restore queue
    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
}