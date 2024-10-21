#include <iostream>
#include "company.h"

using namespace std;

void Company::inputEmployee()
{
    //Task 1: Please implement this!
    Employee newEmployee;
    newEmployee.input();
    empContainer.addHead(newEmployee);

}


void Company::findBestPaid()
{
	if (empContainer.isEmpty()){
		cout << "错误 无员工" << endl;
	}
	ListCont<Employee>::Iterator it = empContainer.Begin();
	bestPaid = *it;
	for (; it != empContainer.End(); it++){
		if (*it > bestPaid){
			bestPaid = *it;
		}
	}

	//Task 2: please implement this!
}

void Company::printBestPaid() const
{
	cout << "The best-paid employee and gross pay: " << endl;
	bestPaid.output();
} // printBestPaid
