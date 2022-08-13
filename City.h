#ifndef CITY_H_
#define CITY_H_

#include <set>
#include <vector>
#include <iostream>
#include <string>

#include "Faculty.h"
#include "Workplace.h"
#include "Manager.h"
#include "Employee.h"
#include "Citizen.h"
#include "Skill.h"


using std::string;

namespace mtm {

	class City {
		private:
			std::set<Faculty<Condition>*> faculties;
			std::set<Workplace*> workplaces;
			std::set<Employee*> employees;
			std::set<Manager*> managers;

			std::vector<Citizen*> citizen_vector;

			string name;
			
			/* ~~ Custom Methods ~~ */
			// Fetch methods. All return NULL in case of object not found in city.
			// This satisfies all use cases for our custom fetch methods, except Workplace
			template<typename T>
			T* fetchPtrFromSetByID(int id, std::set<T*> ptr_set) const {
				// Initialize this variable to NULL since the method returns NULL for no pointer found case
				T* return_ptr = NULL;
				
				typename std::set<T*>::iterator itr = ptr_set.begin();
				while (itr != ptr_set.end()) {
					T* current_ptr = (*itr);
					if (current_ptr->getId() == id) {
						return_ptr = current_ptr;
						break;
					}
					++itr;
				}
				return return_ptr;
			}

			Manager* fetchManager(int manager_id) const {
				return fetchPtrFromSetByID<Manager>(manager_id, this->managers);
			}
			Employee* fetchEmployee(int employee_id) const {
				return fetchPtrFromSetByID<Employee>(employee_id, this->employees);
			}
			Faculty<Condition>* fetchFaculty(int faculty_id) const {
				return fetchPtrFromSetByID<Faculty<Condition>>(faculty_id, this->faculties);
			}

			// Check if citizen exists by ID
			bool citizenExists(int id);
		
		public:
			City(string name): name(name)
			{
				
			}

			// Add employee to city
			void addEmployee(int id_number, string first_name, string last_name, int birth_year);

			// Add manager to city
			void addManager(int id_number, string first_name, string last_name, int birth_year);
			
			// Add faculty to city
			void addFaculty(int faculty_id, Skill skill, int added_points, Condition* condition_ptr);
			
			// Create a new workplace and add to city
			void createWorkplace(int workplace_id, string workplace_name, int workplace_common_salary, int workplace_manager_common_salary);

			// Teach employee at faculty
			void teachAtFaculty(int employee_id, int faculty_id);

			// Hire employee at workplace considering employee satisfies generic condition function
			template<class Condition>
			void hireEmployeeAtWorkplace(Condition& condition, int employee_id, int manager_id, int workplace_id) {
				Employee* employee = this->fetchEmployee(employee_id);

				if (employee == NULL) {
					throw EmployeeDoesNotExist();
				}

				Manager* manager = this->fetchManager(manager_id);

				if (manager == NULL) {
					throw ManagerDoesNotExist();
				}

				Workplace* workplace = this->fetchWorkplace(workplace_id);

				if (workplace == NULL) {
					throw WorkplaceDoesNotExist();
				}

				workplace->hireEmployee(condition, employee, manager->getId());
			}

			// Hire manager to specific workplace
			void hireManagerAtWorkplace(int manager_id, int workplace_id);

			// Fire employee working under manager in specific workplace
			void fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id);

			// Fire manager working in specific workplace
			void fireManagerAtWorkplace(int manager_id, int workplace_id);

			// Display short description of all citizens whose salary is greater-or-larger than 'salary'
			int getAllAboveSalary(std::ostream& os, int salary);

			// Returns true if both employees work in the same workplace, throw exception if one of them doesn't exist
			bool isWorkingInTheSameWorkplace(int employee1_id, int employee2_id) const;
			
			// Print to ostream all employees with passed skill, in short format
			void printAllEmployeesWithSkill(std::ostream& os, int skill_id) const;

			// Destruct all pointer
			~City();

			
			Workplace* fetchWorkplace(int workplace_id) const;
		};
		
}


#endif