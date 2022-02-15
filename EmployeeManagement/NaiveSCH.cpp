#include "NaiveSCH.h"

NaiveSCH::NaiveSCH(vector<EmployeeInfo>& employee) : employee_(employee) {
}

vector<EmployeeInfo*> NaiveSCH::searchByName(Name name)
{
	vector<EmployeeInfo*> result;
	for (auto it = employee_.begin(); it != employee_.end(); ++it) {
		if (it->name.first == name.first && it->name.last == name.last) {
			result.push_back(&(*it));
		}
	}
	return result;
}

vector<EmployeeInfo*> NaiveSCH::searchByPhoneNumber(PhoneNumber number)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByBirth(Birthday birth)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByCL(CL cl)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByCerti(CERTI certi)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*>NaiveSCH::searchByFirstName(string name) {
	vector<EmployeeInfo*> result;
	for (auto it = employee_.begin(); it != employee_.end(); ++it) {
		if (it->name.first == name) result.push_back(&(*it));
	}
	return result;
}

vector<EmployeeInfo*>NaiveSCH::searchByLastName(string name) {
	vector<EmployeeInfo*> result;
	for (auto it = employee_.begin(); it != employee_.end(); ++it) {
		if (it->name.last == name) result.push_back(&(*it));
	}
	return result;
}

vector<EmployeeInfo*> NaiveSCH::searchByMidPhoneNumber(int numeber) {
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByLastPhoneNumber(int number)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByBirthYear(string year)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByBirthMonth(string month)
{
	return vector<EmployeeInfo*>();
}

vector<EmployeeInfo*> NaiveSCH::searchByBirthDay(string day)
{
	return vector<EmployeeInfo*>();
}

