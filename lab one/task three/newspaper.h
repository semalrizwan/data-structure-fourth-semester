#pragma once
#include"library.h"
#include<iostream>
using namespace std;
class newspaper :public library
{
protected:
	string publishingdate;
	string edition;
public:
	//setter 
	void setdate(string date)
	{
		publishingdate = date;
	}
	void setedition(string e)
	{
		edition = e;
	}
	//getters
	string getdate()
	{
		return publishingdate;
	}
	string getedition()
	{
		return edition;
	}
	//parameterized constructor
	newspaper(string title, string date, string e) :library(title)
	{
		publishingdate = date;
		edition = e;
	}
	//function to display newsapaper details
	void display()
	{
		cout << "\nNewspaper Title: " << booktitle;
		cout << "\nPublishing Date: " << publishingdate;
		cout << "\nEdition: " << edition;
	}
};

