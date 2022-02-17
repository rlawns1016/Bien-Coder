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

		EmployeeResultSet rsltSet;
		for (auto aKey : pks) {
			if (option1 == "-p") {
				rsltSet.insert(*db_->getEmployeeInfo(aKey));
			}
			result += (int)db_->erase(aKey);
		}
		rsltSet.toVector(resultSet);
		return result;
	}
private:
	IDataBase* db_;
};