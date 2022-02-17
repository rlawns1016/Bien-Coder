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
#define ERROR_CODE_CANNOT_READ_LINE		-3

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
					//virtual int execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet)
					//del->execute(delIns->GetOption1(), delIns->GetOption2(), "", string param, vector<EmployeeInfo>& resultSet)
					//save result to outputFile
					break;
				}
				case OP_CODE::SCH:
				{
					ISCH* sch = new SCH(db);
					InstructionSch* schIns = (InstructionSch*)ins;
					//execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet)
					//sch->execute(~);
					//save result to outputFile
					break;
				}
				case OP_CODE::MOD:
				{
					IMOD* mod = new MOD(db);
					InstructionMod* modIns = (InstructionMod*)ins;
					EmployeeInfo info;
					//execute(string option1, string option2, string column, string param, vector<EmployeeInfo>& resultSet, const EmployeeInfo& info)
					//mod->execute(~);
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