#include "pch.h"
#include "../EmployeeManagement/output.h"
#include "../EmployeeManagement/output.cpp"

TEST(OutputTest, OutputToFileClassTest) {
	string outputPath = "./output.txt";
	vector<EmployeeInfo> resultSet1ea, resultSet5ea;
	vector<EmployeeInfo> emptySet;
	OutputToFile* output = new OutputToFile();
	resultSet1ea.push_back({ 2000000001, {"GILDONG", "KIM"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV});
	resultSet5ea.push_back({ 1900000001, {"GILDONG1", "LEE"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	resultSet5ea.push_back({ 1900000002, {"GILDONG2", "LEE"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	resultSet5ea.push_back({ 1900000003, {"GILDONG3", "LEE"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	resultSet5ea.push_back({ 1900000004, {"GILDONG4", "LEE"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	resultSet5ea.push_back({ 1900000005, {"GILDONG5", "LEE"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });

	bool resultOpen = output->Open(outputPath);
	ASSERT_EQ(true, resultOpen);
	bool resultWriteLine = output->WriteLine(OP_CODE::SCH, 0);
	EXPECT_EQ(true, resultWriteLine);
	resultWriteLine = output->WriteLine(OP_CODE::SCH, 1);
	EXPECT_EQ(true, resultWriteLine);
	resultWriteLine = output->WriteLine(OP_CODE::SCH, 11);
	EXPECT_EQ(true, resultWriteLine);
	resultWriteLine = output->WriteLine(OP_CODE::SCH, emptySet);
	EXPECT_EQ(true, resultWriteLine);
	resultWriteLine = output->WriteLine(OP_CODE::SCH, resultSet1ea);
	EXPECT_EQ(true, resultWriteLine);
	resultWriteLine = output->WriteLine(OP_CODE::SCH, resultSet5ea);
	EXPECT_EQ(true, resultWriteLine);
	bool resultClose = output->Close();
	EXPECT_EQ(true, resultClose);

	ifstream resultCheckStream;
	string resultString;
	resultCheckStream.open(outputPath);
	ASSERT_EQ(true, resultCheckStream.is_open());
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,NONE", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,1", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,11", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,NONE", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000001,GILDONG KIM,CL1,010-1234-5678,19900101,ADV", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000001,GILDONG1 LEE,CL1,010-1234-5678,19900101,ADV", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000002,GILDONG2 LEE,CL1,010-1234-5678,19900101,ADV", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000003,GILDONG3 LEE,CL1,010-1234-5678,19900101,ADV", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000004,GILDONG4 LEE,CL1,010-1234-5678,19900101,ADV", resultString);
	getline(resultCheckStream, resultString);
	EXPECT_EQ("SCH,00000005,GILDONG5 LEE,CL1,010-1234-5678,19900101,ADV", resultString);
	resultCheckStream.close();
}