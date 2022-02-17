#pragma once
#include <fstream>
#include "mainFrame.h"

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
	string GetOption1();
	string GetOption2();
	virtual void GetEmployeeInfo(EmployeeInfo& e) = 0;
	virtual void GetColumnData(string& columnName, string& columnValue) = 0;
	virtual void GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) = 0;

protected:
	void SetInstruction(const OP_CODE op, const string opt1, const string opt2);
	OP_CODE operationCode_;
	string option1_;
	string option2_;
};

class InstructionAdd : public Instruction {
public:
	void SetInstruction(const OP_CODE op, const string opt1, const string opt2, const EmployeeInfo& e);
	virtual void GetEmployeeInfo(EmployeeInfo& e) override;

public:
	virtual void GetColumnData(string& columnName, string& columnValue) override { throw exception(); }
	virtual void GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) override { throw exception(); }

private:
	EmployeeInfo employee_;
};

class InstructionDel : public Instruction {
public:
	void SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName, const string cValue);
	virtual void GetColumnData(string& columnName, string& columnValue) override;

public:
	virtual void GetEmployeeInfo(EmployeeInfo& e) override { throw exception(); }
	virtual void GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) override { throw exception(); }

private:
	string columnName_;
	string columnValue_;
};

class InstructionSch : public Instruction {
public:
	void SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName, const string cValue);
	virtual void GetColumnData(string& columnName, string& columnValue) override;

public:
	virtual void GetEmployeeInfo(EmployeeInfo& e) override { throw exception(); }
	virtual void GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) override { throw exception(); }

private:
	string columnName_;
	string columnValue_;
};

class InstructionMod : public Instruction {
public:
	void SetInstruction(const OP_CODE op, const string opt1, const string opt2, const string cName1, const string cValue1, const string cName2, const string cValue2);
	virtual void GetColumnData(string& columnName1st, string& columnValue1st, string& columnName2nd, string& columnValue2nd) override;

public:
	virtual void GetEmployeeInfo(EmployeeInfo& e) override { throw exception(); }
	virtual void GetColumnData(string& columnName, string& columnValue) override { throw exception(); }

private:
	string columnName1st_;
	string columnValue1st_;
	string columnName2nd_;
	string columnValue2nd_;
};

class InputFromFile {
public:
	bool Open(string path);
	bool Close();
	bool ReadLine(Instruction** ins); // 한 줄씩 명령 라인을 읽어서 ins에 내용을 채워준다. 성공 시 true 리턴, EOF 도달 시 false 리턴.

private:
	OP_CODE ConvertStrToOpCode(const string& opCode);
	CL ConvertStrToCl(const string& cl);
	CERTI ConvertStrToCerti(const string& certi);
	bool CreateInstructionAdd(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload);
	bool CreateInstructionDel(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload);
	bool CreateInstructionMod(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload);
	bool CreateInstructionSch(Instruction** ins, const OP_CODE opCode, const string& option1, const string& option2, const string& payload);
	InstructionAdd insAdd;
	InstructionDel insDel;
	InstructionMod insMod;
	InstructionSch insSch;
	ifstream fileStream;
};