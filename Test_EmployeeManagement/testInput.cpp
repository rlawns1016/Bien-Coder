#include "pch.h"
#include "../EmployeeManagement/input.h"
#include "../EmployeeManagement/input.cpp"

TEST(InputTest, InstructionAddClassTest) {
	OP_CODE inputOp = OP_CODE::ADD;
	OPTION_1 inputOption1 = OPTION_1::PRINT_EMPTY;
	OPTION_2 inputOption2 = OPTION_2::CONDITION_EMPTY;
	EmployeeInfo inputEmployee = { 2000123456,{ "GILDONG", "KIM" },CL::CL1,{ 1234,5678 },{ 1990,1,1 },CERTI::ADV };
	InstructionAdd* ins = new InstructionAdd();
	bool resultSetInstruction = ins->SetInstruction(inputOp, inputOption1, inputOption2, inputEmployee);
	EmployeeInfo outputEmployee;
	bool resultGetEmployeeInfo = ins->GetEmployeeInfo(outputEmployee);
	EXPECT_EQ(true, resultSetInstruction);
	EXPECT_EQ(true, resultGetEmployeeInfo);
	EXPECT_EQ(inputOp, ins->GetOperationCode());
	EXPECT_EQ(inputOption1, ins->GetPrintOption());
	EXPECT_EQ(inputOption2, ins->GetCondition());
	EXPECT_EQ(inputEmployee.employeeNum, outputEmployee.employeeNum);
	EXPECT_EQ(inputEmployee.name.first, outputEmployee.name.first);
	EXPECT_EQ(inputEmployee.cl, outputEmployee.cl);
	EXPECT_EQ(inputEmployee.phoneNum.mid, outputEmployee.phoneNum.mid);
	EXPECT_EQ(inputEmployee.phoneNum.end, outputEmployee.phoneNum.end);
	EXPECT_EQ(inputEmployee.birthday.y, outputEmployee.birthday.y);
	EXPECT_EQ(inputEmployee.birthday.m, outputEmployee.birthday.m);
	EXPECT_EQ(inputEmployee.birthday.d, outputEmployee.birthday.d);
	EXPECT_EQ(inputEmployee.certi, outputEmployee.certi);
	delete ins;
}
