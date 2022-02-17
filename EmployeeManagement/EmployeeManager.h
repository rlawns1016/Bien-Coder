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

	int run(string inputFIleName, string outputFileName)
	{
		int ret = ERROR_CODE_NO_ERROR;
		//input
		Instruction* ins = nullptr;
		InputFromFile* input = new InputFromFile();
		bool isInputFileOpen = input->Open(inputFIleName);
		//output
		OutputToFile* output = new OutputToFile();
		bool isOutputFileOpen = output->Open(outputFileName);
		//db
		IDataBase* db = new DataBase();
		vector<EmployeeInfo> result;
		
		//module
		IADD* add = new ADD(db);
		IDEL* del = new DEL(db);
		ISCH* sch = new SCH(db);
		IMOD* mod = new MOD(db);

		if (!isInputFileOpen || !isOutputFileOpen)	ret = ERROR_CODE_CANNOT_OPEN_FILE;
		else
		{
			while (input->ReadLine(&ins))
			{
				switch (ins->GetOperationCode())
				{
				case OP_CODE::ADD:
				{
					InstructionAdd* addIns = (InstructionAdd*)ins;
					EmployeeInfo info;
					addIns->GetEmployeeInfo(info);
					add->execute(info);
					break;
				}
				case OP_CODE::DEL:
				{
					InstructionDel* delIns = (InstructionDel*)ins;
					string columnName, columnValue;
					vector<EmployeeInfo> resultSet;
					delIns->GetColumnData(columnName, columnValue);
					int ret = del->execute(delIns->GetOption1(), delIns->GetOption2(), columnName, columnValue, resultSet);				
					if (delIns->GetOption1() == "-p")
					{
						output->WriteLine(OP_CODE::DEL, resultSet);
					}
					else
					{
						output->WriteLine(OP_CODE::DEL, ret);
					}
					break;
				}
				case OP_CODE::SCH:
				{
					InstructionSch* schIns = (InstructionSch*)ins;
					string columnName, columnValue;
					vector<EmployeeInfo> resultSet;
					schIns->GetColumnData(columnName, columnValue);
					int ret = sch->execute(schIns->GetOption1(), schIns->GetOption2(), columnName, columnValue, resultSet);

					if (schIns->GetOption1() == "-p")
					{
						output->WriteLine(OP_CODE::SCH, resultSet);
					}
					else
					{
						output->WriteLine(OP_CODE::SCH, ret);
					}
					break;
				}
				case OP_CODE::MOD:
				{
					InstructionMod* modIns = (InstructionMod*)ins;
					string col1, val1, col2, val2;
					vector<EmployeeInfo> resultSet;
					modIns->GetColumnData(col1, val1, col2, val2);
					int ret = mod->execute(modIns->GetOption1(), modIns->GetOption2(), col1, val1, col2, val2, resultSet);

					if (modIns->GetOption1() == "-p")
					{
						output->WriteLine(OP_CODE::MOD, resultSet);
					}
					else
					{
						output->WriteLine(OP_CODE::MOD, ret);
					}
					break;
				}
				default:
					ret = ERROR_CODE_INVALID_INSTRUCTION;
					break;
				}
			}
		}
		
		input->Close();
		output->Close();

		return ret;
	}


private:

};