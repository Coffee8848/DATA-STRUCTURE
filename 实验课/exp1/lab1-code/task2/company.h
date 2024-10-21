#ifndef COMPCONT_H
#define COMPCONT_H

#include "employee.h"
#include "listCont.h"

class Company
{
private:
	Employee bestPaid;
	ListCont<Employee> empContainer;

public:
	void inputEmployee(); 

	void findBestPaid(); 

	void printBestPaid() const;
}; 

#endif