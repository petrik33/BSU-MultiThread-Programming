#ifndef CREATOR_H_
#define CREATOR_H_

#include <Windows.h>

#include <fstream>
#include <iostream>

#include "../Common/Employee.h"

namespace creator {

struct ICreatorProps {
  char fileName[50];
  int recordsNum;
};

DWORD WINAPI Creator(LPVOID iCreatorProps);

Employee* readEmployeeFromConsole();
void writeEmployeeToStream(Employee* employee, std::ostream& out);

}  // namespace creator

#endif
