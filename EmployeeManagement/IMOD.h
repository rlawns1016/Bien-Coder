#pragma once
#include <iostream>
#include <vector>
#include "mainFrame.h"

using namespace std;


struct SearchBaseCmd {

	virtual vector<EmployeeInfo*> searchByFirstName(string name) = 0;
	virtual vector<EmployeeInfo*> searchByLastName(string name) = 0;
};

class ModifyCmd : public SearchBaseCmd {
public:
	ModifyCmd(const EmployeeListParameter& param, DB& database);
	~ModifyCmd();	

private:
	vector<EmployeeInfo>& employee_;

	string Search_ColumnName;
	string Search_ColumValue;
	string Mod_ColumnName;
	string Mod_ColumnValue;
};

#if 0 // temp
ModifyCmd::ModifyCmd(const EmployeeListParameter& param, DB& database) : BaseCmd{ param, database) {

	Search_ColumnName = param.GetArgs()[0];
	Search_ColumValue = param.GetArgs()[1];
	Mod_ColumnName = param.GetARgs()[2];
	Mod_ColumnValue = param.GetArgs()[3];
}

ModifyCmd::~ModifyCmd() {

}	

string ModifyCmd::Process() {

	// need to DataBase Type : SearchColumnName & Opetion -p, -f/-l, -m/-l, -y/-m/-d
	// need to MofidyColumName : none

	string result = GetResult(employeeList); 
	
	for (auto employee : employeeList) {
		delete employee;
	}

	return result;
}
#endif
