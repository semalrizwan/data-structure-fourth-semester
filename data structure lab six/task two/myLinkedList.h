#include <iostream>
#include"LinkedList.h"
#include"Node.h"
using namespace std;
class myLinkedList : public LinkedList
{
public:
    void insertAtLast(int value);
    void insertAtFirst(int value);
    void display();
    int removeFromFirst();
    int removeFromLast();
    bool isEmpty();

    //task two functions
    int getSize();
    bool search(int v);
    int peek(int pos);
    int get(int pos);
};
bool myLinkedList::isEmpty() 
{
    return first == nullptr && last == nullptr;
}

void myLinkedList::insertAtFirst(int value) 
{
    Node* nn = new Node;
    nn->data = value;
    nn->next = nullptr;

    if (isEmpty()) {
        first = last = nn;
    }
    else {
        nn->next = first;
        first = nn;
    }
}
void myLinkedList::insertAtLast(int value)
{
    Node* nn = new Node;
    nn->data = value;
    nn->next = nullptr;

    if (isEmpty()) {
        first = last = nn;
    }
    else {
        last->next = nn;
        last = nn;
    }
}

void myLinkedList::display() 
{
    Node* t = first;
    while (t != nullptr) {
        cout << t->data << " -> ";
        t = t->next;
    }
    cout << "NULL\n";
}

int myLinkedList::removeFromFirst() 
{
    if (isEmpty()) return -99999;

    Node* t = first;
    int val = t->data;

    first = first->next;
    if (first == nullptr) last = nullptr;

    delete t;
    return val;
}

int myLinkedList::removeFromLast()
{
    if (isEmpty()) return -99999;

    if (first == last) {
        int val = first->data;
        delete first;
        first = last = nullptr;
        return val;
    }

    Node* t = first;
    while (t->next != last)
    {
        t = t->next;
    }

    int val = last->data;
    delete last;
    last = t;
    last->next = nullptr;

    return val;
}
// 1. getSize()
int myLinkedList::getSize() 
{
    int count = 0;
    Node* t = first; //first node data is stored into t

    while (t != nullptr) 
    {
        count++;
        t = t->next; //the loop continues as long as there is no empty node and count increases that tell sus the total number of varaibes present 
    }
    return count;
}
// 2. search()
bool myLinkedList::search(int v) 
{
    Node* t = first; //firt node is stored into t

    while (t != nullptr) 
    {
        //if the value of out data is equal to the specific value entered then it'll return trye otherwise it moves to the nexr node
        if (t->data == v)
            return true;
        t = t->next;
    }
    return false; //the loop continyes until false and if there is none then it'll return false
}
// 3. peek()
int myLinkedList::peek(int pos) 
{
    if (pos < 0) return -99999;//if the control is not pointing to any node at the moment then itll resturn garbage value

    Node* t = first;
    int index = 0;

    while (t != nullptr) 
    {
        if (index == pos)
            return t->data;

        t = t->next;
        index++;
    }

    return -99999; // invalid position
}

// 4. get() (remove + return)
int myLinkedList::get(int pos) 
{
    if (pos < 0 || isEmpty())
        return -99999;

    // remove first
    if (pos == 0) 
    {
        return removeFromFirst();
    }

    Node* prev = first;
    Node* curr = first->next;
    int index = 1;

    while (curr != nullptr) 
    {
        if (index == pos) 
        {
            int val = curr->data;

            prev->next = curr->next;

            if (curr == last)
                last = prev;

            delete curr;
            return val;
        }

        prev = curr;
        curr = curr->next;
        index++;
    }

    return -99999; // invalid position
}

