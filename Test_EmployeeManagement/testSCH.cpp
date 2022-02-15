#include "pch.h"

#include "pch.h"
#include "../EmployeeManagement/ISCH.h"

TEST(SearchCase, SearchByName) {

	//input...
	vector <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	//SCH »ý¼º
	ISCH* sch = new NaiveSCH(employees);
	vector <EmployeeInfo*> result;

	result = sch->searchByFirstName("KIM");
	EXPECT_EQ(result[0]->name.first, "KIM");

	result = sch->searchByLastName("GILDONG");
	EXPECT_EQ(result.size(), 3);

	result = sch->searchByFirstName("PARK");
	EXPECT_EQ(result.size(), 0);

}