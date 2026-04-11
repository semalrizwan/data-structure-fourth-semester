#include <iostream>
using namespace std;

/* * MANDATORY TASK ANALYSIS:
 * 1. Understanding: I need to be able to rearrange the list. This means swapping two numbers
 * at different positions and sorting the entire list in order (ascending or descending).
 * 2. Approach: For swapping, I locate the two nodes by index and swap their values.
 * For sorting, I used a bubble sort style approach where I compare every pair and swap if they are out of order.
 * 3. Reused Functions: display and insertAtLast.
 * 4. Learning: I learned how sorting algorithms apply to linked lists and that swapping data is easier than swapping pointers.
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

    void insertAtLast(int v) {
        Node* nn = new Node{ v, nullptr };
        if (!first) first = last = nn;
        else { last->next = nn; last = nn; }
    }

    void swap(int xi, int yi) {
        if (xi == yi) return;
        Node* nodeX = nullptr, * nodeY = nullptr, * t = first;
        for (int i = 0; t; i++) {
            if (i == xi) nodeX = t;
            if (i == yi) nodeY = t;
            t = t->next;
        }
        if (nodeX && nodeY) {
            int temp = nodeX->data;
            nodeX->data = nodeY->data;
            nodeY->data = temp;
        }
    }

    void sort(bool asc) {
        if (!first) return;
        bool swapped;
        do {
            swapped = false;
            for (Node* t = first; t && t->next; t = t->next) {
                if (asc ? (t->data > t->next->data) : (t->data < t->next->data)) {
                    int temp = t->data;
                    t->data = t->next->data;
                    t->next->data = temp;
                    swapped = true;
                }
            }
        } while (swapped);
    }

    void display() {
        for (Node* t = first; t; t = t->next) cout << t->data << " -> ";
        cout << "NULL" << endl;
    }
};

int main() {
    myLinkedList list;
    list.insertAtLast(40);
    list.insertAtLast(10);
    list.insertAtLast(30);
    cout << "Original: "; list.display();
    list.sort(true);
    cout << "Sorted Asc: "; list.display();
    return 0;
}