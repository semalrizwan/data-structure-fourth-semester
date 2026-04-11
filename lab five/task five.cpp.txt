#include <iostream>
using namespace std;

/* * MANDATORY TASK ANALYSIS:
 * 1. Understanding: I need to create a list that stays sorted automatically. Instead of just
 * adding items to the front or back, the list must search for the correct numerical spot
 * for every new piece of data.
 * 2. Approach: When 'insertSorted' is called, I check if the new value is smaller than the
 * current 'first' node. If not, I traverse the list until I find a node whose 'next' value
 * is larger than my new value, then I link the new node in that gap.
 * 3. Reused Functions: display and isEmpty logic.
 * 4. Learning: I learned how to implement an "Ordered List," which is more efficient for
 * searching and reporting data in a specific sequence.
 */

struct Node {
    int data;
    Node* next;
};

class SortedFirstOnlyLinkedList {
protected:
    Node* first;
    bool ascending;
public:
    SortedFirstOnlyLinkedList(bool asc = true) {
        first = nullptr;
        ascending = asc;
    }

    bool isEmpty() { return first == nullptr; }

    void insertSorted(int value) {
        Node* nn = new Node{ value, nullptr };

        // Case 1: List is empty or value belongs at the very start
        if (isEmpty() || (ascending ? value < first->data : value > first->data)) {
            nn->next = first;
            first = nn;
            return;
        }

        // Case 2: Find the correct position in the middle or end
        Node* t = first;
        while (t->next != nullptr && (ascending ? t->next->data < value : t->next->data > value)) {
            t = t->next;
        }
        nn->next = t->next;
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
};

int main() {
    SortedFirstOnlyLinkedList list(true); // Ascending
    list.insertSorted(30);
    list.insertSorted(10);
    list.insertSorted(20);
    list.insertSorted(40);

    cout << "Automatically Sorted List: ";
    list.display();

    return 0;
}