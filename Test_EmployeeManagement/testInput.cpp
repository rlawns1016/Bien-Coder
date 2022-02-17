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

TEST(InputTest, InputFromFileClassTest_ADD) {
	string inputPath = "./input_20_20.txt";
	Instruction* outputIns = nullptr;
	InputFromFile* input = new InputFromFile();
	bool resultOpen = input->Open(inputPath);
	bool resultReadLine = input->ReadLine(&outputIns);
	ASSERT_EQ(true, resultOpen);
	ASSERT_EQ(true, resultReadLine);
	ASSERT_NE(nullptr, outputIns);
	EXPECT_EQ(OP_CODE::ADD, outputIns->GetOperationCode());
	EXPECT_EQ(" ", outputIns->GetOption1());
	EXPECT_EQ(" ", outputIns->GetOption2());

	EmployeeInfo e;
	outputIns->GetEmployeeInfo(e);
	EXPECT_EQ(2015123099, e.employeeNum);
	EXPECT_EQ("VXIHXOTH", e.name.first);
	EXPECT_EQ("JHOP", e.name.last);
	EXPECT_EQ(CL::CL3, e.cl);
	EXPECT_EQ(3112, e.phoneNum.mid);
	EXPECT_EQ(2609, e.phoneNum.end);
	EXPECT_EQ(1977, e.birthday.y);
	EXPECT_EQ(12, e.birthday.m);
	EXPECT_EQ(11, e.birthday.d);
	EXPECT_EQ(CERTI::ADV, e.certi);
	input->Close();
	delete input;
}

TEST(InputTest, InputFromFileClassTest_DEL) {
	string inputPath = "./input_DEL.txt";
	Instruction* outputIns = nullptr;
	InputFromFile* input = new InputFromFile();
	bool resultOpen = input->Open(inputPath);
	bool resultReadLine = input->ReadLine(&outputIns);
	ASSERT_EQ(true, resultOpen);
	ASSERT_EQ(true, resultReadLine);
	ASSERT_NE(nullptr, outputIns);
	EXPECT_EQ(OP_CODE::DEL, outputIns->GetOperationCode());
	EXPECT_EQ("-p", outputIns->GetOption1());
	EXPECT_EQ("-l", outputIns->GetOption2());

	string columnName, columnValue;
	outputIns->GetColumnData(columnName, columnValue);
	EXPECT_EQ("name", columnName);
	EXPECT_EQ("MPOSXU", columnValue);
	input->Close();
	delete input;
}

TEST(InputTest, InputFromFileClassTest_MOD) {
	string inputPath = "./input_MOD.txt";
	Instruction* outputIns = nullptr;
	InputFromFile* input = new InputFromFile();
	bool resultOpen = input->Open(inputPath);
	bool resultReadLine = input->ReadLine(&outputIns);
	ASSERT_EQ(true, resultOpen);
	ASSERT_EQ(true, resultReadLine);
	ASSERT_NE(nullptr, outputIns);
	EXPECT_EQ(OP_CODE::MOD, outputIns->GetOperationCode());
	EXPECT_EQ("-p", outputIns->GetOption1());
	EXPECT_EQ(" ", outputIns->GetOption2());

	string columnName1st, columnValue1st, columnName2nd, columnValue2nd;
	outputIns->GetColumnData(columnName1st, columnValue1st, columnName2nd, columnValue2nd);
	EXPECT_EQ("name", columnName1st);
	EXPECT_EQ("FB NTAWR", columnValue1st);
	EXPECT_EQ("birthday", columnName2nd);
	EXPECT_EQ("20050520", columnValue2nd);
	input->Close();
	delete input;
}

TEST(InputTest, InputFromFileClassTest_SCH) {
	string inputPath = "./input_SCH.txt";
	Instruction* outputIns = nullptr;
	InputFromFile* input = new InputFromFile();
	bool resultOpen = input->Open(inputPath);
	bool resultReadLine = input->ReadLine(&outputIns);
	ASSERT_EQ(true, resultOpen);
	ASSERT_EQ(true, resultReadLine);
	ASSERT_NE(nullptr, outputIns);
	EXPECT_EQ(OP_CODE::SCH, outputIns->GetOperationCode());
	EXPECT_EQ("-p", outputIns->GetOption1());
	EXPECT_EQ("-m", outputIns->GetOption2());

	string columnName, columnValue;
	outputIns->GetColumnData(columnName, columnValue);
	EXPECT_EQ("phoneNum", columnName);
	EXPECT_EQ("3112", columnValue);
	input->Close();
	delete input;
}
