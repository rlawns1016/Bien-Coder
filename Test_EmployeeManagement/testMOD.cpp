#include "pch.h"
#include "../EmployeeManagement/IMOD.h"
#include "../EmployeeManagement/ISCH.h"

TEST(MODCase, ByName) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG1"},CL::CL1,{1,5678},{1990,1,1},CERTI::PRO });
	db->add({ 2001123456, {"KIM","GOLDONG2"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2002123456, {"HONG","GILDONG3"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2003123456, {"KIM","GOLDONG4"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2004123456, {"CHOI","GILDONG5"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });

	IMOD* mod = new MOD(db);	
	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;	

	// 1. certi ����
	EXPECT_EQ(db->getEmployeeInfo(2000123456)->certi, PRO);
	resultCnt = mod->execute("-p", "-l", "name", "GILDONG1", "certi", "EX", resultSet);	
	EXPECT_EQ(db->getEmployeeInfo(2000123456)->certi, EX);

	EXPECT_EQ(db->getEmployeeInfo(2003123456)->cl, CL1);
	resultCnt = mod->execute("-p", "-l", "name", "GOLDONG4", "cl", "CL3", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2003123456)->cl, CL3);

}