#include "input.h"

OP_CODE Instruction::GetOperationCode() {
	return this->operationCode_;
}

OPTION_1 Instruction::GetPrintOption() {
	return this->print_;
}

OPTION_2 Instruction::GetCondition() {
	return this->condition_;
}

void InstructionAdd::SetInstruction(const OP_CODE op, const OPTION_1 opt1, const OPTION_2 opt2, const EmployeeInfo& e) {
	this->operationCode_ = op;
	this->print_ = opt1;
	this->condition_ = opt2;
	this->employee_ = e;
	
}

void InstructionAdd::GetEmployeeInfo(EmployeeInfo& e) {
	e = this->employee_;
}