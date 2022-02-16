#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "mainFrame.h"

using namespace std;

struct IFinder {
	virtual vector<list<EmployeeInfo>::iterator> searchIterator(string option, string column, string param) = 0;
};

class Finder : public IFinder {
public:
	Finder(list<EmployeeInfo>& employee) : employee_(employee) {
	}

	virtual vector<list<EmployeeInfo>::iterator> searchIterator(string option, string column, string param) override {
		vector<list<EmployeeInfo>::iterator> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (compare(option, column, param, &*it)) {
				result.push_back(it);
			}
		}
		return result;
	}
	
private:
	vector<string> split(string str, char delimiter) {
		vector<string> internal;
		stringstream ss(str);
		string temp;
		while (getline(ss, temp, delimiter)) {
			internal.push_back(temp);
		}
		return internal;
	}

	unsigned int getFullYearEmployeeNum(string employeeNum) {
		int num = stoi(employeeNum);
		return (num >= 69000000) ? num + 1900000000 : num + 2000000000;
	}

	CL getCL(string cl) {
		if (cl == "CL1") return CL1;
		else if (cl == "CL2") return CL2;
		else if (cl == "CL3") return CL3;
		else /*if (cl == "CL4")*/ return CL4;
		//TODO :: invalid CL
	}

	CERTI getCerti(string certi) {
		if (certi == "ADV") return ADV;
		else if (certi == "PRO") return PRO;
		else /*if (certi == "EX")*/ return EX;
		//TODO :: invalid certi
	}

	bool compareName(string option, string param, EmployeeInfo* target) {
		if (option == "-f") {
			return target->name.first == param;
		}
		else if (option == "-l") {
			return target->name.last == param;
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target->name.first == split(param, ' ')[0] && target->name.last == split(param, ' ')[1]);
		}
	}
	bool comparePhoneNum(string option, string param, EmployeeInfo* target) {
		if (option == "-m") {
			return target->phoneNum.mid == stoi(param);
		}
		else if (option == "-l") {
			return target->phoneNum.end == stoi(param);
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target->phoneNum.mid == stoi(split(param, '-')[1])
				&& target->phoneNum.end == stoi(split(param, '-')[2]));
		}
	}
	bool compareBirthDay(string option, string param, EmployeeInfo* target) {
		if (option == "-y") {
			return target->birthday.y == stoi(param.substr(0, 2));
		}
		else if (option == "-m") {
			return target->birthday.m == stoi(param.substr(2, 2));
		}
		else if (option == "-d") {
			return target->birthday.d == stoi(param.substr(4, 2));
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target->birthday.y == stoi(param.substr(0, 2))
				&& target->birthday.m == stoi(param.substr(2, 2))
				&& target->birthday.d == stoi(param.substr(4, 2)));
		}
	}

	bool compare(string option, string column, string param, EmployeeInfo* target) {
		if (column == "employeeNum") {
			return getFullYearEmployeeNum(param) == target->employeeNum;
		}
		else if (column == "name") {
			return compareName(option, param, target);
		}
		else if (column == "cl") {
			return getCL(param) == target->cl;
		}
		else if (column == "phoneNum") {
			return comparePhoneNum(option, param, target);
		}
		else if (column == "birthday") {
			return compareBirthDay(option, param, target);
		}
		else if (column == "certi") {
			return getCerti(param) == target->certi;
		}
		return false;
	}

	list<EmployeeInfo>& employee_;
};

