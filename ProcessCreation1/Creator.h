#pragma once

#include <Windows.h>

#include <fstream>
#include <iostream>

#include "Employee.h"

namespace creator {

struct ICreatorProps {
  char fileName[50];
  int recordsNum;
};

DWORD WINAPI Creator(LPVOID iCreatorProps);

Employee* readEmployeeFromConsole();
void writeEmployeeToStream(Employee* employee, std::ostream& out);

}  // namespace creator
