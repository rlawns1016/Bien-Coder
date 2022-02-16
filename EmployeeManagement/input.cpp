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

OP_CODE InputFromFile::ConvertStrToOpCode(const string& opCode) {
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

CL InputFromFile::ConvertStrToCl(const string& cl) {
	if ("CL1" == cl)
		return CL::CL1;
	else if ("CL2" == cl)
		return CL::CL2;
	else if ("CL3" == cl)
		return CL::CL3;
	else if ("CL4" == cl)
		return CL::CL4;
}

CERTI InputFromFile::ConvertStrToCerti(const string& certi) {
	if ("ADV" == certi)
		return CERTI::ADV;
	else if ("PRO" == certi)
		return CERTI::PRO;
	else if ("EX" == certi)
		return CERTI::EX;
}

bool InputFromFile::ReadLine(Instruction** ins) {
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
		result = CreateInstructionAdd(ins, opCode, option1, option2, payload);
		break;
	
	case OP_CODE::DEL :
		result = CreateInstructionDel(ins, opCode, option1, option2, payload);
		break;

	case OP_CODE::MOD :
		result = CreateInstructionMod(ins, opCode, option1, option2, payload);
		break;

	case OP_CODE::SCH :
		result = CreateInstructionSch(ins, opCode, option1, option2, payload);
		break;

	default:
		return false;
	}

	return result;
}

bool InputFromFile::CreateInstructionAdd(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {
	EmployeeInfo e;
	string payloadSubStr = payload;
	size_t payloadLength = payload.length();
	size_t payloadPos;

	//��� �տ� "19" �ٿ��� ��� ���� �����ϰ� ����
	payloadPos = payloadSubStr.find(',');
	string employeeNum = "19" + payloadSubStr.substr(0, payloadPos);
	e.employeeNum = atoi(employeeNum.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find(' ');
	string firstName = payloadSubStr.substr(0, payloadPos);
	e.name.first = atoi(firstName.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find(',');
	string lastName = payloadSubStr.substr(0, payloadPos);
	e.name.last = atoi(lastName.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find(',');
	string cl = payloadSubStr.substr(0, payloadPos);
	e.cl = ConvertStrToCl(cl);
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	// ��ȭ��ȣ 010- �� skip
	payloadPos = payloadSubStr.find('-');
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find('-');
	string midPhoneNum = payloadSubStr.substr(0, payloadPos);
	e.phoneNum.mid = atoi(midPhoneNum.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find(',');
	string endPhoneNum = payloadSubStr.substr(0, payloadPos);
	e.phoneNum.end = atoi(endPhoneNum.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);

	payloadPos = payloadSubStr.find(',');
	string birthday = payloadSubStr.substr(0, payloadPos);
	e.birthday.y = atoi(birthday.substr(0, 4).c_str());
	e.birthday.m = atoi(birthday.substr(4, 2).c_str());
	e.birthday.d = atoi(birthday.substr(6, 2).c_str());
	string certi = payloadSubStr.substr(payloadPos + 2, payloadLength - payloadPos - 2);
	e.certi = ConvertStrToCerti(certi);

	insAdd.SetInstruction(opCode, option1, option2, e);

	*ins = &insAdd;

	return true;;
}

bool InputFromFile::CreateInstructionDel(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {

	return false;
}

bool InputFromFile::CreateInstructionMod(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {

	return false;
}

bool InputFromFile::CreateInstructionSch(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {

	return false;
}
