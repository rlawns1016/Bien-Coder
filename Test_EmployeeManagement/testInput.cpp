#include "pch.h"
#include "../EmployeeManagement/input.h"
#include "../EmployeeManagement/input.cpp"

TEST(InputTest, InstructionAddClassTest) {
	OP_CODE inputOp = OP_CODE::ADD;
	string inputOption1 = " ";
	string inputOption2 = " ";
	EmployeeInfo inputEmployee = { 2000123456,{ "GILDONG", "KIM" },CL::CL1,{ 1234,5678 },{ 1990,1,1 },CERTI::ADV };
	InstructionAdd* ins = new InstructionAdd();
	ins->SetInstruction(inputOp, inputOption1, inputOption2, inputEmployee);
	EmployeeInfo outputEmployee;
	ins->GetEmployeeInfo(outputEmployee);
	EXPECT_EQ(inputOp, ins->GetOperationCode());
	EXPECT_EQ(inputOption1, ins->GetOption1());
	EXPECT_EQ(inputOption2, ins->GetOption2());
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

TEST(InputTest, InputFromFileClassTest) {
	string inputPath = "./input_20_20.txt";
	Instruction outputIns;
	InputFromFile* input = new InputFromFile();
	bool resultOpen = input->Open(inputPath);
	bool resultReadLine = input->ReadLine(outputIns);
	ASSERT_EQ(true, resultOpen);
	ASSERT_EQ(true, resultReadLine);
	EXPECT_EQ(OP_CODE::ADD, outputIns.GetOperationCode());
	EXPECT_EQ("", outputIns.GetOption1());
	EXPECT_EQ("", outputIns.GetOption2());
}
