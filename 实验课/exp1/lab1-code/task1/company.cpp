#include <iostream>
using namespace std;

#include "company.h"

void Company::inputEmployee()
{
	//Task 1: Please implement this!
	Employee newEmployee;
	newEmployee.input();
	empContainer.addHead(newEmployee);

}

int Company::getNumber() const
{
	return empContainer.getSize();
}