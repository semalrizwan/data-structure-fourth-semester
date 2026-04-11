#include <iostream>
using namespace std;

/* * MANDATORY TASK ANALYSIS:
 * 1. Understanding: This task involves working with a list that only tracks the 'first' node.
 * Since there is no 'last' pointer, any operation at the end of the list requires walking through
 * every single node until the end is found.
 * 2. Approach: To insert or remove from the last position, I use a while loop to find the node
 * where 'next' is null. For sorting, I compare data values and swap them to avoid complex pointer
 * re-linking.
 * 3. Reused Functions: I am using the standard Node structure and basic traversal logic.
 * 4. Learning: I learned that while a single-pointer list saves memory, it makes operations
 * at the tail much slower compared to a list with a 'last' pointer.
 */

struct Node {
    int data;
    Node* next;
};

class FirstOnlyLinkedList {
protected:
    Node* first;
public:
    FirstOnlyLinkedList() { first = nullptr; }
};

class myFirstOnlyLinkedList : public FirstOnlyLinkedList {
public:
    void insertAtFirst(int value) {
        Node* nn = new Node{ value, first };
        first = nn;
    }

    void insertAtLast(int value) {
        Node* nn = new Node{ value, nullptr };
        if (!first) {
            first = nn;
            return;
        }
        Node* t = first;
        while (t->next != nullptr) t = t->next;
        t->next = nn;
    }

    void display() {
        Node* t = first;
        while (t) {
            cout << t->data << " -> ";
            t = t->next;
        }
        cout << "NULL" << endl;
    }

    void sort(bool asc) {
        if (!first) return;
        bool swapped;
        do {
            swapped = false;
            Node* t = first;
            while (t->next != nullptr) {
                if (asc ? (t->data > t->next->data) : (t->data < t->next->data)) {
                    int temp = t->data;
                    t->data = t->next->data;
                    t->next->data = temp;
                    swapped = true;
                }
                t = t->next;
            }
        } while (swapped);
    }
};

int main() {
    myFirstOnlyLinkedList list;
    list.insertAtLast(50);
    list.insertAtFirst(20);
    list.insertAtLast(10);
    cout << "Unsorted: "; list.display();
    list.sort(true);
    cout << "Sorted: "; list.display();
    return 0;
}