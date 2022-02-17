#pragma once

#include "mainFrame.h"
#include "IADD.h"
#include "ISCH.h"
#include "IDEL.h"
#include "IMOD.h"
#include "input.h"
//#include "output.h"
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
		bool resultOpen = input->Open(inputFIleName);
		
		//output

		//db
		IDataBase* db = new DataBase();
		vector<EmployeeInfo> result;

		if (!resultOpen)	ret = ERROR_CODE_CANNOT_OPEN_FILE;
		else
		{
			while (input->ReadLine(&ins))
			{
				switch (ins->GetOperationCode())
				{
				case OP_CODE::ADD:
				{
					IADD* add = new ADD(db);
					InstructionAdd* addIns = (InstructionAdd*)ins;
					EmployeeInfo info;
					addIns->GetEmployeeInfo(info);
					add->execute(info);
					break;
				}
				case OP_CODE::DEL:
				{
					IDEL* del = new DEL(db);
					InstructionDel* delIns = (InstructionDel*)ins;
					string columnName, columnValue;
					vector<EmployeeInfo> resultSet;
					delIns->GetColumnData(columnName, columnValue);
					int ret = del->execute(delIns->GetOption1(), delIns->GetOption2(), columnName, columnValue, resultSet);
					
					//save result to outputFile
					break;
				}
				case OP_CODE::SCH:
				{
					ISCH* sch = new SCH(db);
					InstructionSch* schIns = (InstructionSch*)ins;
					string columnName, columnValue;
					vector<EmployeeInfo> resultSet;
					schIns->GetColumnData(columnName, columnValue);
					int ret = sch->execute(schIns->GetOption1(), schIns->GetOption2(), columnName, columnValue, resultSet);

					//save result to outputFile
					break;
				}
				case OP_CODE::MOD:
				{
					IMOD* mod = new MOD(db);
					InstructionMod* modIns = (InstructionMod*)ins;
					string columnName, columnValue;
					vector<EmployeeInfo> resultSet;
					modIns->GetColumnData(columnName, columnValue);
					int ret = mod->execute(modIns->GetOption1(), modIns->GetOption2(), columnName, columnValue, resultSet);
					
					//save result to outputFile
					break;
				}
				default:
					ret = ERROR_CODE_INVALID_INSTRUCTION;
					break;
				}
			}
		}

		return ret;
	}


private:	

};