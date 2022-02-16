#pragma once
#include "IFinder.h"

struct IDEL {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) = 0;
};

class DEL : public IDEL {
public:
	DEL(IFinder* finder, list<EmployeeInfo>& employee) : finder_(finder), employee_(employee) {
	}

	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) override {
		resultSet.clear();
		vector <list<EmployeeInfo>::iterator> its;
		its = finder_->searchIterator(option2, column, param);
		for (auto it : its) {
			if (option1 == "-p") {
				resultSet.push_back(*it);
			}
			employee_.erase(it);
		}
			// TODO :: check over 5
		return its.size();
	}
private:
	IFinder* finder_;
	list<EmployeeInfo>& employee_;
};