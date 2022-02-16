#pragma once
#include "IFinder.h"
#include <vector>

struct IMOD {
	virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet) = 0;	
};

class MOD : public IMOD {

public:
	
	MOD(IFinder* finder, list<EmployeeInfo>& employee) : finder_(finder), employee_(employee) {
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
