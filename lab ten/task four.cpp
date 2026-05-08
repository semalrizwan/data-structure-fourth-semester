#include<iostream>
using namespace std;
/* 
1. UNDERSTANDING:
unlike a stack a queue is FIFO to process it recursively while keeping the original, dequeue elements
recurse and then enqueue them back to the end of the queue

2. SOLUTION:
we remove the front element solve the problem for the remaining queue and then restore the element by putting 
it back in the queue
 
3. LEARNING:  
queues are circular or linear recursion must be careful to handle so data doesnt get lost

4. SKILLS:
FIFO iterative logic into recursive logic
*/

//1. copy qeueu
void copyQueue(MyQueue& src, MyQueue& copy) 
{
    if (src.isEmpty())
    {
        return; // Base Case
    }
    //recurrsion
    int v = src.dequeue();     
    copyQueue(src, copy);     
    copy.enqueue(v);         
    src.enqueue(v);           
}

//2. display
void display(MyQueue& mq) 
{
    if (mq.isEmpty())
    {
        return; //baase case
    }
    //recurrsion
    int v = mq.dequeue();
    cout << v << " ";         
    display(mq);              
    mq.enqueue(v);           
}

//3. maximum element
int max(MyQueue& mq) 
{
    int v = mq.dequeue();
    //base case
    if (mq.isEmpty()) 
    {
        mq.enqueue(v);        
        return v;
    }
    //recurssion
    int currentMax = max(mq); 
    int finalMax = (v > currentMax) ? v : currentMax;
    mq.enqueue(v);            
    return finalMax;
}

//4. frequency
int countFrequency(MyQueue& mq, int target, int remaining) 
{
    if (remaining == 0)
    {
        return 0; //base case
    }
    //recurrsion
    int v = mq.dequeue();
    mq.enqueue(v); 
    int match = (v == target) ? 1 : 0;
    return match + countFrequency(mq, target, remaining - 1);
}

// main frequency
MyQueue frequency(MyQueue& adt) 
{
    MyQueue result(adt.getSize()); // resulting queue to store frequencies
    return result;
}