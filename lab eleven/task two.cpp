/*
1. understanding:
 use a stack to solve math problems written in prefix and postfix styles
 move a stack to another stack following the rules where a bigger
 number can never sit on top of a smaller number

2. steps:
- read the symbols if it is a number put it in the stack
if it is a math sign take two numbers out do the math, and put it back
- move all except the bottom one to a middle spot
move the bottom one to the goal then move the rest on top

3. functions:
 push and pop from the arraystack to manage the data
the logic relies on the stack's last in first out nature

4. learning:
math expressions can be solved easily if you process them
from the correct side using a stack

5. skills:
solving complex ordering problems and understand the movement of
data between different storage containers
*/

#include <iostream>
#include "MyStack.h"
using namespace std;

// evaluate prefix (reading right to left)
int evaluatePrefix(char* expression, MyStack s) 
{
    // find the end of the string first
    static int i = 0;
    if (expression[i] == '\0')
    {
        return s.top();
    }
    // this requires moving to the end and coming back
    //  process the character
    char c = expression[i++];
    // if it is a number
    if (c >= '0' && c <= '9') 
    {
        // push onto stack
        s.push(c - '0');
    }
    else 
    {
        // it is an operator, get two values
        int v1, v2;
        s.pop(v1);
        s.pop(v2);
        // apply operator and push back
        if (c == '+')
        {
            s.push(v1 + v2);
        }
        else if (c == '-')
        {
            s.push(v1 - v2);
        }
    }
    // recurse
    return evaluatePrefix(expression, s);
}

// move stack using hanoi rules
void copyTOH(MyStack src, MyStack& copy)
{
    // if source is empty, do nothing
    if (src.isEmpty())
    {
        return;
    }
    int topVal;
    // take the top item
    src.pop(topVal);
    // move everything else first
    copyTOH(src, copy);
    // put the item in the new stack
    copy.push(topVal);
}

int main() 
{
    // create a stack with size 20
    MyStack s1(20); 
    // create a character array for a prefix math problem
    char pre[] = "+91";  
    // solve the prefix problem and show the result
    cout << "prefix result: " << evaluatePrefix(pre, s1) << endl; 

    // reset the index and create a postfix problem
    char post[] = "91+";
    // solve the postfix problem and show the result
    cout << "postfix result: " << evaluatePostfix(post, s1) << endl; 

    // create two stacks to test the copy function
    MyStack source(10); // 
    MyStack destination(10); 
    // add some numbers to the first stack
    source.push(3); // 
    source.push(2); // 
    source.push(1); // 
    // use the hanoi logic to move them to the second stack
    copyTOH(source, destination); 

    // finish the program
    return 0; 
}