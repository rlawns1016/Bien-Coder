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
	vector<EmployeeInfo> resultSet;

	//module
	Module* mod = nullptr;
	AddModule* addModule = new AddModule();
	DelModule* delModule = new DelModule();
	SchModule* schModule = new SchModule();
	ModModule* modModule = new ModModule();


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
				mod = addModule;
				break;
			}
			case OP_CODE::DEL:
			{
				mod = delModule;
				break;
			}
			case OP_CODE::SCH:
			{
				mod = schModule;
				break;
			}
			case OP_CODE::MOD:
			{
				mod = modModule;
				break;
			}
			default:
				ret = ERROR_CODE_INVALID_INSTRUCTION;
				break;
			}
			
			if (ret != ERROR_CODE_NO_ERROR)
			{
				break;
			}
			
			resultCnt = mod->run(db, ins, resultSet);

			writeToOutputFile(opCode, ins->GetOption1() == "-p", output, resultSet, resultCnt);
		}
	}
	input->Close();
	output->Close();

	delete db;
	delete addModule;
	delete delModule;
	delete schModule;
	delete modModule;

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

