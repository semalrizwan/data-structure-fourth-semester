#include<iostream>
#include"myLinkedList.h"
using namespace std;
int main() 
{
    myLinkedList list;
    // Insert elements
    list.insertAtLast(10);
    list.insertAtLast(20);
    list.insertAtLast(30);
    list.insertAtLast(40);

    cout << "Linked List: ";
    list.display();

    // getSize
    cout << "\nSize: " << list.getSize();

    // search
    cout << "\nSearch 20: " << (list.search(20) ? "Found" : "Not Found");
    cout << "\nSearch 99: " << (list.search(99) ? "Found" : "Not Found");

    // peek
    cout << "\nPeek at position 2: " << list.peek(2);

    // get (remove)
    cout << "\nRemoved at position 1: " << list.get(1);

    cout << "\nUpdated List: ";
    list.display();

    return 0;
}