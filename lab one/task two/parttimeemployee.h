#pragma once
#include"employee.h"
#include<iostream>
using namespace std;
class parttimeemployee
{
private:
	int hours;
	double rateperhour;
public:
	//parameterized constructor
	parttimeemployee(int h, float rate)
	{
		hours = h;
		rateperhour = rate;
	}
	//function to return salary after calcuation
	double calculatesalary()
	{
		return hours * rateperhour;
	}
};

