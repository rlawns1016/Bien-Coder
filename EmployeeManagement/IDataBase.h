#pragma once

#include <iostream>
#include "mainFrame.h"
#include <unordered_map>
#include <sstream>
#include "EmployeeResultSet.h"
#include "util.h"

struct IDataBase {
	virtual vector<unsigned int> search(string option, string column, string param) = 0;
	virtual bool makeCopyFromParam(string option, string column, string param, EmployeeInfo& info) = 0;
	virtual bool modify(unsigned int employeeNum, EmployeeInfo newInfo) = 0;
	virtual bool erase(unsigned int employeeNum) = 0;
	virtual bool add(EmployeeInfo info) = 0;
	virtual EmployeeInfo* getEmployeeInfo(unsigned int employeeNum) = 0;
	virtual unsigned int getEmployeeCount() = 0;
};

struct ColumnCompare {
	enum {
		eID, eName, eCL, ePhone, eBirth, eCerti
	};
	virtual bool compare(string option, string param, EmployeeInfo target) = 0;
};

struct ColumnCompareID : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		return Util::getFullYearEmployeeNum(param) == target.employeeNum;
	}
};

struct ColumnCompareName : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		if (option == "-f") {
			return target.name.first == param;
		}
		else if (option == "-l") {
			return target.name.last == param;
		}
		else {
			vector<string> vstr = Util::split(param, ' ');
			if (vstr.size() < 1)
				throw std::invalid_argument("invalid param. name is 2 words");

			return (target.name.first == vstr[0] && target.name.last == vstr[1]);
		}
	}
};

struct ColumnCompareCerti : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		return Util::getCerti(param) == target.certi;
	}
};

struct ColumnComparePhoneNum : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		if (option == "-m") {
			return target.phoneNum.mid == stoi(param);
		}
		else if (option == "-l") {
			return target.phoneNum.end == stoi(param);
		}
		else {
			vector<string> vstr = Util::split(param, '-');
			if (vstr.size() < 2)
				throw std::invalid_argument("invalid param. phone number is 3 digits");

			return (target.phoneNum.mid == stoi(vstr[1])
				&& target.phoneNum.end == stoi(vstr[2]));
		}
	}
};

struct ColumnCompareBirthDay : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		if (option == "-y") {
			return target.birthday.y == stoi(param);
		}
		else if (option == "-m") {
			return target.birthday.m == stoi(param);
		}
		else if (option == "-d") {
			return target.birthday.d == stoi(param);
		}
		else {
			if (param.size() < 8)
				throw std::invalid_argument("invalid param. birthday is 8 numbers");

			return (target.birthday.y == stoi(param.substr(0, 4))
				&& target.birthday.m == stoi(param.substr(4, 2))
				&& target.birthday.d == stoi(param.substr(6, 2)));
		}
	}
};

struct ColumnCompareCL : public ColumnCompare {
	virtual bool compare(string option, string param, EmployeeInfo target) {
		return Util::getCL(param) == target.cl;
	}
};

class DataBase : public IDataBase {
public:
	DataBase() {
		comp[ColumnCompare::eID] = new ColumnCompareID();
		comp[ColumnCompare::eName] = new ColumnCompareName();
		comp[ColumnCompare::eCL] = new ColumnCompareCL();
		comp[ColumnCompare::ePhone] = new ColumnComparePhoneNum();
		comp[ColumnCompare::eBirth] = new ColumnCompareBirthDay();
		comp[ColumnCompare::eCerti] = new ColumnCompareCerti();
	}

	virtual ~DataBase() {
		for (int i = 0; i <= ColumnCompare::eCerti; i++) {
			delete comp[i];
		}
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
		assign(column, param, info);
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

	bool compare(string option, string column, string param, EmployeeInfo target) {

		if (column == "employeeNum") {
			return comp[ColumnCompare::eID]->compare(option, param, target);
		}
		else if (column == "name") {
			return comp[ColumnCompare::eName]->compare(option, param, target);
		}
		else if (column == "cl") {
			return comp[ColumnCompare::eCL]->compare(option, param, target);
		}
		else if (column == "phoneNum") {
			return comp[ColumnCompare::ePhone]->compare(option, param, target);
		}
		else if (column == "birthday") {
			return comp[ColumnCompare::eBirth]->compare(option, param, target);
		}
		else if (column == "certi") {
			return comp[ColumnCompare::eCerti]->compare(option, param, target);
		}
		else {
			throw std::invalid_argument("invalid column. Column cosist name, cl, phoneNum, birthday, certi");
		}
		return false;
	}

	void assignName(string param, EmployeeInfo& target) {
		vector<string> vstr = Util::split(param, ' ');
		if (vstr.size() < 1) 
			throw std::invalid_argument("invalid param. name is 2 words");

		target.name.first = vstr[0];
		target.name.last = vstr[1];
	}
	void assignPhoneNum(string param, EmployeeInfo& target) {
		vector<string> vstr = Util::split(param, '-');
		if (vstr.size() < 2)
			throw std::invalid_argument("invalid param. phone number is 3 digits");

		target.phoneNum.mid = stoi(vstr[1]);
		target.phoneNum.end = stoi(vstr[2]);
	}
	void assignBirthDay( string param, EmployeeInfo& target) {
		if (param.size() < 8) 
			throw std::invalid_argument("invalid param. phone number is 8 numbers");

		target.birthday.y = stoi(param.substr(0, 4));
		target.birthday.m = stoi(param.substr(4, 2));
		target.birthday.d = stoi(param.substr(6, 2));
	}
	void assign(string column, string param, EmployeeInfo& target) {
		if (column == "employeeNum") {
			target.employeeNum = Util::getFullYearEmployeeNum(param);
		}
		else if (column == "name") {
			assignName(param, target);
		}
		else if (column == "cl") {
			target.cl = Util::getCL(param);
		}
		else if (column == "phoneNum") {
			assignPhoneNum(param, target);
		}
		else if (column == "birthday") {
			assignBirthDay(param, target);
		}
		else if (column == "certi") {
			target.certi = Util::getCerti(param);
		}
		else {
			throw std::invalid_argument("invalid column. Column cosist name, cl, phoneNum, birthday, certi");
		}
	}

	unordered_map<unsigned int, EmployeeInfo> employee_;
	ColumnCompare* comp[6];
};

