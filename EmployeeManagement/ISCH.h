#pragma once
#include "IFinder.h"

struct ISCH {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) = 0;
};

class SCH : public ISCH {
public:
	SCH(IFinder* finder) : finder_(finder) {
	}

	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) override {
		resultSet.clear();
		vector <list<EmployeeInfo>::iterator> its;
		its = finder_->searchIterator(option2, column, param);
		if (option1 == "-p") {
			for (auto it : its) {
				resultSet.push_back(*it);
			}
			// TODO :: check over 5
		}
		return its.size();
	}
private:
	IFinder* finder_;
};