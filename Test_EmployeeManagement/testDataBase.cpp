#include "pch.h"
#include "../EmployeeManagement/IDEL.h"

TEST(DBCase, Add) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	EXPECT_EQ(db->getEmployeeInfo(2004123456)->name.first, "CHOI");
	EXPECT_EQ(db->getEmployeeInfo(2004123456)->name.last, "GILDONG");
	EXPECT_EQ(db->getEmployeeCount(), 5);
}

TEST(DBCase, Modify) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	EXPECT_EQ(true, db->modify(2002123456, { 2002123456, {"KO","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO }));
	EXPECT_EQ(db->getEmployeeInfo(2002123456)->name.first, "KO");
	EXPECT_EQ(db->getEmployeeCount(), 5);
}

TEST(DBCase, Erase) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"KIM","GOLDONG"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2002123456, {"HONG","GILDONG"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2003123456, {"KIM","GOLDONG"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2004123456, {"CHOI","GILDONG"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	EXPECT_EQ(true, db->erase(2002123456));
	EXPECT_EQ(db->getEmployeeInfo(2002123456), nullptr);
	EXPECT_EQ(db->getEmployeeCount(), 4);
	
}