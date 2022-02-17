#include "output.h"
#include <algorithm>

bool OutputToFile::Open(string path) {
	fileStream.open(path);

	if (false == fileStream.is_open())
		return false;

	return true;
}

bool OutputToFile::Close() {
	if (false == fileStream.is_open())
		return false;

	fileStream.close();
	return true;
}

bool OutputToFile::WriteLine(OP_CODE opCode, int resultCnt) {
	if (false == fileStream.is_open())
		return false;

	string opCodeStr = ConvertOpCodeToStr(opCode);
	string resultCntStr;

	if (0 == resultCnt) resultCntStr = "NONE";
	else resultCntStr = to_string(resultCnt);
	
	fileStream << opCodeStr + "," + resultCntStr << endl;
	
	return true;
}

bool compare(EmployeeInfo emp1, EmployeeInfo emp2) {
	return emp1.employeeNum < emp2.employeeNum;
}

bool OutputToFile::WriteLine(OP_CODE opCode, vector<EmployeeInfo>& resultSet) {
	if (false == fileStream.is_open())
		return false;

	string opCodeStr = ConvertOpCodeToStr(opCode);

	if (true == resultSet.empty()) {
		fileStream << opCodeStr + "," + "NONE" << endl;
		return true;
	}

	sort(resultSet.begin(), resultSet.end(), compare);

	for (auto value : resultSet) {
		string eNum = ConvertEmployeeNumToStr(value.employeeNum);
		string name = value.name.last + " " + value.name.first;
		string cl = ConvertCltoStr(value.cl);
		string phoneNum = ConvertPhoneNumberToStr(value.phoneNum.mid, value.phoneNum.end);
		string birthday = ConvertBirthdayToStr(value.birthday.y, value.birthday.m, value.birthday.d);
		string certi = ConvertCertiToStr(value.certi);
		fileStream << opCodeStr + "," + eNum + "," + name + "," + cl + "," + phoneNum + "," + birthday + "," + certi << endl;
	}

	return true;
}

string OutputToFile::ConvertOpCodeToStr(const OP_CODE opCode) {
	if (OP_CODE::ADD == opCode)
		return "ADD";
	else if (OP_CODE::DEL == opCode)
		return "DEL";
	else if (OP_CODE::SCH == opCode)
		return "SCH";
	else if (OP_CODE::MOD == opCode)
		return "MOD";
	else
		return "UNKNOWN";
}

string OutputToFile::ConvertEmployeeNumToStr(const int employeeNum) {
	int eNum = employeeNum;
	if (eNum < 2000000000) eNum -= 1900000000;
	else eNum -= 2000000000;
	string convertStr = to_string(eNum);
	string padding;
	for (int i = 0; i < (8 - convertStr.length()); i++)
		padding += "0";
	return padding + convertStr;
}

string OutputToFile::ConvertCltoStr(const CL cl) {
	if (CL::CL1 == cl)
		return "CL1";
	else if (CL::CL2 == cl)
		return "CL2";
	else if (CL::CL3 == cl)
		return "CL3";
	else if (CL::CL4 == cl)
		return "CL4";

	return "UNKNOWN";
}

string OutputToFile::ConvertPhoneNumberToStr(const int mid, const int end) {
	string convertStrMid = to_string(mid);
	string convertStrEnd = to_string(end);
	string paddingMid, paddingEnd;
	for (int i = 0; i < (4 - convertStrMid.length()); i++)
		paddingMid += "0";
	for (int i = 0; i < (4 - convertStrEnd.length()); i++)
		paddingEnd += "0";
	return "010-" + paddingMid + convertStrMid + "-" + paddingEnd + convertStrEnd;
}

string OutputToFile::ConvertBirthdayToStr(const int year, const int month, const int day) {
	string convertStrYear = to_string(year);
	string convertStrMonth = to_string(month);
	string convertStrDay = to_string(day);
	string paddingYear, paddingMonth, paddingDay;
	for (int i = 0; i < (4 - convertStrYear.length()); i++)
		paddingYear += "0";
	for (int i = 0; i < (2 - convertStrMonth.length()); i++)
		paddingMonth += "0";
	for (int i = 0; i < (2 - convertStrDay.length()); i++)
		paddingDay += "0";
	return paddingYear + convertStrYear + paddingMonth + convertStrMonth + paddingDay + convertStrDay;
}

string OutputToFile::ConvertCertiToStr(const CERTI certi) {
	if (CERTI::ADV == certi)
		return "ADV";
	else if (CERTI::PRO == certi)
		return "PRO";
	else if (CERTI::EX == certi)
		return "EX";

	return "UNKNOWN";
}
