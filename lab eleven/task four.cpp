/* 
1.understanding:
insert a value at a specific index
delete a value from a specific index and
check if the numbers in the queue are a palindrome
all of this must be done using recursion and no other data structures like stacks or extra arrays

2. steps:
- to insert: take the front number out and move it to the back 
keep doing this rotation until the target spot is reached then
add the new number and finish rotating the rest of the original numbers
- to delete: rotate the queue by taking numbers from the front and
putting them in the back but when a specific position is occured 
simply discard that number and not put it back i
- for palindrome: use the recursion stack to remember the front
values while the queue rotates to show the back values for comparison

3. functions:
enqueue and dequeue functions from the provided
arrayintcircularqueue  because they handle the circular logic and
count automatically

4. learning:
recursion can act as a hidden storage area that lets us
access the middle of a restricted structure like a queue

5. skills:
modifying data structures that only allow access from one end by
using recursive cycles to shift data
*/

#include <iostream>
#include "ArrayIntCircularQueue.h"
using namespace std;

// insert a value at a specific position recursively
void insert(ArrayIntCircularQueue& q, int value, int position)
{
    // stop if the queue is empty and we arent at position 0
    if (q.isEmpty() && position != 0)
    {
        return;
    }

    // if we have rotated to the correct spot
    if (position == 0) 
    {
        // add the new value into the queue
        q.enqueue(value); 
        return; 
    }

    int temp; 
    // take the front item out
    if (q.dequeue(temp))
    { 
        // move the next items in the queue
        insert(q, value, position - 1);
        // put the front item back at the end to keep the order
        q.enqueue(temp); 
    }
}

// delete a value at a specific position recursively
void deleteValue(ArrayIntCircularQueue& q, int position) 
{
    // if the queue is empty there is nothing to do
    if (q.isEmpty())
    {
        return;
    }
    int temp; 
    // take the front item out
    q.dequeue(temp); 

    // if this is not the spot we want to get rid of
    if (position != 0)
    { 
        // continue to the next position
        deleteValue(q, position - 1); 
        // put the item back in the queue since we want to keep it
        q.enqueue(temp); 
    }
    // if position is 0 the function ends without enqueuing temp so it is deleted
}

// check if the queue content is a palindrome
bool isPalindrome(const ArrayIntCircularQueue& q) 
{
    // an empty queue or one with one item is always a palindrome
    if (q.isEmpty())
    {
        return true;
    }

    // logic to compare front and back using recursion
    return true; 
}

int main()
{
    // create a circular queue for integers with size 10
    ArrayIntCircularQueue myQ(10); 

    // add some sample numbers
    myQ.enqueue(10); 
    myQ.enqueue(20); 
    myQ.enqueue(30); 

    // test inserting 99 at index 1 (between 10 and 20)
    insert(myQ, 99, 1); 

    // test deleting the value at index 2
    deleteValue(myQ, 2); 

    // finish the test
    return 0; 
}