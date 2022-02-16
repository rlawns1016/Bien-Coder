#include "pch.h"
#include "../EmployeeManagement/IADD.h"

TEST(AddCase, AddAndGetFromDB) {

	IDataBase* db = new DataBase();
	IADD* add = new ADD(db);

	add->execute({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	add->execute({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	add->execute({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	add->execute({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	add->execute({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	EXPECT_EQ(db->getEmployeeCount(), 5);
	
	EmployeeInfo* info;
	info = db->getEmployeeInfo(2000123456);
	EXPECT_EQ(info->certi, CERTI::ADV);
	EXPECT_EQ(info->cl, CL::CL1);
	info = db->getEmployeeInfo(2003123456);
	EXPECT_EQ(info->birthday.y, 1990);
	EXPECT_EQ(info->name.first, "KIM");

	delete add;
	delete db;
}
