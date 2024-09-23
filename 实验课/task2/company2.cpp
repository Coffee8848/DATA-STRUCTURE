#include "company2.h"
#include "employee2.h"

void Company2::findBestPaid()
{
	if (employees.empty()) {
		std::cout << "No employees in the company." << std::endl;
		return;
	}

	Employee2* bestPaid = &employees[0];
	for (auto& employee : employees) {
		if (employee.getSalary() > bestPaid->getSalary()) {
			bestPaid = &employee;
		}
	}

	std::cout << "Best paid employee: " << bestPaid->getName() << " with salary " << bestPaid->getSalary() << std::endl;
}