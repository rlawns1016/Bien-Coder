#pragma once

#include "IDataBase.h"

struct IDEL {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) = 0;
};

class DEL : public IDEL {
public:
	DEL(IDataBase* db) : db_(db) {
	}

	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) override {
		resultSet.clear();
		vector<unsigned int> pks;
		int result = 0;
		pks = db_->search(option2, column, param);
		for (auto aKey : pks) {
			if (option1 == "-p") {
				resultSet.push_back(*db_->getEmployeeInfo(aKey));
			}
			result += (int)db_->erase(aKey);
		}
		return result;
	}
private:
	IDataBase* db_;
};


struct IMOD {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet, const EmployeeInfo newinfo) = 0;
};

class MOD : public IMOD {
public:
	MOD(IDataBase* db) : db_(db) {
	}

	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet, const EmployeeInfo newinfo) override {		

		resultSet.clear();
		vector<unsigned int> pks;	

		int result = 0;			

		pks = db_->search(option2, column, param);
		for (auto aKey : pks) {
			if (option1 == "-p") {
				resultSet.push_back(*db_->getEmployeeInfo(aKey));
			}			
			if (column != "employeeNum") {
				result += (int)db_->modify(aKey, newinfo);
			}			
		}
		return result;
	}
private:
	IDataBase* db_;
};


struct IMOD_Exception {
	virtual void ModEmployeeInfoException(const EmployeeInfo& info) = 0;
};

class MOD_Exception : public IMOD_Exception {

public:
	MOD_Exception(vector<EmployeeInfo>& employee) : employee_mod(employee) {}

	virtual void ModEmployeeInfoException(const EmployeeInfo& info) override
	{
		employee_mod.push_back(info);
	}

private:
	vector<EmployeeInfo>& employee_mod;
};
