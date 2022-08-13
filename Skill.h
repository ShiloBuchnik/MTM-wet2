#ifndef SKILL_H_
#define SKILL_H_

#include <string>
#include <iostream>

using std::ostream;
using std::string;

namespace mtm {
	class Skill
	{
	private:
		int id, requiredPoints;
		string name;

	public:
		Skill(int id, string name, int requiredPoints): name(name)
		{
			this->id = id;
			this->requiredPoints = requiredPoints;
		}

		int getId() const;
		string getName() const;
		int getRequiredPoints() const;

		friend bool operator < (const Skill &obj1, const Skill &obj2);

		Skill operator++(int);
		Skill& operator+=(int pointsToAdd);

		Skill(const Skill &obj) = default;
		~Skill() = default;
	};

	
	// Simple Operators
	bool operator > (const Skill &obj1, const Skill &obj2);
	bool operator == (const Skill &obj1, const Skill &obj2);
	bool operator <= (const Skill &obj1, const Skill &obj2);
	bool operator >= (const Skill &obj1, const Skill &obj2);
	bool operator != (const Skill &obj1, const Skill &obj2);


	Skill operator + (Skill obj, int pointsToAdd);
	Skill operator + (int pointsToAdd, Skill obj);
	ostream& operator << (ostream& os, const Skill &obj);


	bool compareSkillId(Skill& skill1, Skill& skill2);

}

#endif
