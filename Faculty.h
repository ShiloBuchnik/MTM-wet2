#ifndef FACULTY_H_INCLUDED
#define FACULTY_H_INCLUDED

#include "Employee.h"
#include "Skill.h"
#include "exceptions.h"


namespace mtm {
   // This is an abstact class for Faculty Conditions
   class Condition {
      public:
         virtual bool operator()(Employee* employee) = 0;
   };

   template<class FacultyCondition>
   class Faculty
   {
      private:
         int id, added_points;
         FacultyCondition* acceptance_condition;
         Skill skill;
      
      public:
         Faculty(int id, Skill skill, int added_points, FacultyCondition* condition_ptr):
            skill(skill.getId(), skill.getName(), skill.getRequiredPoints())
         {
            this->id = id;
            this->added_points = added_points;
            this->acceptance_condition = condition_ptr;
         }

         
         Skill getSkill() const {
            return this->skill;
         }

         int getId() const {
            return this->id;
         }

         int getAddedPoints() const {
            return this->added_points;
         }
         
         void teach(Employee* obj);
         
         Faculty(const Faculty &obj) = default;
         ~Faculty() = default;
   };

   template<class FacultyCondition>
	void Faculty<FacultyCondition>::teach(Employee *obj) {
         // Throw appropriate exception if employee cannot be taught skill
         if (!(*this->acceptance_condition)(obj)) {
            throw EmployeeNotAccepted();
         }
         obj->learnSkill(this->skill); // Try learn skill, throws exception and does not set score on error
         obj->setScore(this->added_points);
	}
}

#endif
