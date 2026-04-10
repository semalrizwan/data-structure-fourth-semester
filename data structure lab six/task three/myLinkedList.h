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
    //task three function
    void put(int v, int pos);
    void swap(int xi, int yi);
    void sort(bool asc);
};
bool myLinkedList::isEmpty() 
{
    return first == nullptr && last == nullptr;
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
    while (t->next != last) {
        t = t->next;
    }

    int val = last->data;
    delete last;
    last = t;
    last->next = nullptr;

    return val;
}
int myLinkedList::getSize() {
    int count = 0;
    Node* t = first;
    while (t != nullptr) {
        count++;
        t = t->next;
    }
    return count;
}

int myLinkedList::peek(int pos) {
    Node* t = first;
    int index = 0;

    while (t != nullptr) {
        if (index == pos)
            return t->data;
        t = t->next;
        index++;
    }
    return -99999;
}
// 1. put(v, pos)
void myLinkedList::put(int v, int pos) {
    if (pos < 0 || pos > getSize()) {
        cout << "Invalid position\n";
        return;
    }

    if (pos == 0) {
        insertAtFirst(v);
        return;
    }

    if (pos == getSize()) {
        insertAtLast(v);
        return;
    }

    Node* nn = new Node;
    nn->data = v;

    Node* t = first;
    for (int i = 0; i < pos - 1; i++) {
        t = t->next;
    }

    nn->next = t->next;
    t->next = nn;
}

// 2. swap(xi, yi)
void myLinkedList::swap(int xi, int yi) {
    if (xi == yi) return;

    int size = getSize();
    if (xi < 0 || yi < 0 || xi >= size || yi >= size) {
        cout << "Invalid positions\n";
        return;
    }

    int val1 = peek(xi);
    int val2 = peek(yi);

    Node* t = first;
    int index = 0;

    while (t != nullptr) {
        if (index == xi)
            t->data = val2;
        else if (index == yi)
            t->data = val1;

        t = t->next;
        index++;
    }
}

// 3. sort(asc)
void myLinkedList::sort(bool asc) {
    if (isEmpty()) return;

    for (Node* i = first; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {

            if (asc) {
                if (i->data > j->data) {
                    int temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
            else {
                if (i->data < j->data) {
                    int temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }
}