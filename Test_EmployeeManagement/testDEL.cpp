#include "pch.h"

#include "pch.h"
#include "../EmployeeManagement/IDEL.h"

TEST(DelCase, DelByName) {

	//input...
	vector <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"}, CL::CL1,{1234,5678}, {1990,1,1}, CERTI::ADV });
	employees.push_back({ 2001123456, {"HONG","GILDONG"}, CL::CL2,{1235,5678}, {1991,1,1}, CERTI::PRO });
	employees.push_back({ 2002123456, {"CHOI","GILDONG"}, CL::CL3,{1236,5678}, {1992,1,1}, CERTI::EX });

	//create DEL obj
	IDEL* d = new NaiveDEL(employees);
	int result;

	result = d->deleteByFirstName("KIM");
	EXPECT_EQ(result, 1);

	result = d->deleteByFirstName("PARK");
	EXPECT_EQ(result, 0);

	result = d->deleteByLastName("GILDONG");
	EXPECT_EQ(result, 2);
}