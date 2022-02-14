
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define ERROR_CODE_INVALID_INPUT	-1
#define ERROR_CODE_INVALID_FILE		-2

#define CMD_ADD	1
#define CMD_SCH	2
#define CMD_DEL	3
#define CMD_MOD	4

extern void init();
extern int getCommandFromLine(string str);
extern void ADD(string str, ofstream* outputFile);
extern void SCH(string str, ofstream* outputFile);
extern void DEL(string str, ofstream* outputFile);
extern void MOD(string str, ofstream* outputFile);


int main(int argc, char* argv[])
{
/*
	argv[0] : 실행경로
	argv[1] : Input file name
	argc[2] : Ouput file name
*/
	if (argc != 3)
	{
		printf("ERROR :: INVALID INPUT\n");
		exit(ERROR_CODE_INVALID_INPUT);
	}

	init();
	
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(argv[1], ios::in);
	outputFile.open(argv[2], ios::out);

	if (inputFile.is_open() && outputFile.is_open())
	{
		string str; 
		while (!inputFile.eof())
		{
			getline(inputFile, str);
			switch (getCommandFromLine(str))
			{
			case CMD_ADD:
				ADD(str, &outputFile);
				break;
			case CMD_SCH:
				SCH(str, &outputFile);
				break;
			case CMD_DEL:
				DEL(str, &outputFile);
				break;
			case CMD_MOD:
				MOD(str, &outputFile);
				break;
			default:
					
				break;
			}
		}

		inputFile.close();
		outputFile.close();
	}
	else
	{
		printf("ERROR :: CANNOT OPEN FILE\n");
		exit(ERROR_CODE_INVALID_FILE);
	}


	return 0;
}

