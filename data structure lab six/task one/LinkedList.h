#include<iostream>
using namespace std;
class LinkedList
{
protected:
    Node*first;
    Node*last;
public:
  LinkedList()
  {
      first = nullptr; last = nullptr;
  };
  //THE PROVIDED COPY CONSTRUCTOR WOULD ONLY DELETE TWO NODES MAX AND HAS A POTENTIONAL MEMORY LEAKAGE RISK 
  //SO, WE FIX THE COPY CONSTRUCTOR LIKE THIS TO NEATLY DELETE THE WHOLE LINKED LIST WITHOUT MEMORY LEAKAGE 
  LinkedList::~LinkedList()
  {
      Node* temp = first; //TEMPORARY NODE TO STORE DATA TO 
      while (temp != nullptr)
      {
          Node* nextNode = temp->next;
          delete temp;
          temp = nextNode;
      }
      first = nullptr;
      last = nullptr;
  }
  virtual ~LinkedList();
    virtual void insertAtLast(int) = 0;
    virtual void insertAtFirst(int) = 0;
    virtual int removeFromFirst() = 0;
    virtual int removeFromLast() = 0;
    virtual bool isEmpty() = 0;
    virtual void display() = 0;
};


