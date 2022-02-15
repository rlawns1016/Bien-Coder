#pragma once

#include "mainFrame.h"

enum {
	ADD = 1,
	DEL,
	SCH,
	MOD
} OP_CODE;

enum {
	NO_PRINT = 1,
	PRINT_WITH_5RECORD
} OPTION_1;

enum {
	CONDITION_EMPTY = 1,
	CONDITION_BY_FIRSTNAME,
	CONDITION_BY_LASTNAME,
	CONDITION_BY_MIDPHONENUM,
	CONDITION_BY_LASTPHONENUM,
	CONDITION_BY_YEAR,
	CONDITION_BY_MONTH,
	CONDITION_BY_DAY
} OPTION_2;

enum {
	CN_EMPLOYEE_NUM = 1,
	CN_NAME,
	CN_CL,
	CN_PHONE_NUM,
	CN_BIRTHDAY,
	CN_CERTI
} COLUMN_NAME;



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
	virtual bool ReadLine(Instruction* ins) = 0; // 한 줄씩 명령 라인을 읽어서 ins에 내용을 채워준다. 성공 시 true 리턴, EOF 도달 시 false 리턴.
};
