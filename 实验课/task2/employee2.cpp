#include "employee2.h"

#include <iostream>
using namespace std;

Employee2::Employee2()
{
	month = 0;
	monthlySalary = 0;
}

void Employee2::input()
{
	cout << "Please enter a name, month, and monthly salary; to quit, enter * followed by any number: ";
	cin >> name >> month >> monthlySalary;
}