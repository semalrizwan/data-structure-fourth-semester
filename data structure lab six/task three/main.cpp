#include<iostream>
#include"myLinkedList.h"
using namespace std;
int main() {
    myLinkedList list;

    // Initial data
    list.insertAtLast(30);
    list.insertAtLast(10);
    list.insertAtLast(50);
    list.insertAtLast(20);

    cout << "Original List:\n";
    list.display();

    // put
    cout << "\nInsert 99 at position 2:\n";
    list.put(99, 2);
    list.display();

    // swap
    cout << "\nSwap positions 1 and 3:\n";
    list.swap(1, 3);
    list.display();

    // sort ascending
    cout << "\nSort Ascending:\n";
    list.sort(true);
    list.display();

    // sort descending
    cout << "\nSort Descending:\n";
    list.sort(false);
    list.display();

    return 0;
}