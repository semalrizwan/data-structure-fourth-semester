#include <iostream>
using namespace std;

/* * MANDATORY TASK ANALYSIS:
 * 1. Understanding: I need to write functions that work directly with Node pointers instead of a class.
 * This involves creating a mirror copy of a list and a way to wipe the memory clean when done.
 * 2. Approach: For 'copy', I will create a new node for every node in the original list and link
 * them one by one. For 'freeMemory', I will loop through and delete each node to prevent memory leaks.
 * 3. Reused Functions: I am using basic pointer traversal and the Node structure.
 * 4. Learning: I learned how to manage memory manually and how to create deep copies of linked structures.
 */

struct Node {
    int data;
    Node* next;
};

// Function to copy a linked list
Node* copy(Node* head) {
    if (head == nullptr) return nullptr;

    Node* newNode = new Node;
    newNode->data = head->data;
    newNode->next = copy(head->next); // Recursive deep copy
    return newNode;
}

// Function to delete all nodes and free memory
void freeMemory(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void display(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = new Node{ 10, new Node{20, new Node{30, nullptr}} };

    cout << "Original List: ";
    display(head);

    Node* clonedList = copy(head);
    cout << "Cloned List: ";
    display(clonedList);

    freeMemory(head);
    freeMemory(clonedList);
    return 0;
}