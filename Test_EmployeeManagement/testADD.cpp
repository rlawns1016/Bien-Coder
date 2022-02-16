//#include "gtest/gtest.h"
#include "pch.h"
#include "../EmployeeManagement/IADD.h"
#include "../EmployeeManagement/ISCH.h"


TEST(AddCase, AddOnly) {

	//input...
	vector <EmployeeInfo> employees;
	IADD* iADD = new ADD(employees);
	iADD->AddEmployeeInfo({ 2000123456,{ "KIM","GILDONG" },CL::CL1,{ 1234,5678 },{ 1990,1,1 },CERTI::ADV });
	iADD->AddEmployeeInfo({ 2001123456,{ "HONG","GILDONG" },CL::CL2,{ 1235,5678 },{ 1991,1,1 },CERTI::PRO });
	iADD->AddEmployeeInfo({ 2002123456,{ "CHOI","GILDONG" },CL::CL3,{ 1236,5678 },{ 1992,1,1 },CERTI::EX });

	EXPECT_EQ(employees[0].employeeNum, 2000123456);
	EXPECT_EQ(employees[0].phoneNum.mid, 1234);
	EXPECT_EQ(employees[1].name.first, "GILDONG");
	EXPECT_EQ(employees[1].birthday.m, 1);
	EXPECT_EQ(employees[2].cl, CL::CL3);
	EXPECT_EQ(employees[2].certi, CERTI::EX);
	EXPECT_EQ(employees.size(), 3);

	delete iADD;
}

TEST(AddandSearchCase, SearchAfterAdd) {

	vector <EmployeeInfo> employees;
	IADD* iADD = new ADD(employees);
	iADD->AddEmployeeInfo({ 2000123456,{ "GILDONG", "KIM", },CL::CL1,{ 1234,5678 },{ 1990,1,1 },CERTI::ADV });
	iADD->AddEmployeeInfo({ 2001123456,{ "GILDONG", "HONG" },CL::CL2,{ 1235,5678 },{ 1991,1,1 },CERTI::PRO });
	iADD->AddEmployeeInfo({ 2002123456,{ "GILDONG", "CHOI" },CL::CL3,{ 1236,5678 },{ 1992,1,1 },CERTI::EX });

	ISCH* sch = new NaiveSCH(employees);
	vector <EmployeeInfo*> result;
	result = sch->searchByFirstName("GILDONG");
	EXPECT_EQ(result[0]->name.first, "GILDONG");

	result = sch->searchByLastName("HONG");
	EXPECT_EQ(result.size(), 1);

	result = sch->searchByLastName("PARK");
	EXPECT_EQ(result.size(), 0);

	delete iADD;
	delete sch;
}