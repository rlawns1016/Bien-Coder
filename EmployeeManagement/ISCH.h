#pragma once
#include <iostream>
#include <vector>
#include "mainFrame.h"

using namespace std;

struct ISCH {
	
	// basic
	virtual vector<EmployeeInfo*> searchByName(Name name) = 0;
	virtual vector<EmployeeInfo*> searchByPhoneNumber(PhoneNumber number) = 0;
	virtual vector<EmployeeInfo*> searchByBirth(Birthday birth) = 0;
	virtual vector<EmployeeInfo*> searchByCL(CL cl) = 0;
	virtual vector<EmployeeInfo*> searchByCerti(CERTI certi) = 0;

	// option
	virtual vector<EmployeeInfo*> searchByFirstName(string name) = 0;
	virtual vector<EmployeeInfo*> searchByLastName(string name) = 0;
	virtual vector<EmployeeInfo*> searchByMidPhoneNumber(int numeber) = 0;
	virtual vector<EmployeeInfo*> searchByLastPhoneNumber(int number) = 0;
	virtual vector<EmployeeInfo*> searchByBirthYear(string year) = 0;
	virtual vector<EmployeeInfo*> searchByBirthMonth(string month) = 0;
	virtual vector<EmployeeInfo*> searchByBirthDay(string day) = 0;
};