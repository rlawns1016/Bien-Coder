#include "input.h"

OP_CODE Instruction::GetOperationCode() {
	return this->operationCode_;
}

string Instruction::GetOption1() {
	return this->option1_;
}

string Instruction::GetOption2() {
	return this->option2_;
}

void InstructionAdd::SetInstruction(const OP_CODE op, const string opt1, const string opt2, const EmployeeInfo& e) {
	this->operationCode_ = op;
	this->option1_ = opt1;
	this->option2_ = opt2;
	this->employee_ = e;
}

void InstructionAdd::GetEmployeeInfo(EmployeeInfo& e) {
	e = this->employee_;
}

bool InputFromFile::Open(string str) {
	fileStream.open(str);

	if (false == fileStream.is_open())
		return false;

	return true;
}

OP_CODE InputFromFile::ConvertStrToOpCode(string opCode) {
	if ("ADD" == opCode)
		return OP_CODE::ADD;
	else if ("DEL" == opCode) 
		return OP_CODE::DEL;
	else if ("SCH" == opCode)
		return OP_CODE::SCH;
	else if ("MOD" == opCode)
		return OP_CODE::MOD;
	else 
		return OP_CODE::UNKNOWN;
}

bool InputFromFile::ReadLine(Instruction& ins) {
	bool result = false;

	if (false == fileStream.is_open())
		return false;
	
	if (true == fileStream.eof())
		return false;

	string readStr;
	OP_CODE opCode;
	string option1, option2, option3, payload;
	size_t pos, len;
	getline(fileStream, readStr);
	len = readStr.length();

	//TODO : invalid input check
	
	pos = readStr.find(',');
	opCode = ConvertStrToOpCode(readStr.substr(0, pos));
	readStr = readStr.substr(pos + 2, len - pos - 2);
	
	pos = readStr.find(',');
	option1 = readStr.substr(0, pos);
	readStr = readStr.substr(pos + 2, len - pos - 2);

	pos = readStr.find(',');
	option2 = readStr.substr(0, pos);
	readStr = readStr.substr(pos + 2, len - pos - 2);

	pos = readStr.find(',');
	option3 = readStr.substr(0, pos);
	payload = readStr.substr(pos + 2, len - pos - 2);

	switch (opCode) {
	case OP_CODE::ADD :
		result = CreateInstructionAdd(ins);
		break;
	
	case OP_CODE::DEL :
		result = CreateInstructionDel(ins);
		break;

	case OP_CODE::MOD :
		result = CreateInstructionMod(ins);
		break;

	case OP_CODE::SCH :
		result = CreateInstructionSch(ins);
		break;

	default:
		return false;
	}

	return result;
}

bool InputFromFile::CreateInstructionAdd(Instruction& ins) {

	return false;
}

bool InputFromFile::CreateInstructionDel(Instruction& ins) {

	return false;
}

bool InputFromFile::CreateInstructionMod(Instruction& ins) {

	return false;
}

bool InputFromFile::CreateInstructionSch(Instruction& ins) {

	return false;
}
