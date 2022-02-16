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
	return false;
}

bool InputFromFile::ReadLine(Instruction* ins) {
	return false;
}
