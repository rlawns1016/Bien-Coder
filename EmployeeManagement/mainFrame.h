#pragma once

#include<string>

using namespace std;

typedef struct
{
	int  mid, end;
}PhoneNumber;

typedef struct
{
	int y, m, d;
}Birthday;

typedef struct
{
	string first, last;
}Name;

typedef enum {
	CL1 = 1,
	CL2,
	CL3,
	CL4,
}CL;

typedef enum {
	ADV = 1,
	PRO,
	EX
}CERTI;

typedef struct 
{
	unsigned int employeeNum;
	Name name;
	CL cl;
	PhoneNumber phoneNum;
	Birthday birthday;
	CERTI certi;
}EmployeeInfo;