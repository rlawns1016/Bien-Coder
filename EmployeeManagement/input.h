#pragma once

#include "mainFrame.h"

enum OP_CODE {
	ADD = 1,
	DEL,
	SCH,
	MOD
};

enum OPTION_1 {
	NO_PRINT = 1,
	PRINT_WITH_5RECORD
};

enum OPTION_2 {
	CONDITION_EMPTY = 1,
	CONDITION_BY_FIRSTNAME,
	CONDITION_BY_LASTNAME,
	CONDITION_BY_MIDPHONENUM,
	CONDITION_BY_LASTPHONENUM,
	CONDITION_BY_YEAR,
	CONDITION_BY_MONTH,
	CONDITION_BY_DAY
};

enum COLUMN_NAME {
	CN_EMPLOYEE_NUM = 1,
	CN_NAME,
	CN_CL,
	CN_PHONE_NUM,
	CN_BIRTHDAY,
	CN_CERTI
};



class Instruction {

protected :
	enum OP_CODE operationCode_;
	enum OPTION_1 print_;
	enum OPTION_2 condition_;
	enum COLUMN_NAME columnName_;
	string columnValue_;
};

class InstructionAdd : public Instruction {

private : 
	EmployeeInfo employee_;
};

class InstructionDel : public Instruction {

};

class InstructionSch : public Instruction {

};

class InstructionMod : public Instruction {

private :
	enum COLUMN_NAME columnName2nd_;
	string columnValue2nd_;
};


struct Input {
	virtual bool Open(string path) = 0;
	virtual bool ReadLine(Instruction* ins) = 0; // �� �پ� ��� ������ �о ins�� ������ ä���ش�. ���� �� true ����, EOF ���� �� false ����.
};
