#include<iostream>
#include"fulltimeemployee.h"
#include"parttimeemployee.h"
using namespace std;
int main()
{
	//creating objects
	fulltimeemployee e1(60000); //fixed salary
	parttimeemployee e2(5, 650); //worked 5 hours at the rate of 900 per hour

	cout << "\nFull Time Employee Salary: " << e1.calculatesalary() << " ";
	cout << "\nPart Time Employee Salary: " << e2.calculatesalary() << " ";
	return 0;
}