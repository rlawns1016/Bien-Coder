#pragma once

#include "mainFrame.h"

enum class OP_CODE {
	ADD,
	DEL,
	SCH,
	MOD,
	UNKNOWN
};

enum class OPTION_1 {
	PRINT_EMPTY,
	PRINT_WITH_5RECORD,
	PRINT_UNKNOWN
};

enum class OPTION_2 {
	CONDITION_EMPTY,
	CONDITION_BY_FIRSTNAME,
	CONDITION_BY_LASTNAME,
	CONDITION_BY_MIDPHONENUM,
	CONDITION_BY_LASTPHONENUM,
	CONDITION_BY_YEAR,
	CONDITION_BY_MONTH,
	CONDITION_BY_DAY,
	CONDITION_UNKNOWN
};

enum class COLUMN_NAME {
	CN_EMPLOYEE_NUM,
	CN_NAME,
	CN_CL,
	CN_PHONE_NUM,
	CN_BIRTHDAY,
	CN_CERTI,
	CN_UNKNOWN
};



class Instruction {
public:
	OP_CODE GetOperationCode();
	OPTION_1 GetPrintOption();
	OPTION_2 GetCondition();

protected:
	OP_CODE operationCode_;
	OPTION_1 print_;
	OPTION_2 condition_;
};

class InstructionAdd : public Instruction {
public:
	void SetInstruction(const OP_CODE op, const OPTION_1 opt1, const OPTION_2 opt2, const EmployeeInfo& e);
	void GetEmployeeInfo(EmployeeInfo& e);

private:
	EmployeeInfo employee_;
};

class InstructionDel : public Instruction {

private:
	COLUMN_NAME columnName_;
	string columnValue_;
};

class InstructionSch : public Instruction {

private:
	COLUMN_NAME columnName_;
	string columnValue_;
};

class InstructionMod : public Instruction {

private:
	COLUMN_NAME columnName1st_;
	string columnValue1st_;
	COLUMN_NAME columnName2nd_;
	string columnValue2nd_;
};


struct Input {
	virtual bool Open(string path) = 0;
	virtual bool ReadLine(Instruction* ins) = 0; // �� �پ� ��� ������ �о ins�� ������ ä���ش�. ���� �� true ����, EOF ���� �� false ����.
};
