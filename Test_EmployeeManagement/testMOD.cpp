#include "pch.h"
#include "../EmployeeManagement/IMOD.h"

TEST(MODCase, ByName) {

	list <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	employees.push_back({ 1991351446, {"LIM", "PNQN"},CL::CL3,{6094,6223},{1997,1,22},CERTI::PRO });
	employees.push_back({ 1993916535, {"JANG","YHFQ"},CL::CL3,{1509,9243},{1958,05,25},CERTI::PRO });
	employees.push_back({ 2007843022, {"SEO", "FKI" },CL::CL3,{4837,6716},{1981,6,30},CERTI::ADV });


	IMOD* mod = new MOD(new Finder(employees), employees);
	vector<EmployeeInfo> resultSet;
	int resultCnt;
	
	resultCnt = mod->execute("-p", "", "emplyeeNum", "00123456", resultSet);	
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 1);
	EXPECT_EQ(employees.size(), 7);
	
	resultCnt = mod->execute("-p", "-l", "name", "GOLDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GOLDONG");	
	EXPECT_EQ(resultSet[1].name.last, "GOLDONG");
	EXPECT_EQ(resultCnt, 2);
	EXPECT_EQ(employees.size(), 5);
	
	resultCnt = mod->execute("-p", "-l", "name", "GILDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultSet[1].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 3);
	EXPECT_EQ(employees.size(), 3);	

	resultCnt = mod->execute("-p", "-f", "name", "HONG", resultSet);
	EXPECT_EQ(resultCnt, 1);
}