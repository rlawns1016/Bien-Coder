#include "pch.h"
#include "../EmployeeManagement/ISCH.h"

TEST(SCHCase, byName) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = sch->execute("-p", "", "employeeNum", "00123456", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("-p", "-l", "name", "GILDONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultSet[1].name.last, "GILDONG");
	EXPECT_EQ(resultSet[2].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 3);

	resultCnt = sch->execute("-p", "-f", "name", "HONG", resultSet);
	EXPECT_EQ(resultSet[0].name.last, "GILDONG");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("", "", "name", "HONG GILDONG", resultSet);
	EXPECT_EQ(resultCnt, 1);
}

TEST(SCHCase, byCL) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = sch->execute("-p", "", "cl", "CL2", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "HONG");
	EXPECT_EQ(resultCnt, 1);

	db->add({ 2022123456, {"CHOI","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	resultCnt = sch->execute("", "", "cl", "CL2", resultSet);
	EXPECT_EQ(resultCnt, 2);
}

TEST(SCHCase, byPhoneNum) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,1},CERTI::EX });

	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = sch->execute("-p", "", "phoneNum", "010-1235-5678", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "HONG");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("-p", "-l", "phoneNum", "5678", resultSet);
	EXPECT_EQ(resultCnt, 3);

	resultCnt = sch->execute("-p", "-m", "phoneNum", "1235", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "HONG");
	EXPECT_EQ(resultCnt, 1);
}

TEST(SCHCase, byBirth) {

	IDataBase* db = new DataBase();
	db->add({ 2000123456, {"KIM","GILDONG"},CL::CL1,{1234,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2001123456, {"HONG","GILDONG"},CL::CL2,{1235,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2002123456, {"CHOI","GILDONG"},CL::CL3,{1236,5678},{1992,1,2},CERTI::EX });

	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	resultCnt = sch->execute("-p", "", "birthday", "19900101", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("-p", "-y", "birthday", "1991", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "HONG");
	EXPECT_EQ(resultCnt, 1);

	resultCnt = sch->execute("-p", "-m", "birthday", "01", resultSet);
	EXPECT_EQ(resultCnt, 3);

	resultCnt = sch->execute("-p", "-d", "birthday", "01", resultSet);
	EXPECT_EQ(resultSet[0].name.first, "KIM");
	EXPECT_EQ(resultCnt, 2);
}