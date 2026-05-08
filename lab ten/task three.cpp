#include<iostream>
using namespace std;
/*
1. UNDERTANDING:
 stack operations like copy, display, finding the maximum and minimum size but we need to do this using recurrsion
 stack uses LIFO so the function calls can easily remember the values until the all the values are popped and the 
 base case is executed

2. SOLUTION:
 to use the stack recurrsively we first pop the element and then call the recursive function for all the remaining values
 in the stack except for the one that we popped ten once its done we oush back all the values and restore the stack

3. LEARNING:how to use a recurrsions rac to temporarily store the data without using any other data structure

4. SKILLS:
manipulating complex dfata structures using stack knowledge
*/

//1.copy functions
void copyStack(ArrayStack<int> src, ArrayStack<int>& copy)
{
	//base case
	if (src.isEmpty())
	{
		return; 
	}
	//recurrsive case
	int v;
	src.pop(v);
	copyStack(src, copy);
	copy.push(v);
}

//2.display stack
void display(ArrayStack<int> as)
{
	//base case 
	if (as.isEmpty())
	{
		return;
	}
	//recurrsive
	int v;
	as.pop(v);
	cout << "\n" << v;
	display(as);
}

//3.get size
int getSize(ArrayStack<int> as)
{
	//base case
	if (as.isEmpty())
	{
		return;
	}
	//recurrsive case
	int v;
	as.pop(v);
	return 1 + getSize(as); //it adds one to the size for the current element
}

//4.max elememt
int getSize(ArrayStack<int> as)
{
	//base case
	if (as.isEmpty())
	{
		return v;
	}
	int v;
	as.pop(v);
	int next = max(as);
	retunr(v > next) ? v : next;
}

//count functions
int count(ArrayStack<int> adt, int val)
{
	if (adt.isEmpty())
	{
		return 0;
	}
	int v;
	adt.pop(v);
	int mat5ch = (v == val) ? 1 : 0;
	return match + count(adt, val);
}

//frequency function
ArrayStack<int> frequency(ArrayStack<int> adt)
{
	//base case
	if (adt.isEmpt())
	{
		return;
	}
	//recurrsion
	int v;
	adt.pop(v);
	int freq = count(adt, v) + 1;
	int result = frequency(adt);
	result.push(freq);
	return result;
}

