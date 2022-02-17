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
		IADD* add = new ADD(db);
		InstructionAdd* addIns = (InstructionAdd*)ins;
		EmployeeInfo info;
		addIns->GetEmployeeInfo(info);
		return add->execute(info);
	}
};

class DelModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		IDEL* del = new DEL(db);
		InstructionDel* delIns = (InstructionDel*)ins;
		string columnName, columnValue;
		delIns->GetColumnData(columnName, columnValue);
		return del->execute(delIns->GetOption1(), delIns->GetOption2(), columnName, columnValue, resultSet);
	}
};

class SchModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		ISCH* sch = new SCH(db);
		InstructionSch* schIns = (InstructionSch*)ins;
		string columnName, columnValue;
		schIns->GetColumnData(columnName, columnValue);
		return sch->execute(schIns->GetOption1(), schIns->GetOption2(), columnName, columnValue, resultSet);
	}
};

class ModModule : public Module {
public:
	virtual int run(IDataBase* db, Instruction* ins, vector<EmployeeInfo>& resultSet) override
	{
		IMOD* mod = new MOD(db);
		InstructionMod* modIns = (InstructionMod*)ins;
		string col1, val1, col2, val2;
		modIns->GetColumnData(col1, val1, col2, val2);
		return mod->execute(modIns->GetOption1(), modIns->GetOption2(), col1, val1, col2, val2, resultSet);
	}
};

class EmployeeManager {
public:
	EmployeeManager() {}
	int run(string inputFIleName, string outputFileName);
private:
	void writeToOutputFile(OP_CODE opCode, bool isPOption, OutputToFile* output, vector<EmployeeInfo>& resultSet, int result);
};
