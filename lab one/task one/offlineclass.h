#pragma once
#include"course.h"
#include<iostream>
using namespace std;
class offlineclass 
{
private:
	int months;
	int hoursperday;
public:
	//parameterized constructor
	offlineclass(int m, int day)
	{
		months = m;
		hoursperday = day;
	}
	//function to return area
	int duration()
	{
		return months * hoursperday;
	}
};

