#include <iostream>
using namespace std;

/* * MANDATORY TASK ANALYSIS:
 * 1. Understanding: The task is to add specific tools to our linked list like finding its length,
 * searching for a number, or removing a number from a specific middle spot.
 * 2. Approach: I use a counter for size, a comparison loop for search, and pointer manipulation
 * (tracking current and previous nodes) to remove an item from the middle of the list.
 * 3. Reused Functions: insertAtLast and display from previous labs.
 * 4. Learning: I learned how to traverse a list using indices and how to safely unhook a node from the chain.
 */

struct Node {
    int data;
    Node* next;
};

class myLinkedList {
    Node* first;
    Node* last;
public:
    myLinkedList() { first = last = nullptr; }

    void insertAtLast(int value) {
        Node* nn = new Node{ value, nullptr };
        if (!first) first = last = nn;
        else { last->next = nn; last = nn; }
    }

    int getSize() {
        int count = 0;
        for (Node* t = first; t; t = t->next) count++;
        return count;
    }

    bool search(int v) {
        for (Node* t = first; t; t = t->next) if (t->data == v) return true;
        return false;
    }

    int peek(int pos) {
        Node* t = first;
        for (int i = 0; t && i < pos; i++) t = t->next;
        return t ? t->data : -99999;
    }

    int get(int pos) {
        if (!first || pos < 0) return -99999;
        if (pos == 0) {
            Node* t = first;
            int val = t->data;
            first = first->next;
            if (!first) last = nullptr;
            delete t;
            return val;
        }
        Node* curr = first;
        Node* prev = nullptr;
        for (int i = 0; curr && i < pos; i++) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return -99999;
        int val = curr->data;
        prev->next = curr->next;
        if (curr == last) last = prev;
        delete curr;
        return val;
    }

    void display() {
        for (Node* t = first; t; t = t->next) cout << t->data << " -> ";
        cout << "NULL" << endl;
    }
};

int main() {
    myLinkedList list;
    list.insertAtLast(10);
    list.insertAtLast(20);
    list.insertAtLast(30);
    cout << "Size: " << list.getSize() << endl;
    cout << "Get pos 1: " << list.get(1) << endl;
    list.display();
    return 0;
}