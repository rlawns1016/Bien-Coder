#include "EmployeeManager.h"

#define EXIT_ERROR_CODE_INVALID_INPUT	-1

int main(int argc, char* argv[])
{
	if (argc != 3 || !argv[1] || !argv[2])
	{
		exit(EXIT_ERROR_CODE_INVALID_INPUT);
	}
	int ret = 0;
	EmployeeManager* manager = new EmployeeManager();
	ret = manager->run(argv[1], argv[2]);
	delete manager;
	return ret;
}

