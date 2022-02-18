#pragma once
#include "mainFrame.h"
#include <list>

struct EmployeeResultSet {
	const static int MAX_RESULT = 5;
	list<EmployeeInfo> result;
		
	int insert(EmployeeInfo info) {

		int cnt = 0;
		for (auto it = result.begin(); it != result.end(); ++it) {
			if (info.employeeNum < it->employeeNum) {
				result.insert(it, info);
				if (result.size() > MAX_RESULT) {
					result.pop_back();
				}
				return true;
			}
			cnt++;
			if (cnt >= MAX_RESULT) {
				return false;
			}
		}

		result.push_back(info);
		return true;
	}

	void toVector(vector<EmployeeInfo>& info) {
		info.clear();
		for (auto it = result.begin(); it != result.end(); ++it) {
			info.push_back(*it);
		}
	}
};