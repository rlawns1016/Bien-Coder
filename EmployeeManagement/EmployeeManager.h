#pragma once

#include "mainFrame.h"
#include "IADD.h"
#include "ISCH.h"
#include "IDEL.h"
#include "IMOD.h"
#include "input.h"
#include "output.h"
#include<string>

#define ERROR_CODE_NO_ERROR				1
#define ERROR_CODE_INVALID_INSTRUCTION	-1
#define ERROR_CODE_CANNOT_OPEN_FILE		-2

class EmployeeManager {
public:
	EmployeeManager() {}
	
	int run(string inputFIleName, string outputFileName);

private:
	void writeToOutputFile(OP_CODE opCode, bool isPOption, OutputToFile* output, vector<EmployeeInfo>& resultSet, int result);
	void runAdd(IADD* add, Instruction* ins, OutputToFile* outStream);
	int runDel(IDEL* del, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet);
	int runSch(ISCH* sch, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet);
	int runMod(IMOD* mod, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet);
};