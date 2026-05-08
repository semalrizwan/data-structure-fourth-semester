#include<iostream>
using namespace std;
/*
1. LOGIC:
 we will use loop based fuctions to search in the array and ect
2. STARTEGY:
 we can also use if instead of using for or while loop. the if statement is used to check if we have reached the base case
 if not then we will solve the sma;; part and pass that part to the function itself. this will be the recurrsion.
3. LEARNING:
 recurrsion usually requires a very clear exit condition. it avoids infinite loops and the stack is used to keep track of eacah call
4. SKILLS:
 complex problems can be easily broken down into smaller identical problems
 */

//1. count down function
void func(int n)
{
	//base case
	if (n <= 0)
	{
		return;
	}
	cout << "\n" << n;
	//recurrsion
	func(n - 1);
}

//2. sum function
int sum(int n)
{
	//base case
	if (n <= 1)
	{
		return n; //because if it is a single nuber it will be added to zero and returned as it is
	}
	//recurrison
	return n + sum(n - 1);
}

//3. max number in an array
int maxrecurrsion(int a[], int size)
{
	//base case
	if (size == 1)
	{
		return a[0];
	}
	//recurrsion 
	int currentmax = maxrecurrsion(a, size - 1);
	return (a[size - 1] > currentmax) ? a[size - 1] : currentmax;
}

//4. count digits
int countdigits(int n)
{
	//base case
	if (n == 0)
	{
		return 0;
	}
	//recurrsion
	int count = (n % 10 != 0) ? 1 : 0;
	return count + countdigits(n / 10);
}

//5.display digits
void displaydigits(int n)
{
	//base case
	if (n < 10)
	{
		cout << "\n" << n;
		return;
	}
	//recurrsion
	displaydigits(n / 10);
	cout << n % 10 << " "; //used to show each digit separately
}

//6.binary search
int binarysearch(int a[], int low, int high, int v)
{
	//base case
	if (low > high)
	{
		return -1; //because then the numbers will go into the negatives
	}
	//for recurrsion
	int mid = low + (high - low) / 2;
	if (a[mid] == v)
	{
		return mid;
	}
	if (v > a[mid])
	{
		return binarysearch(a, mid + 1, high, v);
	}
	else
	{
		return binarysearch(a, low, mid - 1, v);
	}
}

//main function
int main()
{
	//for sum
	cout << "\nSum of 60 is: " << sum(60);
	//for max
	int array[5] = { 1,2,3,4,5 };
	cout << "\nThe maximum number in the array is: " << maxrecurrsion(array, 5);
	//for binary search
	int array2[10] = { 1,2,3,4,5,6,7,8,9,10 };
	cout << "\nThe element at index 5 is: " << binarysearch(array2, 1, 4, 7);

	return 0;
}
