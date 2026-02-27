#pragma once
#include"employee.h"
#include<iostream>
using namespace std;
class fulltimeemployee
{
private:
	float fixedsalary;
public:
	//parameterized function
	fulltimeemployee(float s)
	{
		fixedsalary = s;
	}
	//function to return the salary 
	double calculatesalary()
	{
		return fixedsalary;
		//since the fulltime employee has a fixed salary so we dont need to calculate it
	}
};

