#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <vector>
#include <string>

#include "Skill.h"
#include "Citizen.h"

using std::string;
using std::ostream;
using std::vector;

namespace mtm {

	class Employee: public Citizen
	{
	private:
		int score;
		vector<Skill> skills;

	public:
		Employee(int id, string firstName, string lastName, int birthYear): Citizen(id, firstName, lastName, birthYear)
		{
			score = 0;
		}

		int getScore() const;
		void setScore(int scoreToAdd);
		int getSalary() const override;
		void setSalary(int salaryToAdd);

		void learnSkill(const Skill& obj);
		void forgetSkill(int skillId);
		bool hasSkill(int skillId);

		ostream& printShort(ostream& os) override;
		ostream& printLong(ostream& os) override;

		Employee* clone() const override;

		~Employee() override = default;
	};

}

#endif