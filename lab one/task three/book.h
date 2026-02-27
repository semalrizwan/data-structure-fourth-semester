#pragma once
#include"library.h"
#include<iostream>
using namespace std;
class book:public library
{
protected:
	string authorname;
	int page;
public:
	//setter 
	void setname(string name)
	{
		authorname = name;
	}
	void setpage(int p)
	{
		page = p;
	}
	//getter
	string getname()
	{
		return authorname;
	}
	int getpage()
	{
		return page;
	}
	//parameterized constructor
	book(string title, string name, int p) :library(title)
	{
		authorname = name;
		page = p;
	}
	//function to display book details
	void display()
	{
		cout << "\nBook Title: " << booktitle;
		cout << "\nAuthor Name: " << authorname;
		cout << "\nBook Page: " << page;
	}

};

