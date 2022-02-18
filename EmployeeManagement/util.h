#pragma once
#include "mainFrame.h"
#include <vector>
#include <sstream>

using namespace std;

namespace Util
{
	static vector<string> split(string str, char delimiter) {
		vector<string> internal;
		stringstream ss(str);
		string temp;
		while (getline(ss, temp, delimiter)) {
			internal.push_back(temp);
		}
		return internal;
	}

	static unsigned int getFullYearEmployeeNum(string employeeNum) {
		int num = stoi(employeeNum);
		return (num >= 69000000) ? num + 1900000000 : num + 2000000000;
	}

	static CL getCL(string cl) {
		if (cl == "CL1") return CL1;
		else if (cl == "CL2") return CL2;
		else if (cl == "CL3") return CL3;
		else if (cl == "CL4") return CL4;
		else throw std::invalid_argument("invalid CL");
	}

	static CERTI getCerti(string certi) {
		if (certi == "ADV") return ADV;
		else if (certi == "PRO") return PRO;
		else if (certi == "EX") return EX;
		else throw std::invalid_argument("invalid CL");
	}
};