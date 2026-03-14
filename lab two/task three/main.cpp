#include<iostream>
#include"MyStack.h"     // FIX FROM LAB TEXT: it says include Stack.h and Stack.h
// but actual required files are Stack.h and MyStack.h
using namespace std;

const int SIZE = 10;

// checks whether a number is prime or not
bool isPrime(int n)
{
    // prime numbers are greater than 1
    if (n <= 1)
        return false;

    // check divisibility from 2 to n-1
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

// checks whether a number is a perfect square or not
bool isPerfectSquare(int n)
{
    if (n < 0)
        return false;

    for (int i = 0; i * i <= n; i++)
    {
        if (i * i == n)
            return true;
    }

    return false;
}

// checks whether a single number is palindrome or not
// example: 121 yes, 343 yes, 123 no
bool isPalindromeValue(int n)
{
    if (n < 0)
        return false;

    int original = n;
    int reverse = 0;
    int digit = 0;

    while (n > 0)
    {
        digit = n % 10;
        reverse = reverse * 10 + digit;
        n = n / 10;
    }

    return original == reverse;
}

// displays prime result for each stack value
// stack is restored after checking
void checkPrime(MyStack& S)
{
    MyStack temp(S.size());
    int x;

    cout << "Prime Check:" << endl;

    // first reverse the stack into temp
    while (S.pop(x))
        temp.push(x);

    // now temp will give values in original order
    while (temp.pop(x))
    {
        cout << x << " -> ";

        if (isPrime(x))
            cout << "Prime";
        else
            cout << "Not Prime";

        cout << endl;

        // restore original stack
        S.push(x);
    }
}

// displays perfect square result for each stack value
// stack is restored after checking
void checkPerfectSquare(MyStack& S)
{
    MyStack temp(S.size());
    int x;

    cout << "Perfect Square Check:" << endl;

    while (S.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        cout << x << " -> ";

        if (isPerfectSquare(x))
            cout << "Perfect Square";
        else
            cout << "Not Perfect Square";

        cout << endl;

        S.push(x);
    }
}

// displays palindrome result for each single value
// stack is restored after checking
void checkPalindromeValues(MyStack& S)
{
    MyStack temp(S.size());
    int x;

    cout << "Palindrome Value Check:" << endl;

    while (S.pop(x))
        temp.push(x);

    while (temp.pop(x))
    {
        cout << x << " -> ";

        if (isPalindromeValue(x))
            cout << "Palindrome";
        else
            cout << "Not Palindrome";

        cout << endl;

        S.push(x);
    }
}

// checks whether complete stack values form a palindrome sequence
// example: 123 456 539 456 123 -> palindrome sequence
bool isStackPalindrome(MyStack& S)
{
    MyStack temp(S.size());
    MyStack originalCopy(S.size());
    MyStack reverseCopy(S.size());

    int x;
    int a, b;

    // move original stack to temp
    // while doing this, also store reverse order copy
    while (S.pop(x))
    {
        temp.push(x);
        reverseCopy.push(x);
    }

    // restore original stack and create original order copy
    while (temp.pop(x))
    {
        S.push(x);
        originalCopy.push(x);
    }

    // compare both stacks
    // if all corresponding values are equal, sequence is palindrome
    while (originalCopy.pop(a) && reverseCopy.pop(b))
    {
        if (a != b)
            return false;
    }

    return true;
}

//main function
int main()
{
    MyStack S(SIZE);

    cout << "Enter " << SIZE << " integers:" << endl;

    // reused read() function style from previous task
    read(S, cin, SIZE);

    cout << "Stack Values: ";
    display(S, cout);

    // separate global function for prime check
    checkPrime(S);
    cout << endl;

    // separate global function for perfect square check
    checkPerfectSquare(S);
    cout << endl;

    // separate global function for palindrome value check
    checkPalindromeValues(S);
    cout << endl;

    // final check for complete stack sequence palindrome
    if (isStackPalindrome(S))
        cout << "The values stored in the Stack form a Palindrome." << endl;
    else
        cout << "The values stored in the Stack do not form a Palindrome." << endl;

    return 0;
}