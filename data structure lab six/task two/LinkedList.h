#include<iostream>
#include"node.h"
using namespace std;
class LinkedList //abstract class
{
protected:
    Node* first;
    Node* last;
public:
    //default constructor
    LinkedList() 
    {
        first = nullptr; 
        last = nullptr; 

    };
    //destrcutor
    ~LinkedList()
    {
        //making a temportary node to store the data because if we do not makea temp node it won't be a proper destructor
        Node* temp = first;
        while (temp != nullptr)
        {
            Node* nextnode = temp->next;
            delete temp;
            temp = nextnode;
        }
        first = nullptr;
        last = nullptr;
    }
    virtual void insertAtLast(int) = 0;
    virtual void insertAtFirst(int) = 0;
    virtual int removeFromFirst() = 0;
    virtual int removeFromLast() = 0;
    virtual bool isEmpty() = 0;
    virtual void display() = 0;
};


