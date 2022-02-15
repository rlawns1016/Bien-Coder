#include "input.h"

OP_CODE Instruction::GetOperationCode() {
	return OP_CODE::UNKNOWN;
}

OPTION_1 Instruction::GetPrintOption() {
	return OPTION_1::PRINT_UNKNOWN;
}

OPTION_2 Instruction::GetCondition() {
	return OPTION_2::CONDITION_UNKNOWN;
}

bool InstructionAdd::SetInstruction(const OP_CODE op, const OPTION_1 opt1, const OPTION_2 opt2, const EmployeeInfo& e) {
	return false;
}

bool InstructionAdd::GetEmployeeInfo(EmployeeInfo& e) {
	return false;
}