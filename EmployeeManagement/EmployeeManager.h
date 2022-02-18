#pragma once

#include "mainFrame.h"
#include "IADD.h"
#include "ISCH.h"
#include "IDEL.h"
#include "IMOD.h"
#include "input.h"
#include "output.h"
#include<string>
#include "IDataBase.h"

#define ERROR_CODE_NO_ERROR				1
#define ERROR_CODE_INVALID_INSTRUCTION	-1
#define ERROR_CODE_CANNOT_OPEN_FILE		-2


struct Module
{
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) = 0;
};

class AddModule : public Module {
public : 
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		int ret = 0;
		IADD* add = new ADD(db);
		InstructionAdd* addIns = (InstructionAdd*)ins;
		EmployeeInfo info;
		addIns->GetEmployeeInfo(info);
		ret = add->execute(info);
		delete add;
		return ret;
	}
};

class DelModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		int ret = 0;
		IDEL* del = new DEL(db);
		InstructionDel* delIns = (InstructionDel*)ins;
		string columnName, columnValue;
		delIns->GetColumnData(columnName, columnValue);
		ret = del->execute(delIns->GetOption1(), delIns->GetOption2(), columnName, columnValue, resultSet);
		delete del;
		return ret;
	}
};

class SchModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		int ret = 0;
		ISCH* sch = new SCH(db);
		InstructionSch* schIns = (InstructionSch*)ins;
		string columnName, columnValue;
		schIns->GetColumnData(columnName, columnValue);
		ret = sch->execute(schIns->GetOption1(), schIns->GetOption2(), columnName, columnValue, resultSet);
		delete sch;
		return ret;
	}
};

class ModModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		int ret = 0;
		IMOD* mod = new MOD(db);
		InstructionMod* modIns = (InstructionMod*)ins;
		string col1, val1, col2, val2;
		modIns->GetColumnData(col1, val1, col2, val2);
		ret = mod->execute(modIns->GetOption1(), modIns->GetOption2(), col1, val1, col2, val2, resultSet);
		delete mod;
		return ret;
	}
};

class EmployeeManager {
public:
	EmployeeManager() {}
	int run(string inputFIleName, string outputFileName);
private:
	void writeToOutputFile(OP_CODE opCode, bool isPOption, OutputToFile* output, vector<EmployeeInfo>& resultSet, int result);
};
