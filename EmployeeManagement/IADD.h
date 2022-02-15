#pragma once
#include "mainFrame.h"
#include <vector>

struct IADD {
	virtual void AddEmployeeInfo(const EmployeeInfo& info) = 0;
};

class ADD : public IADD {

public:
	ADD(vector<EmployeeInfo>& employee) : employee_(employee) {}

	virtual void AddEmployeeInfo(const EmployeeInfo& info) override
	{
		employee_.push_back(info);
	}

private:
	vector<EmployeeInfo>& employee_;
};

