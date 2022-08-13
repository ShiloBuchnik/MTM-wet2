#ifndef WORKPLACE_H_
#define WORKPLACE_H_

#include <string>
#include <set>
#include <vector>

#include "exceptions.h"
#include "Citizen.h"
#include "Manager.h"
#include "Employee.h"

using std::string;

namespace mtm {

	// This functor sorts manager IDs in Workplace managers set for printing purposes
	class ManagerIDCompare {
		public:
			bool operator()(const Manager* manager1, const Manager* manager2) const {
				return *manager1 < *manager2;
			}
	};

	class Workplace {
		int id;
		string name;
		int common_salary;
		int manager_common_salary;
		std::set<Manager*, ManagerIDCompare> managers;
		
	public:
		Workplace(int workplace_id, string workplace_name, int workplace_common_salary, int workplace_manager_common_salary) :
			id(workplace_id), name(workplace_name), common_salary(workplace_common_salary), manager_common_salary(workplace_manager_common_salary) {

			}
		
		// Getter methods
		int getID() const {
			return id;
		}
		string getName() const {
			return name;
		}
		int getWorkersSalary() const {
			return common_salary;
		}
		int getManagersSalary() const {
			return manager_common_salary;
		}

		// Condition is a generic function, therefore 'hireEmployee' is defined as a template

	template<class Condition>
	void hireEmployee(Condition& condition, Employee* employee, int manager_id) {

		// Throw an exception if employee does not comply with condition
		if (!condition(employee)) {
			throw EmployeeNotSelected();
		}
		// Throw an exception if manager is not found in workplace
		Manager* manager = this->fetchManager(manager_id);
		bool manager_found = (manager != NULL);

		if (!manager_found) {
			throw ManagerIsNotHired();
		}

		// Throw an exception if employee is already hired under manager in workplace
		if (manager->hasEmployee(employee)) {
			throw EmployeeAlreadyHired();
		}

		// All requirements are met, new employee can be safely hired by manager
		manager->addEmployee(employee);

		// Set employee salary to comply with workplace
		employee->setSalary(this->common_salary);
	}

		// Hire manager to workplace, throw an exception if manager already works there
		void hireManager(Manager* manager);

		// Fire employee working under specific manager
		void fireEmployee(int employee_id, int manager_id);

		// Fire manager and all of manager's employees from workplace
		void fireManager(int manager_id);

		// Implementation of << operator
		friend std::ostream& operator<<(ostream& os, const Workplace& workplace);

		// Custom method: fetch manager from workplace. Return NULL if manager does not work there.
		Manager* fetchManager(int manager_id) const; 

		bool hasManager(int manager_id) const {
			return (fetchManager(manager_id) != NULL);
		}
		bool hasManager(Manager* manager) const {
			return (this->managers.count(manager));
		}

		// Used for City: returns whether employee exists in workplace
		std::vector<bool> hasEmployees(int employee1_id, int employee2_id) const;

		// Reduction for one employee_id case
		bool hasEmployee(int employee_id) const {
			return (hasEmployees(employee_id, employee_id)).at(1);
		}
	};
}

#endif