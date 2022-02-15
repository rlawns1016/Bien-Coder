#include "pch.h"
#include "../EmployeeManagement/ISCH.h"

#if 0
TEST(SearchCase, SearchByName) {

	//input...
	vector <EmployeeInfo> employees;
	employees.push_back({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	employees.push_back({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	employees.push_back({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	//SCH 持失
	ISCH* sch = new NaiveSCH(employees);
	vector <EmployeeInfo*> result;

	result = sch->searchByFirstName("KIM");
	EXPECT_EQ(result[0]->name.first, "KIM");

	result = sch->searchByLastName("GILDONG");
	EXPECT_EQ(result.size(), 3);

	result = sch->searchByFirstName("PARK");
	EXPECT_EQ(result.size(), 0);
}
#endif


TEST(ModeCase, SearchByName) {

	//input...
	vector <EmployeeInfo> employees;

	employees.push_back({ 1991351446, {"LIM", "PNQN"},CL::CL3,{6094,6223},{1997,1,22},CERTI::PRO });
	employees.push_back({ 1993916535, {"JANG","YHFQ"},CL::CL3,{1509,9243},{1958,05,25},CERTI::PRO });
	employees.push_back({ 2007843022, {"SEO", "FKI" },CL::CL3,{4837,6716},{1981,6,30},CERTI::ADV });

	//SCH 持失
	ISCH* sch = new NaiveSCH(employees);
	vector <EmployeeInfo*> result;

	result = sch->searchByFirstName("LIM");
	EXPECT_EQ(result[0]->name.first, "LIM");

	result = sch->searchByLastName("YHFQ");
	EXPECT_EQ(result.size(), 1);

	result = sch->searchByFirstName("SEU");
	EXPECT_EQ(result.size(), 0);
}

