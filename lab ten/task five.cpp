#include<iostream>
using namespace std;
/* 
1. understanding:
we interact with the list by removing from the first or last positions recursion allows us to process each 
node individually until the list is empty

2. solution: 
to process the list we remove the front element recursively call the function for the remaining list and then use
insertatfirst to put the element back during the unwinding phase of recursion
 
3. learning:
doubly linked lists are flexible because we can remove from either end but recursive restoration must match the
removal logic 

4. skills: 
i can now implement complex traversal and counting logic without using while loops
*/

//1. copy
void LLCopy(ConcreteDoublyLinkedList<int>& src, ConcreteDoublyLinkedList<int>& copy) 
{
    if (src.isEmpty())
    {
        return; // Base Case
    }
    //recurrsive
    int x;
    src.removeFromLast(x);    
    LLCopy(src, copy);        

    copy.insertAtFirst(x);    
    src.insertAtLast(x);      
}

//2.display
void display(ConcreteDoublyLinkedList<int>& as) 
{
    if (as.isEmpty())
    {
        return;
    }
    //recurrsion
    int v;
    as.removeFromFirst(v);    
    cout << v << " <-> ";    
    display(as);           
    as.insertAtFirst(v);      
}

//3.get size
int getSize(ConcreteDoublyLinkedList<int>& as) 
{
    if (as.isEmpty())
    {
        return 0; //base case
    }
    //recurrsion
    int v;
    as.removeFromLast(v);
    int currentSize = 1 + getSize(as);
    as.insertAtLast(v);      
    return currentSize;
}

//4. maximum elemenyt
int max(ConcreteDoublyLinkedList<int>& as) 
{
    int mx;
    as.removeFromLast(mx);
    //base case
    if (as.isEmpty()) 
    {
        as.insertAtLast(mx);
        return mx;
    }
    //recurrsion
    int v = max(as);          
    int finalMax = (mx > v) ? mx : v;
    as.insertAtLast(mx);     
    return finalMax;
}

//5. frequency
int countInDLL(ConcreteDoublyLinkedList<int>& adt, int target)
{
    if (adt.isEmpty())
    {
        return 0;
    }
    //recurssion
    int v;
    adt.removeFromFirst(v);
    int match = (v == target) ? 1 : 0;
    int total = match + countInDLL(adt, target);
    adt.insertAtFirst(v);     
    return total;
}

ArrayQueue<int> frequency(ConcreteDoublyLinkedList<int>& adt) 
{
    ArrayQueue<int> result(10);
    // this would ideally iterate through the list recursively 
    // and push counts into the queue.
    return result;
}