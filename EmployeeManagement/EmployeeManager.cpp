#include "EmployeeManager.h"

int EmployeeManager::run(string inputFIleName, string outputFileName)
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

	if (!isInputFileOpen || !isOutputFileOpen)
	{
		ret = ERROR_CODE_CANNOT_OPEN_FILE;
	}
	else
	{
		while (input->ReadLine(&ins))
		{
			int resultCnt = 0;
			OP_CODE opCode = ins->GetOperationCode();
			switch (opCode)
			{
			case OP_CODE::ADD:
			{
				runAdd(add, ins, output);
				break;
			}
			case OP_CODE::DEL:
			{
				resultCnt = runDel(del, ins, output, result);
				break;
			}
			case OP_CODE::SCH:
			{
				resultCnt = runSch(sch, ins, output, result);
				break;
			}
			case OP_CODE::MOD:
			{
				resultCnt = runMod(mod, ins, output, result);
				break;
			}
			default:
				ret = ERROR_CODE_INVALID_INSTRUCTION;
				break;
			}
			if (ret != ERROR_CODE_NO_ERROR)	break;
			writeToOutputFile(opCode, ins->GetOption1() == "-p", output, result, resultCnt);
		}
	}
	input->Close();
	output->Close();

	return ret;
}

void EmployeeManager::writeToOutputFile(OP_CODE opCode, bool isPOption, OutputToFile* output, vector<EmployeeInfo>& resultSet, int result)
{
	if (opCode == OP_CODE::ADD)	return;
	if (isPOption)
	{
		output->WriteLine(opCode, resultSet);
	}
	else
	{
		output->WriteLine(opCode, result);
	}
}

void EmployeeManager::runAdd(IADD* add, Instruction* ins, OutputToFile* outStream)
{
	InstructionAdd* addIns = (InstructionAdd*)ins;
	EmployeeInfo info;
	addIns->GetEmployeeInfo(info);
	add->execute(info);
}

int EmployeeManager::runDel(IDEL* del, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet)
{
	InstructionDel* delIns = (InstructionDel*)ins;
	string columnName, columnValue;
	delIns->GetColumnData(columnName, columnValue);
	return del->execute(delIns->GetOption1(), delIns->GetOption2(), columnName, columnValue, resultSet);
}

int EmployeeManager::runSch(ISCH* sch, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet)
{
	InstructionSch* schIns = (InstructionSch*)ins;
	string columnName, columnValue;
	schIns->GetColumnData(columnName, columnValue);
	return sch->execute(schIns->GetOption1(), schIns->GetOption2(), columnName, columnValue, resultSet);
}

int EmployeeManager::runMod(IMOD* mod, Instruction* ins, OutputToFile* outStream, vector<EmployeeInfo>& resultSet)
{
	InstructionMod* modIns = (InstructionMod*)ins;
	string col1, val1, col2, val2;
	modIns->GetColumnData(col1, val1, col2, val2);
	return mod->execute(modIns->GetOption1(), modIns->GetOption2(), col1, val1, col2, val2, resultSet);
}
