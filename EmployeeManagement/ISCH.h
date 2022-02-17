#pragma once
#include "IDataBase.h"

struct ISCH {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) = 0;
};

class SCH : public ISCH {
public:
	SCH(IDataBase* db) : db_(db) {
	}

	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) override {
		resultSet.clear();
		vector<unsigned int> pks;
		int result = 0;
		EmployeeResultSet rsltSet;
		pks = db_->search(option2, column, param);
		for (auto aKey : pks) {
			if (option1 == "-p") {
				rsltSet.insert(*db_->getEmployeeInfo(aKey));
			}
			result++;
		}
		rsltSet.toVector(resultSet);
		return result;

	}
private:
	IDataBase* db_;
};