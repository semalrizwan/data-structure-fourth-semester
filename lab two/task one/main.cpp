#include<iostream>
#include"MyArray.h"
using namespace std;

const int MAX_SIZE = 10;

int main()
{
    MyArray A(MAX_SIZE);
    int n = 0;

    cout << "Please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;

    // reads n numbers into array A
    read(A, cin, n);
    cout << "Array A Values: ";
    display(A, cout);

    // copies A into B
    MyArray B(MAX_SIZE);
    copy(A, B);
    cout << "Array B Values: ";
    display(B, cout);

    // create C with 3 initial values
    MyArray C(MAX_SIZE);
    C.add(9);
    C.add(7);
    C.add(5);

    // insert values of A into C starting from position 2
    insert(A, C, 2);
    cout << "Array C Values: ";
    display(C, cout);

    // shift left from position 2
    shiftLeft(C, 2);
    cout << "Array C Values: ";
    display(C, cout);

    // shift right from position 2
    shiftRight(C, 2);
    cout << "Array C Values: ";
    display(C, cout);

    int mx = 0;
    float ag = 0.0;

    // find maximum and average of C
    stats(C, mx, ag);
    cout << "Array C Values: ";
    display(C, cout);
    cout << "Average is " << ag << " maximum is " << mx << endl;

    return 0;
}