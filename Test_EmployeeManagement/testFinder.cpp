#include "pch.h"
#include "../EmployeeManagement/IFinder.h"


TEST(FinderCase, SearchIterator) {

	list <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	IFinder* sch = new Finder(employees);
	vector <list<EmployeeInfo>::iterator> result;

	result = sch->searchIterator("", "emplyeeNum", "00123456");
	EXPECT_EQ(result[0]->name.first, "KIM");

	result = sch->searchIterator("-l", "name", "GILDONG");
	EXPECT_EQ(result.size(), 3);

	result = sch->searchIterator("-f", "name", "HONG");
	EXPECT_EQ(result.size(), 1);

	result = sch->searchIterator("", "name", "HONG GILDONG");
	EXPECT_EQ(result.size(), 1);

}