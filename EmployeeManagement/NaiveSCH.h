#pragma once
#include "ISCH.h"

class NaiveSCH : public ISCH {
public:
	NaiveSCH(vector<EmployeeInfo>& employee);

	// basic
	virtual vector<EmployeeInfo*> searchByName(Name name) override;
	virtual vector<EmployeeInfo*> searchByPhoneNumber(PhoneNumber number) override;
	virtual vector<EmployeeInfo*> searchByBirth(Birthday birth) override;
	virtual vector<EmployeeInfo*> searchByCL(CL cl) override;
	virtual vector<EmployeeInfo*> searchByCerti(CERTI certi) override;

	// option
	virtual vector<EmployeeInfo*> searchByFirstName(string name) override;
	virtual vector<EmployeeInfo*> searchByLastName(string name) override;
	virtual vector<EmployeeInfo*> searchByMidPhoneNumber(int numeber) override;
	virtual vector<EmployeeInfo*> searchByLastPhoneNumber(int number) override;
	virtual vector<EmployeeInfo*> searchByBirthYear(string year) override;
	virtual vector<EmployeeInfo*> searchByBirthMonth(string month) override;
	virtual vector<EmployeeInfo*> searchByBirthDay(string day) override;

	virtual ~NaiveSCH() {};

private:
	vector<EmployeeInfo>& employee_;
};

