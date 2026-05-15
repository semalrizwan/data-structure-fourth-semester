/* 
1. understanding:
 recursive functions for a doubly linked lis 
 this list has nodes that point both forward and backward a new number should be placed at
any spot take a number out from any spot and check if the list reads the
same way from the start and the end

2. steps:
- to insert: move through the nodes one by one when the position
count reaches zero create a new node and link its front and back
pointers to the existing neighbors
- to delete: travel to the correct node then tell the node before
it and the node after it to point to each other skipping the current one
- for palindrome: use recursive to compare the data at
the beginning with the data at the end and move inward

3. functions:
use the next and previous pointers inside the node class to move
through the list recursion replaces the need for any while or for loops

4. learning:
 doubly linked lists are safer for recursion because you can
easily verify the connection from both directions

5. skills:
handle complex memory addresses and link them together in a
chain without losing any data
*/

#include <iostream>
using namespace std;

// structure for a doubly linked list node
template <class T>
class Node {
public:
    T data; // holds the value
    Node* next; // points to the next node
    Node* prev; // points to the previous node

    Node(T val) : data(val), next(nullptr), prev(nullptr)
    {
        //constructor
    }
};

// class to manage the doubly linked list
template <class T>
class DoublyLinkedList 
{
public:
    Node<T>* head; // start of the list
    DoublyLinkedList() : head(nullptr) //head is set at nullptr
    {

    } 

    // recursive helper to find the spot and insert
    void insertRecursive(Node<T>*& curr, Node<T>* previous, T value, int position)
    {
        // if we found the spot or reached the end
        if (position == 0 || curr == nullptr) 
        { 
            Node<T>* newNode = new Node<T>(value); // make the new node
            newNode->next = curr; // point new node to current
            newNode->prev = previous; // point new node back to previous
            if (curr != nullptr)
            {
                curr->prev = newNode; // update current's back pointer
                curr = newNode; // update the link from the parent node
                return; // 
            }
        }
        // move to the next node and decrease position
        insertRecursive(curr->next, curr, value, position - 1); //recurrsion
    }

    // recursive helper to find the spot and delete
    void deleteRecursive(Node<T>*& curr, int position) 
    {
        // stop if list is empty or index is out of bounds
        if (curr == nullptr) return; 

        // if we found the node to delete
        if (position == 0) 
        {
            Node<T>* temp = curr; // save the node to delete
            curr = curr->next; // skip the node
            if (curr != nullptr)
            {
                curr->prev = temp->prev; // update back pointer
                delete temp; // free the memory
                return; // stop
            }
        }
        // move to the next node
        deleteRecursive(curr->next, position - 1); 
    }
};

// insert value at specific position
void insert(DoublyLinkedList<int>& list, int value, int position) 
{
    // start the recursive process from the head
    list.insertRecursive(list.head, nullptr, value, position); 
}

// delete value at specific position 
void deleteValue(DoublyLinkedList<int>& list, int position)
{
    // start the recursive deletion from the head
    list.deleteRecursive(list.head, position); 
}

// recursive helper to compare start and end values
bool checkPalindrome(Node<int>* left, Node<int>*& right) 
{
    // if we hit the end of the list
    if (left == nullptr)
    {
        return true;
    }

    // go all the way to the end first
    bool isMatch = checkPalindrome(left->next, right); 
    if (!isMatch)
    {
        return false; // if a mismatch was found deeper, stop
    }

    // compare left data (from start) with right data (from end)
    bool currentMatch = (left->data == right->data); 
    // move the right pointer one step back towards the start
    right = right->next; 
    return currentMatch; // return result
}

// check if list is a palindrome 
bool isPalindrome(const DoublyLinkedList<int>& list) 
{
    // if list is empty, it counts as a palindrome
    if (list.head == nullptr) return true; 
    Node<int>* rightTracker = list.head; // start a tracker at the head
    return checkPalindrome(list.head, rightTracker); 
}

int main()
{
    // create the list object
    DoublyLinkedList<int> myList;

    // test putting values in
    insert(myList, 1, 0); // list: 1
    insert(myList, 2, 1); // list: 1, 2
    insert(myList, 1, 2); // list: 1, 2, 1

    // test the palindrome check
    if (isPalindrome(myList))
    {
        cout << "the list is a palindrome" << endl;
    }

    // test removing a value
    deleteValue(myList, 1);

    return 0;
}
