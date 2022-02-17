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

void Instruction::SetInstruction(const OP_CODE op, const string opt1, const string opt2) {
	this->operationCode_ = op;
	this->option1_ = opt1;
	this->option2_ = opt2;
}

void InstructionAdd::SetInstruction(const OP_CODE op, const string opt1, const string opt2, const EmployeeInfo& e) {
	Instruction::SetInstruction(op, opt1, opt2);
	this->employee_ = e;
}

void InstructionAdd::GetEmployeeInfo(EmployeeInfo& e) {
	e = this->employee_;
}

void InstructionDel::SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName, const string cValue) {
	Instruction::SetInstruction(op, opt1, opt2);
	this->columnName_ = cName;
	this->columnValue_ = cValue;
}

void InstructionDel::GetColumnData(string& columnName, string& columnValue) {
	columnName = this->columnName_;
	columnValue = this->columnValue_;
}

void InstructionMod::SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName1, const string cValue1, const string cName2, const string cValue2) {
	Instruction::SetInstruction(op, opt1, opt2);
	this->columnName1st_ = cName1;
	this->columnValue1st_ = cValue1;
	this->columnName2nd_ = cName2;
	this->columnValue2nd_ = cValue2;
}

void InstructionMod::GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) {
	columnName1st = this->columnName1st_;
	columnValue1st = this->columnValue1st_;
	columnName2nd = this->columnName2nd_;
	columnValue2nd = this->columnValue2nd_;
}

void InstructionSch::SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName, const string cValue) {
	Instruction::SetInstruction(op, opt1, opt2);
	this->columnName_ = cName;
	this->columnValue_ = cValue;
}

void InstructionSch::GetColumnData(string& columnName, string& columnValue) {
	columnName = this->columnName_;
	columnValue = this->columnValue_;
}


bool InputFromFile::Open(string path) {
	fileStream.open(path);

	if (false == fileStream.is_open())
		return false;

	return true;
}

bool InputFromFile::Close() {
	if (false == fileStream.is_open())
		return false;

	fileStream.close();
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
	readStr = readStr.substr(pos + 1, len - pos - 1);
	
	pos = readStr.find(',');
	option1 = readStr.substr(0, pos);
	readStr = readStr.substr(pos + 1, len - pos - 1);
	
	pos = readStr.find(',');
	option2 = readStr.substr(0, pos);
	readStr = readStr.substr(pos + 1, len - pos - 1);
	
	pos = readStr.find(',');
	option3 = readStr.substr(0, pos);
	payload = readStr.substr(pos + 1, len - pos - 1);
	
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

	//사번 앞 연도 2자리를 4자리로 확장하여, 사번 정렬 용이하게 구성
	payloadPos = payloadSubStr.find(',');
	string employeeNum = payloadSubStr.substr(0, payloadPos);
	e.employeeNum = atoi(employeeNum.c_str());
	if (e.employeeNum >= 69000000) e.employeeNum += 1900000000;
	else e.employeeNum += 2000000000;
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(' ');
	e.name.first = payloadSubStr.substr(0, payloadPos);
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	e.name.last = payloadSubStr.substr(0, payloadPos);
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	string cl = payloadSubStr.substr(0, payloadPos);
	e.cl = ConvertStrToCl(cl);
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	// 전화번호 010- 은 skip
	payloadPos = payloadSubStr.find('-');
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find('-');
	string midPhoneNum = payloadSubStr.substr(0, payloadPos);
	e.phoneNum.mid = atoi(midPhoneNum.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	string endPhoneNum = payloadSubStr.substr(0, payloadPos);
	e.phoneNum.end = atoi(endPhoneNum.c_str());
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	string birthday = payloadSubStr.substr(0, payloadPos);

	e.birthday.y = atoi(birthday.substr(0, 4).c_str());
	e.birthday.m = atoi(birthday.substr(4, 2).c_str());
	e.birthday.d = atoi(birthday.substr(6, 2).c_str());
	string certi = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);
	e.certi = ConvertStrToCerti(certi);

	insAdd.SetInstruction(opCode, option1, option2, e);

	*ins = &insAdd;

	return true;
}

bool InputFromFile::CreateInstructionDel(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {
	string payloadSubStr = payload;
	size_t payloadLength = payload.length();
	size_t payloadPos;

	payloadPos = payloadSubStr.find(',');
	string columnName = payloadSubStr.substr(0, payloadPos);
	string columnValue = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	insDel.SetInstruction(opCode, option1, option2, columnName, columnValue);

	*ins = &insDel;

	return true;
}

bool InputFromFile::CreateInstructionMod(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {
	string payloadSubStr = payload;
	size_t payloadLength = payload.length();
	size_t payloadPos;

	payloadPos = payloadSubStr.find(',');
	string columnName1st = payloadSubStr.substr(0, payloadPos);
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	string columnValue1st = payloadSubStr.substr(0, payloadPos);
	payloadSubStr = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	payloadPos = payloadSubStr.find(',');
	string columnName2nd = payloadSubStr.substr(0, payloadPos);
	string columnValue2nd = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);


	insMod.SetInstruction(opCode, option1, option2, columnName1st, columnValue1st, columnName2nd, columnValue2nd);

	*ins = &insMod;
	return true;
}

bool InputFromFile::CreateInstructionSch(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload) {
	string payloadSubStr = payload;
	size_t payloadLength = payload.length();
	size_t payloadPos;

	payloadPos = payloadSubStr.find(',');
	string columnName = payloadSubStr.substr(0, payloadPos);
	string columnValue = payloadSubStr.substr(payloadPos + 1, payloadLength - payloadPos - 1);

	insSch.SetInstruction(opCode, option1, option2, columnName, columnValue);

	*ins = &insSch;

	return true;
}
