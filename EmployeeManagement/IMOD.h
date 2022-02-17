#pragma once

#include "IDataBase.h"

struct IMOD {
	virtual int execute(string option1, string option2, string column, string param, string new_column, string new_param, vector<EmployeeInfo>& resultSet) = 0;
};

class MOD : public IMOD {
public:
	MOD(IDataBase* db) : db_(db) {
	}

	virtual int execute(string option1, string option2, string column, string param, string new_column, string new_param, vector<EmployeeInfo>& resultSet) override {

		resultSet.clear();
		vector<unsigned int> pks;

		int result = 0;

		pks = db_->search(option2, column, param);
		for (auto aKey : pks) {
			if (option1 == "-p") {
				if (new_column != "employeeNum") {
					resultSet.push_back(*db_->getEmployeeInfo(aKey));
				}
			}
			if (new_column != "employeeNum") {
#if 0
				db_->makeCopyFromParam(option2, new_column, new_param, *db_->getEmployeeInfo(aKey));
				result += (int)db_->modify(aKey, *db_->getEmployeeInfo(aKey));
#else
				EmployeeInfo oldInfo = *db_->getEmployeeInfo(aKey);
				db_->makeCopyFromParam(option2, new_column, new_param, oldInfo);
				result += (int)db_->modify(aKey, oldInfo);
#endif
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
