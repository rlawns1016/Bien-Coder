#include<string>

using namespace std;

#define MAX_RECORD_NUM ((int)1e6)

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

struct EmployeeInfo
{
	unsigned int employeeNum;
	string name;
	CL cl;
	string phoneNum;
	string birthday;
	CERTI certi;
}employTable[MAX_RECORD_NUM]; 


void init() {}
void ADD(string str, ofstream* outputFile) {} 
void SCH(string str, ofstream* outputFile) {}
void DEL(string str, ofstream* outputFile) {}
void MOD(string str, ofstream* outputFile) {}

int getCommandFromLine(string str)
{
	/*
	TODO:
	return CMD number
	*/

	return 0;
}
