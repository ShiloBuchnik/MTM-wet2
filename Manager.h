#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Citizen.h"
#include "Employee.h"

using std::string;

namespace mtm {
	class Manager : public Citizen {
		std::vector<Employee*> employees;
	public:
		Manager(int id_number, string first_name, string last_name, int birth_year) :
			Citizen(id_number, first_name, last_name, birth_year) {
			
		}

		// Checks whether manager has employees.
		bool hasEmployees() const {
			return !this->employees.empty();
		}

		// Simply return 'salary' property of Manager
		int getSalary() const override {
			return salary;
		}

		// Simply add to current 'salary' of Manager, assume correct parameter
		void setSalary(int additional_salary) {
			salary = (salary < -additional_salary) ? 0 : salary + additional_salary;
		}

		void addEmployee(Employee *employee);

		void removeEmployee(int id_number);

		// Declare destructor and 'clone' methods
		~Manager() override = default;
		Manager* clone() const override;

		
		// Implementation of virutal printing functions
		std::ostream& printShort(std::ostream& os) override;
		std::ostream& printLong(std::ostream& os) override;


		/* ~~~ Custom Methods ~~~ */

		// Fetch employee working under manager, return NULL in case of no such employee being found
		Employee* fetchEmployee(int employee_id);

		bool hasEmployee(int employee_id) {
			return (fetchEmployee(employee_id) != NULL);
		}

		bool hasEmployee(Employee* employee) const {
			return (std::count(this->employees.begin(), this->employees.end(), employee));
		}

		// Reduce salary of employees when manager is fired
		void setEmployeeSalaries(int common_salary);

		// Fire employees for when manager is fired from workplace
		void fireEmployees() {
			this->employees.clear();
		}
	};
}
	#endif