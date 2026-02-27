#pragma once
#include<iostream>
using namespace std;
class library //base class
{
protected:
	string booktitle;
public:
	//setter
	void settitle(string title)
	{
		booktitle = title;
	}
	//getter
	string gettitle()
	{
		return booktitle;
	}
	//parameterized constructor
	library(string title)
	{
		booktitle = title;
	}
	//virtual function for base class
	virtual void display() = 0;
	//destructor
	virtual ~library()
	{

	}
};

