#include<iostream>
#include"MyStack.h"
using namespace std;
const int MAX_SIZE = 10;
int main()
{
    MyStack A(MAX_SIZE);
    int n = 0;

    cout << "Please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;

    // read numbers into stack A
    read(A, cin, n);

    cout << "Stack A Values: ";
    display(A, cout);

    // copy stack A into B
    MyStack B(MAX_SIZE);
    copy(A, B);

    cout << "Stack B Values: ";
    display(B, cout);

    // create stack C with initial values
    MyStack C(MAX_SIZE);
    C.push(9);
    C.push(7);
    C.push(5);

    // insert stack A into C at position 2
    insert(A, C, 2);

    cout << "Stack C Values: ";
    display(C, cout);

    // shift stack values upward
    shiftUp(C, 2);

    cout << "Stack C Values: ";
    display(C, cout);

    // shift stack values downward
    shiftDown(C, 2);

    cout << "Stack C Values: ";
    display(C, cout);

    int mx = 0;
    float ag = 0.0;

    // calculate maximum and average
    stats(C, mx, ag);

    cout << "Stack C Values: ";
    display(C, cout);

    cout << "Average is " << ag << " maximum is " << mx << endl;

    return 0;
}