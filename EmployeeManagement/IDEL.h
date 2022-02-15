#pragma once

#include <vector>
#include "mainFrame.h"
using namespace std;

struct IDEL {
	virtual int deleteByName(Name name) = 0;
	virtual int deleteByFirstName(string name) = 0;
	virtual int deleteByLastName(string name) = 0;
};

class NaiveDEL : public IDEL {
public:
	NaiveDEL(vector<EmployeeInfo>& employee) : employee_(employee) {
	}

	int deleteByName(Name name) override {
		int result = 0;
		for (auto it = employee_.begin(); it != employee_.end(); ) {
			if (it->name.first == name.first && it->name.first == name.last) {
				it = employee_.erase(it);
				result++;
			}
			else {
				it++;
			}
		}
		return result;
	};

	int deleteByFirstName(string name) override {
		int result = 0;
		for (auto it = employee_.begin(); it != employee_.end(); ) {
			if (it->name.first == name) {
				it = employee_.erase(it);
				result++;
			}
			else {
				it++;
			}
		}
		return result;
	};

	int deleteByLastName(string name) override {
		int result = 0;
		for (auto it = employee_.begin(); it != employee_.end(); ) {
			if (it->name.last == name) {
				it = employee_.erase(it);
				result++;
			}
			else {
				it++;
			}
		}
		return result;
	};
private:
	vector<EmployeeInfo>& employee_;
};
