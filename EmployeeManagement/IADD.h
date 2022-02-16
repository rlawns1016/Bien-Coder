#pragma once
#include "mainFrame.h"
#include "IDataBase.h"

struct IADD {
	virtual int execute(const EmployeeInfo& info) = 0;
};

class ADD : public IADD {

public:
	ADD(IDataBase* db) : db_(db) {
	}

	virtual int execute(const EmployeeInfo& info) override
	{
		return db_->add(info);
	}

private:
	IDataBase* db_;
};

