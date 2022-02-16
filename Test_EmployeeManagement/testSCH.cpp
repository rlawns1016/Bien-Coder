#include "pch.h"
#include "../EmployeeManagement/ISCH.h"

TEST(SCHCase, SearchTest) {

	list <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	ISCH* sch = new SCH(new Finder(employees));
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = sch->execute("-p", "", "employeeNum", "00123456", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("-p", "-l", "name", "GILDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultSet[1].name.last, "GILDONG");
	EXPECT_EQ(resultSet[2].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 3);

	resultCnt = sch->execute("-p", "-f", "name", "HONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("", "", "name", "HONG GILDONG", resultSet);
	EXPECT_EQ(resultCnt, 1);

}