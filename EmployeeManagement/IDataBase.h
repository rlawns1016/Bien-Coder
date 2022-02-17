#pragma once

#include <iostream>
#include "mainFrame.h"
#include <unordered_map>

struct IDataBase {
	virtual vector<unsigned int> search(string option, string column, string param) = 0;
	virtual bool makeCopyFromParam(string option, string column, string param, EmployeeInfo& info) = 0;
	virtual bool modify(unsigned int employeeNum, EmployeeInfo newInfo) = 0;
	virtual bool erase(unsigned int employeeNum) = 0;
	virtual bool add(EmployeeInfo info) = 0;
	virtual EmployeeInfo* getEmployeeInfo(unsigned int employeeNum) = 0;
	virtual unsigned int getEmployeeCount() = 0;
};

class DataBase : public IDataBase {
public:
	DataBase() {
	}

	virtual bool erase(unsigned int employeeNum) override {
		return employee_.erase(employeeNum);
	}

	virtual bool add(EmployeeInfo info) override {
		unsigned int employeeNum = info.employeeNum;
		return employee_.insert({ employeeNum, info }).second;
	}

	virtual bool modify(unsigned int employeeNum, EmployeeInfo newInfo) override {
		if(employee_.find(employeeNum) == employee_.end()) return false;
		employee_[employeeNum] = newInfo;
		return true;
	}


	virtual vector<unsigned int> search(string option, string column, string param) override {
		vector<unsigned int> result;
		for (auto it = employee_.begin(); it != employee_.end(); ++it) {
			if (compare(option, column, param, it->second)) {
				result.push_back(it->first);
			}
		}
		return result;
	}

	virtual bool makeCopyFromParam(string option, string column, string param, EmployeeInfo& info) override {
		assign(option, column, param, info);
		return true; //TODO :: return
	}

	virtual EmployeeInfo* getEmployeeInfo(unsigned int employeeNum) {
		if (employee_.find(employeeNum) == employee_.end()) return nullptr;
		return &employee_[employeeNum];
	}

	virtual unsigned int getEmployeeCount() {
		return employee_.size();
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

	bool compareName(string option, string param, EmployeeInfo target) {
		if (option == "-f") {
			return target.name.first == param;
		}
		else if (option == "-l") {
			return target.name.last == param;
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target.name.first == split(param, ' ')[0] && target.name.last == split(param, ' ')[1]);
		}
	}
	bool comparePhoneNum(string option, string param, EmployeeInfo target) {
		if (option == "-m") {
			return target.phoneNum.mid == stoi(param);
		}
		else if (option == "-l") {
			return target.phoneNum.end == stoi(param);
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target.phoneNum.mid == stoi(split(param, '-')[1])
				&& target.phoneNum.end == stoi(split(param, '-')[2]));
		}
	}
	bool compareBirthDay(string option, string param, EmployeeInfo target) {
		if (option == "-y") {
			return target.birthday.y == stoi(param);
		}
		else if (option == "-m") {
			return target.birthday.m == stoi(param);
		}
		else if (option == "-d") {
			return target.birthday.d == stoi(param);
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			return (target.birthday.y == stoi(param.substr(0, 4))
				&& target.birthday.m == stoi(param.substr(4, 2))
				&& target.birthday.d == stoi(param.substr(6, 2)));
		}
	}

	bool compare(string option, string column, string param, EmployeeInfo target) {
		if (column == "employeeNum") {
			return getFullYearEmployeeNum(param) == target.employeeNum;
		}
		else if (column == "name") {
			return compareName(option, param, target);
		}
		else if (column == "cl") {
			return getCL(param) == target.cl;
		}
		else if (column == "phoneNum") {
			return comparePhoneNum(option, param, target);
		}
		else if (column == "birthday") {
			return compareBirthDay(option, param, target);
		}
		else if (column == "certi") {
			return getCerti(param) == target.certi;
		}
		return false;
	}

	void assignName(string option, string param, EmployeeInfo& target) {
		if (option == "-f") {
			target.name.first = param;
		}
		else if (option == "-l") {
			target.name.last = param;
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			target.name.first = split(param, ' ')[0];
			target.name.last = split(param, ' ')[1];
		}
	}
	void assignPhoneNum(string option, string param, EmployeeInfo& target) {
		if (option == "-m") {
			target.phoneNum.mid = stoi(param);
		}
		else if (option == "-l") {
			target.phoneNum.end = stoi(param);
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			target.phoneNum.mid = stoi(split(param, '-')[1]);
			target.phoneNum.end = stoi(split(param, '-')[2]);
		}
	}
	void assignBirthDay(string option, string param, EmployeeInfo& target) {
		if (option == "-y") {
			target.birthday.y = stoi(param);
		}
		else if (option == "-m") {
			target.birthday.m = stoi(param);
		}
		else if (option == "-d") {
			target.birthday.d = stoi(param);
		}
		else { //TODO :: check invalid option ?
			//TODO :: check valid param ? -> is exist space..
			target.birthday.y = stoi(param.substr(0, 4));
			target.birthday.m = stoi(param.substr(4, 2));
			target.birthday.d = stoi(param.substr(6, 2));
		}
	}
	void assign(string option, string column, string param, EmployeeInfo& target) {
		if (column == "employeeNum") {
			target.employeeNum = getFullYearEmployeeNum(param);
		}
		else if (column == "name") {
			assignName(option, param, target);
		}
		else if (column == "cl") {
			target.cl = getCL(param);
		}
		else if (column == "phoneNum") {
			assignPhoneNum(option, param, target);
		}
		else if (column == "birthday") {
			assignBirthDay(option, param, target);
		}
		else if (column == "certi") {
			target.certi = getCerti(param);
		}
	}

	unordered_map<unsigned int, EmployeeInfo> employee_;
};

