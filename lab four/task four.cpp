#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

/*
1. this task uses queue only and reuses earlier functions.
the full problem statement was not visible in the pdf pages i received,
so this file is kept as a ready template for task 4 style solution.

2. the main idea is to solve the problem by dequeue and enqueue only.
if reverse order is needed then stack can be used with proper reason.

3. reused functions from earlier tasks help reduce code and keep logic simple.

4. learned that queue problems can be solved by controlled movement of values.

5. now i can build full queue based programs step by step.
*/

void display(Queue*, ostream&);
void append(Queue* src, Queue* dst);
void append(Queue* src, Queue* dst, int no);
void reverseAppend(Queue* src, Queue* dst);
int getSize(Queue* q);
int get(Queue* q, int pos);
void sort(Queue* q);
bool isPalindrome(Queue* q);
void isPalindrome(Queue* q, bool& flag);
void rotateLeft(Queue* q, int pos);
void rotateRight(Queue* q, int pos);

// write task 4 specific function here
// example:
// void solveProblem(Queue *q);

const int MAX_SIZE = 10;

int main()
{
    Queue* A = new MyQueue(MAX_SIZE);

    // sample input
    A->enqueue(10);
    A->enqueue(9);
    A->enqueue(2);
    A->enqueue(5);
    A->enqueue(-7);

    cout << "queue values: ";
    display(A, cout);

    // call task 4 function here
    // solveProblem(A);

    delete A;
    return 0;
}

// print queue without changing final order
void display(Queue* q, ostream& out)
{
    int n = getSize(q);
    for (int i = 0; i < n; i++)
    {
        int v = q->dequeue();
        out << v << " ";
        q->enqueue(v);
    }
    out << endl;
}

// copy full queue
void append(Queue* src, Queue* dst)
{
    int n = getSize(src);
    for (int i = 0; i < n; i++)
    {
        int v = src->dequeue();
        src->enqueue(v);
        if (!dst->isFull())
        {
            dst->enqueue(v);
        }
    }
}

// copy limited values
void append(Queue* src, Queue* dst, int no)
{
    int n = getSize(src);
    if (no > n)
    {
        no = n;
    }

    for (int i = 0; i < n; i++)
    {
        int v = src->dequeue();
        src->enqueue(v);
        if (i < no && !dst->isFull())
        {
            dst->enqueue(v);
        }
    }
}

// reverse copy using stack
void reverseAppend(Queue* src, Queue* dst)
{
    int n = getSize(src);
    Stack* s = new MyStack(n);

    for (int i = 0; i < n; i++)
    {
        int v = src->dequeue();
        src->enqueue(v);
        s->push(v);
    }

    for (int i = 0; i < n; i++)
    {
        int v = 0;
        if (s->pop(v) && !dst->isFull())
        {
            dst->enqueue(v);
        }
    }

    delete s;
}

// count elements
int getSize(Queue* q)
{
    int count = 0;
    Queue* temp = new MyQueue(MAX_SIZE);

    while (!q->isEmpty())
    {
        int v = q->dequeue();
        temp->enqueue(v);
        count++;
    }

    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
    return count;
}

// remove and return value at given position
int get(Queue* q, int pos)
{
    int n = getSize(q);
    Queue* temp = new MyQueue(MAX_SIZE);
    int val = 0;

    if (pos < 0)
    {
        pos = 0;
    }
    if (pos >= n)
    {
        pos = n - 1;
    }

    for (int i = 0; i < n; i++)
    {
        int v = q->dequeue();
        if (i == pos)
        {
            val = v;
        }
        else
        {
            temp->enqueue(v);
        }
    }

    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
    return val;
}

// sort ascending
void sort(Queue* q)
{
    int n = getSize(q);
    Queue* sorted = new MyQueue(MAX_SIZE);

    for (int i = 0; i < n; i++)
    {
        int currentSize = getSize(q);
        int minVal = q->dequeue();
        q->enqueue(minVal);

        for (int j = 1; j < currentSize; j++)
        {
            int v = q->dequeue();
            q->enqueue(v);
            if (v < minVal)
            {
                minVal = v;
            }
        }

        bool removed = false;
        for (int j = 0; j < currentSize; j++)
        {
            int v = q->dequeue();
            if (v == minVal && !removed)
            {
                removed = true;
            }
            else
            {
                q->enqueue(v);
            }
        }

        sorted->enqueue(minVal);
    }

    while (!sorted->isEmpty())
    {
        q->enqueue(sorted->dequeue());
    }

    delete sorted;
}

// palindrome using stack
bool isPalindrome(Queue* q)
{
    int n = getSize(q);
    Queue* temp = new MyQueue(MAX_SIZE);
    Stack* s = new MyStack(n);

    for (int i = 0; i < n; i++)
    {
        int v = q->dequeue();
        q->enqueue(v);
        temp->enqueue(v);
        s->push(v);
    }

    bool ok = true;
    for (int i = 0; i < n; i++)
    {
        int a = temp->dequeue();
        int b = 0;
        s->pop(b);

        if (a != b)
        {
            ok = false;
        }
    }

    delete temp;
    delete s;
    return ok;
}

// palindrome without extra adt for single digits
void isPalindrome(Queue* q, bool& flag)
{
    int n = getSize(q);
    int forward = 0;
    int reverse = 0;
    int place = 1;

    for (int i = 0; i < n; i++)
    {
        int v = q->dequeue();
        q->enqueue(v);
        forward = forward * 10 + v;
        reverse = reverse + v * place;
        place *= 10;
    }

    flag = (forward == reverse);
}

// rotate left from position
void rotateLeft(Queue* q, int pos)
{
    int n = getSize(q);

    if (n <= 1 || pos < 0 || pos >= n - 1)
    {
        return;
    }

    Queue* temp = new MyQueue(MAX_SIZE);

    for (int i = 0; i < pos; i++)
    {
        temp->enqueue(q->dequeue());
    }

    int first = q->dequeue();

    while (!q->isEmpty())
    {
        temp->enqueue(q->dequeue());
    }

    temp->enqueue(first);

    while (!temp->isEmpty())
    {
        q->enqueue(temp->dequeue());
    }

    delete temp;
}

// rotate right from position
void rotateRight(Queue* q, int pos)
{
    int n = getSize(q);

    if (n <= 1 || pos < 0 || pos >= n - 1)
    {
        return;
    }

    Queue* left = new MyQueue(MAX_SIZE);
    Queue* right = new MyQueue(MAX_SIZE);

    for (int i = 0; i < pos; i++)
    {
        left->enqueue(q->dequeue());
    }

    while (!q->isEmpty())
    {
        right->enqueue(q->dequeue());
    }

    int size = getSize(right);

    for (int i = 0; i < size - 1; i++)
    {
        right->enqueue(right->dequeue());
    }

    while (!left->isEmpty())
    {
        q->enqueue(left->dequeue());
    }

    while (!right->isEmpty())
    {
        q->enqueue(right->dequeue());
    }

    delete left;
    delete right;
}