#pragma once
#include"course.h"
#include<iostream>
using namespace std;
class onlinecourse 
{
private:
	int weeks;
	int hoursperweek;
public:
	//parameterized constructor
	onlinecourse(int w, int hours)
	{
		weeks = w;
		hoursperweek = hours;
	}
	//function to return area
	int duration()
	{
		return weeks * hoursperweek;
	}
};

