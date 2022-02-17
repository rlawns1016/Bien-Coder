#pragma once

#include "mainFrame.h"
#include "IADD.h"
#include "ISCH.h"
#include "IDEL.h"
#include "IMOD.h"
#include "input.h"
//#include "output.h"
#include <fstream>
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
		ofstream outstream;
		outstream.open(outputFileName, ios::out);

		//module
		IADD* add = new ADD(db);
		IDEL* del = new DEL(db);
		ISCH* sch = new SCH(db);
		IMOD* mod = new MOD(db);

		if (!resultOpen)	ret = ERROR_CODE_CANNOT_OPEN_FILE;
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

					//save result to outputFile		
					string out;
					if (resultSet.empty())
					{
						if (ret == 0)
						{
							out = "DEL,NONE";
						}
						else
						{
							out = "DEL," + to_string(ret);
						}
						outstream << out << endl;
					}
					else
					{
						for (auto e : resultSet)
						{
							out = "DEL," + to_string(e.employeeNum).substr(2,8) + "," + e.name.last + " " + e.name.first + ",";
							switch (e.cl)
							{
							case CL::CL1:
								out += "CL1,";
								break;
							case CL::CL2:
								out += "CL2,";
								break;
							case CL::CL3:
								out += "CL3,";
								break;
							case CL::CL4:
								out += "CL4,";
								break;
							}
							out += "010-" + to_string(e.phoneNum.mid) + "-" + to_string(e.phoneNum.end) + ",";
							out += to_string(e.birthday.y) + to_string(e.birthday.m) + to_string(e.birthday.d) + ",";
							switch (e.certi)
							{
							case CERTI::ADV:
								out += "ADV";
								break;
							case CERTI::PRO:
								out += "PRO";
								break;
							case CERTI::EX:
								out += "EX";
								break;
							}
							outstream << out << endl;
						}
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

					//save result to outputFile
					string out;
					if (resultSet.empty())
					{
						if (ret == 0)
						{
							out = "SCH,NONE";
						}
						else
						{
							out = "SCH," + to_string(ret);
						}
						outstream << out << endl;
					}
					else
					{
						for (auto e : resultSet)
						{
							out = "SCH," + to_string(e.employeeNum).substr(2, 8) + "," + e.name.last + " " + e.name.first + ",";
							switch (e.cl)
							{
							case CL::CL1:
								out += "CL1,";
								break;
							case CL::CL2:
								out += "CL2,";
								break;
							case CL::CL3:
								out += "CL3,";
								break;
							case CL::CL4:
								out += "CL4,";
								break;
							}
							out += "010-" + to_string(e.phoneNum.mid) + "-" + to_string(e.phoneNum.end) + ",";
							out += to_string(e.birthday.y) + to_string(e.birthday.m) + to_string(e.birthday.d) + ",";
							switch (e.certi)
							{
							case CERTI::ADV:
								out += "ADV";
								break;
							case CERTI::PRO:
								out += "PRO";
								break;
							case CERTI::EX:
								out += "EX";
								break;
							}
							outstream << out << endl;
						}
					}
					break;
				}
				case OP_CODE::MOD:
				{
					InstructionMod* modIns = (InstructionMod*)ins;
					string col1, val1, col2, val2;
					vector<EmployeeInfo> resultSet;
					EmployeeInfo info;
					modIns->GetColumnData(col1, val1, col2, val2);
					int ret = mod->execute(modIns->GetOption1(), modIns->GetOption2(), col1, val1, col2, val2, resultSet, info);

					//save result to outputFile
					string out;
					if (resultSet.empty())
					{
						if (ret == 0)
						{
							out = "MOD,NONE";
						}
						else
						{
							out = "MOD," + to_string(ret);
						}
						outstream << out << endl;
					}
					else
					{
						for (auto e : resultSet)
						{
							out = "MOD," + to_string(e.employeeNum).substr(2, 8) + "," + e.name.last + " " + e.name.first + ",";
							switch (e.cl)
							{
							case CL::CL1:
								out += "CL1,";
								break;
							case CL::CL2:
								out += "CL2,";
								break;
							case CL::CL3:
								out += "CL3,";
								break;
							case CL::CL4:
								out += "CL4,";
								break;
							}
							out += "010-" + to_string(e.phoneNum.mid) + "-" + to_string(e.phoneNum.end) + ",";
							out += to_string(e.birthday.y) + to_string(e.birthday.m) + to_string(e.birthday.d) + ",";
							switch (e.certi)
							{
							case CERTI::ADV:
								out += "ADV";
								break;
							case CERTI::PRO:
								out += "PRO";
								break;
							case CERTI::EX:
								out += "EX";
								break;
							}
							outstream << out << endl;
						}
					}
					break;
				}
				default:
					ret = ERROR_CODE_INVALID_INSTRUCTION;
					break;
				}
			}
		}
		
		outstream.close();
		return ret;
	}


private:

};