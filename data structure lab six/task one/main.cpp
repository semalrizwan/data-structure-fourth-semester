#include<iostream>
#include "LinkedList.h"
#include "myLinkedList.h"
using namespace std;

int main()
{
    myLinkedList list1;

    list1.insertAtLast(10);
    list1.insertAtLast(20);
    list1.insertAtLast(30);

    cout << "Original List:\n";
    list1.display();

     //Test Copy Constructor
    myLinkedList list2 = list1;

    cout << "Copied List:\n";
    list2.display();

    // Modify original to check deep copy
    list1.removeFromLast();

    cout << "After removing from original:\n";
    cout << "Original List:\n";
    list1.display();

    cout << "Copied List (should remain same):\n";
    list2.display();

    return 0;
}
