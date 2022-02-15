#pragma once
#include <iostream>
#include <vector>
#include "mainFrame.h"

using namespace std;

struct ISCH {
	virtual vector<EmployeeInfo*> searchByFirstName(string name) = 0;
	virtual vector<EmployeeInfo*> searchByLastName(string name) = 0;
	//virtual vector<Employee*> searchByMidPhoneNumber(string numeber) = 0;
	//virtual vector<Employee*> searchByLastPhoneNumber(string number) = 0;
	//virtual vector<Employee*> searchByBirthYear(string year) = 0;
	//virtual vector<Employee*> searchByBirthMonth(string month) = 0;
	//virtual vector<Employee*> searchByBirthDay(string day) = 0;
};

class NaiveSCH : public ISCH {
public:
	NaiveSCH(vector<EmployeeInfo>& employee) : employee_(employee) {
	}

	virtual vector<EmployeeInfo*> searchByFirstName(string name) override {
		vector<EmployeeInfo*> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (it->name.first == name) result.push_back(&( * it));
		}
		return result;
	};

	virtual vector<EmployeeInfo*> searchByLastName(string name) override {
		vector<EmployeeInfo*> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (it->name.last == name) result.push_back(&(*it));
		}
		return result;
	};
private:
	vector<EmployeeInfo>& employee_;
};

