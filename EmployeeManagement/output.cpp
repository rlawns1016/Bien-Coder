#include "output.h"


bool OutputToFile::Open(string path) {

	return false;
}

bool OutputToFile::Close() {

	return false;
}

bool OutputToFile::WriteLine(OP_CODE opCode, int resultCnt) {

	return false;
}

bool OutputToFile::WriteLine(OP_CODE opCode, vector<EmployeeInfo>& resultSet) {

	return false;
}

string OutputToFile::ConvertOpCodeToStr(const OP_CODE opCode) {
	
	return "fail case";
}

string OutputToFile::ConvertEmployeeNumToStr(const int employeeNum) {

	return "fail case";
}

string OutputToFile::ConvertCltoStr(const CL cl) {

	return "fail case";
}

string OutputToFile::ConvertPhoneNumberToStr(const int mid, const int end) {

	return "fail case";
}

string OutputToFile::ConvertBirthdayToStr(const int year, const int month, const int day) {

	return "fail case";
}

string OutputToFile::ConvertCertiToStr(const CERTI certi) {

	return "fail case";
}
