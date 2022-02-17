#include "mainFrame.h"
#include "EmployeeManager.h"
#include <sstream>
int main(int argc, char* argv[])
{
	EmployeeManager* manager = new EmployeeManager();

	manager->run(argv[1], argv[2]);
	delete manager;
	return 0;
}

