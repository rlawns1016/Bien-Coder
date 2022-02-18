#include "pch.h"
#include "../EmployeeManagement/EmployeeResultSet.h"

TEST(EmployeeResultSetCase, insertSort) {

	EmployeeResultSet rsltSet;
	rsltSet.insert({ 1999000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 2001000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 1997000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 1998000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 2021000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 2022000000, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	rsltSet.insert({ 1997000001, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });

	vector<EmployeeInfo> vectorRslt;
	rsltSet.toVector(vectorRslt);

	EXPECT_EQ(vectorRslt.size(), 5);
	EXPECT_EQ(vectorRslt[0].employeeNum, 1997000000);
	EXPECT_EQ(vectorRslt[1].employeeNum, 1997000001);
	EXPECT_EQ(vectorRslt[2].employeeNum, 1998000000);
	EXPECT_EQ(vectorRslt[3].employeeNum, 1999000000);
	EXPECT_EQ(vectorRslt[4].employeeNum, 2001000000);


}