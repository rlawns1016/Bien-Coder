#pragma once
#include <fstream>
#include <vector>
#include "mainFrame.h"

class OutputToFile {
public:
	bool Open(string path);
	bool Close();
	bool WriteLine(OP_CODE opCode, int resultCnt);
	bool WriteLine(OP_CODE opCode, vector<EmployeeInfo>& resultSet);
private:
	string ConvertOpCodeToStr(const OP_CODE opCode);
	string ConvertEmployeeNumToStr(const int employeeNum);
	string ConvertCltoStr(const CL cl);
	string ConvertPhoneNumberToStr(const int mid, const int end);
	string ConvertBirthdayToStr(const int year, const int month, const int day);
	string ConvertCertiToStr(const CERTI certi);
	ifstream fileStream;
};