#pragma once
#include<iostream>
using namespace std;
class course
{
public:
	//since we only need to make the function we'll just use public
	virtual int duration() = 0;
	virtual ~course()
	{

	}
};

