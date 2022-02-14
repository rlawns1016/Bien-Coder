#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Employee {
	string employeeNum;
	string firstName, lastName;
	string cl;
	string phoneNumber;
	string birthDay;
	string certi;
};

struct ISearch {
	virtual vector<Employee*> searchByFirstName(string name) = 0;
	virtual vector<Employee*> searchByLastName(string name) = 0;
	//virtual vector<Employee*> searchByMidPhoneNumber(string numeber) = 0;
	//virtual vector<Employee*> searchByLastPhoneNumber(string number) = 0;
	//virtual vector<Employee*> searchByBirthYear(string year) = 0;
	//virtual vector<Employee*> searchByBirthMonth(string month) = 0;
	//virtual vector<Employee*> searchByBirthDay(string day) = 0;
};

class NaiveSearch : public ISearch {
public:
	NaiveSearch(vector<Employee>& employee) : employee_(employee) {
	}


	virtual vector<Employee*> searchByFirstName(string name) override {
		vector<Employee*> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (it->firstName == name) result.push_back(&( * it));
		}
		return result;
	};

	virtual vector<Employee*> searchByLastName(string name) override {
		vector<Employee*> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (it->lastName == name) result.push_back(&(*it));
		}
		return result;
	};
private:
	vector<Employee>& employee_;
};

