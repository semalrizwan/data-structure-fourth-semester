#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

/*
1. this task is about doing different operations on queue like rotate, get,
sort and palindrome check using queue only.

2. i will move values using dequeue and enqueue and rebuild queue step by step.
no direct access is possible so everything is done by rotation.

3. reused functions like display, append, getSize help in reducing code.

*/

void display(Queue*, ostream&);
void append(Queue* src, Queue* dst);
void append(Queue* src, Queue* dst, int no);
void reverseAppend(Queue* src, Queue* dst);
int getSize(Queue* q);
void insert(Queue* src, Queue* dst, int pos);
void insert(Queue* q, int v, int pos);
void shiftRight(Queue* q, int pos);
void shiftLeft(Queue* q, int pos);
bool isEqual(Queue*, Queue*);
int get(Queue* q, int pos);
void sort(Queue*);
bool isPalindrome(Queue*);
void isPalindrome(Queue*, bool&);
void rotateLeft(Queue* q, int pos);
void rotateRight(Queue* q, int pos);

const int MAX_SIZE = 10;

int main()
{
    Queue* A = new MyQueue(MAX_SIZE);

    A->enqueue(10);
    A->enqueue(9);
    A->enqueue(2);
    A->enqueue(5);
    A->enqueue(-7);

    cout << "Queue A: ";
    display(A, cout);

    rotateRight(A, 2);
    cout << "after rotate right: ";
    display(A, cout);

    rotateLeft(A, 2);
    cout << "after rotate left: ";
    display(A, cout);

    int v = get(A, 3);
    cout << "value removed: " << v << endl;

    cout << "after get: ";
    display(A, cout);

    if (isPalindrome(A))
        cout << "A is palindrome\n";
    else
        cout << "A is not palindrome\n";

    Queue* C = new MyQueue(MAX_SIZE);
    C->enqueue(234);
    C->enqueue(56);
    C->enqueue(786);
    C->enqueue(56);
    C->enqueue(234);

    if (isPalindrome(C))
        cout << "C is palindrome\n";
    else
        cout << "C is not palindrome\n";

    Queue* D = new MyQueue(MAX_SIZE);
    D->enqueue(3);
    D->enqueue(5);
    D->enqueue(7);
    D->enqueue(5);
    D->enqueue(3);

    bool flag = false;
    isPalindrome(D, flag);

    if (flag)
        cout << "D is palindrome\n";
    else
        cout << "D is not palindrome\n";

    sort(A);
    cout << "after sort: ";
    display(A, cout);

    return 0;
}

// print queue without changing it
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

// copy one queue to another
void append(Queue* src, Queue* dst)
{
    int n = getSize(src);

    for (int i = 0; i < n; i++)
    {
        int v = src->dequeue();
        src->enqueue(v);

        if (!dst->isFull())
            dst->enqueue(v);
    }
}

// copy limited values
void append(Queue* src, Queue* dst, int no)
{
    int n = getSize(src);

    if (no > n)
        no = n;

    for (int i = 0; i < n; i++)
    {
        int v = src->dequeue();
        src->enqueue(v);

        if (i < no && !dst->isFull())
            dst->enqueue(v);
    }
}

// reverse using stack
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
        int v;
        if (s->pop(v))
            dst->enqueue(v);
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
        q->enqueue(temp->dequeue());

    delete temp;
    return count;
}

// remove element from position
int get(Queue* q, int pos)
{
    int n = getSize(q);
    Queue* temp = new MyQueue(MAX_SIZE);

    int val = 0;

    for (int i = 0; i < n; i++)
    {
        int v = q->dequeue();

        if (i == pos)
            val = v;
        else
            temp->enqueue(v);
    }

    while (!temp->isEmpty())
        q->enqueue(temp->dequeue());

    delete temp;
    return val;
}

// simple selection sort using queue
void sort(Queue* q)
{
    int n = getSize(q);
    Queue* sorted = new MyQueue(MAX_SIZE);

    for (int i = 0; i < n; i++)
    {
        int min = q->dequeue();
        q->enqueue(min);

        for (int j = 1; j < n; j++)
        {
            int v = q->dequeue();
            q->enqueue(v);

            if (v < min)
                min = v;
        }

        bool removed = false;

        for (int j = 0; j < n; j++)
        {
            int v = q->dequeue();

            if (v == min && !removed)
                removed = true;
            else
                q->enqueue(v);
        }

        sorted->enqueue(min);
    }

    while (!sorted->isEmpty())
        q->enqueue(sorted->dequeue());

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
        int b;
        s->pop(b);

        if (a != b)
            ok = false;
    }

    delete temp;
    delete s;
    return ok;
}

// palindrome without extra adt (single digits)
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
        reverse += v * place;
        place *= 10;
    }

    flag = (forward == reverse);
}

// rotate left
void rotateLeft(Queue* q, int pos)
{
    int n = getSize(q);
    Queue* temp = new MyQueue(MAX_SIZE);

    for (int i = 0; i < pos; i++)
        temp->enqueue(q->dequeue());

    int first = q->dequeue();

    while (!q->isEmpty())
        temp->enqueue(q->dequeue());

    temp->enqueue(first);

    while (!temp->isEmpty())
        q->enqueue(temp->dequeue());

    delete temp;
}

// rotate right
void rotateRight(Queue* q, int pos)
{
    int n = getSize(q);

    Queue* left = new MyQueue(MAX_SIZE);
    Queue* right = new MyQueue(MAX_SIZE);

    for (int i = 0; i < pos; i++)
        left->enqueue(q->dequeue());

    while (!q->isEmpty())
        right->enqueue(q->dequeue());

    int size = getSize(right);

    for (int i = 0; i < size - 1; i++)
        right->enqueue(right->dequeue());

    while (!left->isEmpty())
        q->enqueue(left->dequeue());

    while (!right->isEmpty())
        q->enqueue(right->dequeue());

    delete left;
    delete right;
}