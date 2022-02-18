#include "pch.h"
#include "../EmployeeManagement/IMOD.h"
#include "../EmployeeManagement/ISCH.h"

TEST(MODCase, ByName) {

	IDataBase* db = new DataBase();
	
	db->add({ 2015123099, {"VXIHXOTH","JHOP"},CL::CL3,{3112,2609},{1977,12,11},CERTI::ADV });
	db->add({ 2017112609, {"FB","NTAWR"},CL::CL4,{5645,6122},{1986,12,03},CERTI::PRO });
	db->add({ 2018115040, {"TTETHU","HBO"},CL::CL3,{4581,2050},{2008,7,18},CERTI::ADV });
	db->add({ 2088114052, {"NQ","LVARW"},CL::CL4,{4528,3059},{1991,10,21},CERTI::PRO });
	db->add({ 2019129568, {"SRERLALH","HMEF"},CL::CL2,{3091,9521},{1964,9,10},CERTI::PRO });
	db->add({ 2017111236, {"VSID","TVO"},CL::CL1,{3669,1077},{2012,7,18},CERTI::PRO });
	db->add({ 2018117906, {"TWU","QSOLT"},CL::CL4,{6672,7186},{2003,4,13},CERTI::PRO });
	db->add({ 1908123556, {"WN","XV"},CL::CL1,{7986,5047},{2010,6,14},CERTI::PRO });
	db->add({ 1902117175, {"SBILHUT","LDEXRI"},CL::CL4,{2814,1699},{1995,07,04},CERTI::ADV });
	db->add({ 1903113260, {"HH","LTUPF"},CL::CL2,{5798,5383},{1979,10,18},CERTI::PRO });
	db->add({ 2014130827, {"RPO","JK"},CL::CL4,{3231,1698},{2009,02,01},CERTI::ADV });
	db->add({ 1901122329, {"DN","WD"},CL::CL4,{7174,5680},{2007,11,17},CERTI::PRO });
	db->add({ 1908108827, {"RTAH","VNUP"},CL::CL4,{9031,2726},{1978,04,17},CERTI::ADV });
	db->add({ 2085125741, {"FBAH","RTIJ"},CL::CL1,{8900,1478},{1978,02,28},CERTI::ADV });
	db->add({ 1908117441, {"BMU","MPOSXU"},CL::CL3,{2703,3153},{2001,02,15},CERTI::ADV });
	db->add({ 2010127115, {"KBU","MHU"},CL::CL3,{3284,4054},{1966,8,14},CERTI::ADV });
	db->add({ 2012117017, {"LFIS","JJIVL"},CL::CL1,{7914,4067},{2012,8,12},CERTI::PRO });
	db->add({ 2011125777, {"TKOQKIS","HC"},CL::CL1,{6734,2289},{1999,10,01},CERTI::PRO });
	db->add({ 2011109136, {"QKAHCEX","LTODDO"},CL::CL4,{2627,8566},{1964,01,30},CERTI::PRO });
	db->add({ 2005101762, {"VCUHLE","HMU"},CL::CL4,{3988,9289},{2003,8,19},CERTI::PRO });

	IMOD* mod = new MOD(db);	
	ISCH* sch = new SCH(db);
	vector<EmployeeInfo> resultSet;
	int resultCnt;

	// 1.Mod Postive Test Case Verification
	// 1.(1) Mod Feature option1 : none
	// 1.(2) Mod Feature option1 : -p

	// 1.(1) Mod Feature option1 : none
	resultCnt = mod->execute("","","name","VXIHXOTH JHOP","name","VXIHXOTH JHOQ",resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099,resultSet); // employeeNum check		
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first,"VXIHXOTH",resultSet); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ", resultSet); // name check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL3, resultSet); // cl check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.mid, 3112, resultSet); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.end, 2609, resultSet); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 1977, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 12, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 11, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, ADV, resultSet); // certi check
	
	// 1.(2) Mod Feature option1 : -p
	resultCnt = mod->execute("-p", "", "name", "VXIHXOTH JHOQ", "name", "VXIHXOTH2 JHOQ2", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099, resultSet); // employeeNum check		
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH2", resultSet); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ2", resultSet); // name check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL3, resultSet); // cl check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.mid, 3112, resultSet); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.end, 2609, resultSet); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 1977, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 12, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 11, resultSet); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, ADV, resultSet); // certi check

																	   
	// 1.(3) Mod Feature option1 : -p + -f
	resultCnt = mod->execute("-p", "-f", "name", "VXIHXOTH", "name", "VXIHXOTH3 JHOQ3", resultSet);	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH2"); // name check, First Name이 VXIHXOTH는 없기 때문에 이름 변경(VXIHXOTH3) 없음.
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ2"); // name check	

	// 1.(4) Mod Feature option1 : -p + -f
	resultCnt = mod->execute("-p", "-f", "name", "VXIHXOTH2", "name", "VXIHXOTH3 JHOQ3", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH3"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ3"); // name check

	// 1.(5) Mod Feature option1 : -p + -l
	resultCnt = mod->execute("-p", "-l", "name", "JHOQ2", "name", "VXIHXOTH4 JHOQ4", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH3"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ3"); // name check

	// 1.(6) Mod Feature option1 : -p + -l
	resultCnt = mod->execute("-p", "-l", "name", "VXIHXOTH4", "name", "VXIHXOTH4 JHOQ4", resultSet); // -l로 검색 + First Name Search
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH3"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ3"); // name check	

	// 1.(7) Mod Feature option1 : -p + -l	
	resultCnt = mod->execute("", "-f", "name", "VXIHXOTH3", "name", "VXIHXOTH4 JHOQ4", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH4"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ4"); // name check

	// 1.(8) Mod Feature option1 : -p + -l	
	resultCnt = mod->execute("-p","-l","name", "JHOQ3", "name", "VXIHXOTH4 JHOQ4", resultSet);	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH4"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ4"); // name check

	// 1.(9) Mod Feature option1 : -p + -m	
	// 3112-2609
	resultCnt = mod->execute("-p", "-m", "phoneNum", "3112", "birthday", "19771212", resultSet);	// ori : 1977,12,11
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH4"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ4"); // name check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL3); // cl check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.mid, 3112); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.end, 2609); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 1977); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 12); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 12); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, ADV); // certi check

	resultCnt = mod->execute("-p", "-l", "phoneNum", "2609", "birthday", "20221113", resultSet);	// ori : 1977,12,12
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 2022); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 11); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 13); // birthday check

	// 1.(10) Mod Feature option1 : -p + -y
	// 3112-2609
	resultCnt = mod->execute("-p", "-y", "birthday", "2022", "certi", "PRO", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check			
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.first, "VXIHXOTH4"); // name check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->name.last, "JHOQ4"); // name check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL3); // cl check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.mid, 3112); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->phoneNum.end, 2609); // phone check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 2022); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 11); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 13); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, PRO); // certi check

	// 1.(10) Mod Feature option1 : -p + -m
	// 3112-2609
	resultCnt = mod->execute("-p", "-m", "birthday", "11", "cl", "CL4", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL4); // cl check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 2022); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 11); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 13); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, PRO); // certi check

	// 1.(10) Mod Feature option1 : -p + -d
	// 3112-2609
	resultCnt = mod->execute("-p", "-d", "birthday", "13", "birthday", "20230101", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->employeeNum, 2015123099); // employeeNum check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->cl, CL4); // cl check	
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.y, 2023); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.m, 1); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->birthday.d, 1); // birthday check
	EXPECT_EQ(db->getEmployeeInfo(2015123099)->certi, PRO); // certi check
	

#if 1	
	db->add({ 2000123456, {"KIM","GILDONG1"},CL::CL1,{1,5678},{1990,1,1},CERTI::PRO });
	db->add({ 2001123456, {"KIM","GOLDONG2"},CL::CL1,{2,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2002123456, {"HONG","GILDONG3"},CL::CL2,{3,5678},{1991,1,1},CERTI::PRO });
	db->add({ 2003123456, {"KIM","GOLDONG4"},CL::CL1,{4,5678},{1990,1,1},CERTI::ADV });
	db->add({ 2004123456, {"CHOI","GILDONG5"},CL::CL3,{5,5678},{1992,1,1},CERTI::EX });
	
	EXPECT_EQ(db->getEmployeeInfo(2000123456)->certi, PRO);
	resultCnt = mod->execute("-p", "-l", "name", "GILDONG1", "certi", "EX", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2000123456)->certi, EX);

	EXPECT_EQ(db->getEmployeeInfo(2003123456)->cl, CL1);
	resultCnt = mod->execute("-p", "-l", "name", "GOLDONG4", "cl", "CL3", resultSet);
	EXPECT_EQ(db->getEmployeeInfo(2003123456)->cl, CL3);
#endif

}