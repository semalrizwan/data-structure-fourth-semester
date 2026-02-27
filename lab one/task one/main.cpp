//GIRHUB LINK: https://github.com/semalrizwan/data-structure-fourth-semester.git


#include<iostream>
#include"onlinecourse.h"
#include"offlineclass.h"
using namespace std;
int main()
{
	//creating class objects
	onlinecourse o1(3, 4);
	offlineclass o2(4, 3);
	cout << "\nDuration of online class: " << o1.duration() << " hours ";
	
	cout << "\nDuration of offline class: " << o2.duration() << " hours ";
	
	return 0;
}