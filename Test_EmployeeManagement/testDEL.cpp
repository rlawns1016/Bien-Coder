#include "pch.h"
#include "../EmployeeManagement/IDEL.h"

TEST(DELCase, DELByName) {

	list <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	IDEL* del = new DEL(new Finder(employees), employees);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = del->execute("-p", "", "emplyeeNum", "00123456", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 1);
	EXPECT_EQ(employees.size(), 4);

	resultCnt = del->execute("-p", "-l", "name", "GOLDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GOLDONG");
	EXPECT_EQ(resultSet[1].name.last, "GOLDONG");
	EXPECT_EQ(resultCnt, 2);
	EXPECT_EQ(employees.size(), 2);

	resultCnt = del->execute("-p", "-l", "name", "GILDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultSet[1].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 2);
	EXPECT_EQ(employees.size(), 0);


	resultCnt = del->execute("-p", "-f", "name", "HONG", resultSet);
	EXPECT_EQ(resultCnt, 0);

}