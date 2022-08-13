#ifndef CITIZEN_H_
#define CITIZEN_H_

#include <string>
#include <iostream>
using std::string;

namespace mtm {
  class Citizen {
  protected:
      int id_number;
      string first_name;
      string last_name;
      int birth_year;
      int salary;
      
  public:
    Citizen(int id_number, string first_name, string last_name, int birth_year) :
      id_number(id_number), first_name(first_name), last_name(last_name), birth_year(birth_year) {
        this->salary = 0;
    };


    // Getter methods
    int getId() const {
      return id_number;
    }
    string getFirstName() const {
      return first_name;
    }
    string getLastName() const {
      return last_name;
    }
    int getBirthYear() const {
      return birth_year;
    }

    // Added property of joined salary between citizens
    virtual int getSalary() const= 0;
    
    // Compare citizens using ID number

    // Only operator> is defined as friend, other comparative operators are based on it
    friend bool operator>(const Citizen& c1, const Citizen& c2);

    // Pure virtual printing methods
    virtual std::ostream& printShort(std::ostream& os) = 0;
    virtual std::ostream& printLong(std::ostream& os) = 0;

    // Pure virtual clone method
    virtual Citizen* clone() const = 0;
    // Definition for virtual destructor
    virtual ~Citizen() = default;
  };

  // These comparative operators are based on Citizen friend operator>
  bool operator<(const Citizen& c1, const Citizen& c2);
  bool operator==(const Citizen& c1, const Citizen& c2);
  bool operator>=(const Citizen& c1, const Citizen& c2);  
  bool operator<=(const Citizen& c1, const Citizen& c2);
  bool operator!=(const Citizen& c1, const Citizen& c2);

	// This function is a reduction case to comparing two citizens using their pointers
	bool compareCitizenPtrId(Citizen* cit1, Citizen* cit2);


}

  #endif