#ifndef REPORTER_H_
#define REPORTER_H_

#include <Windows.h>

#include <fstream>
#include <iostream>

#include "../Common/Employee.h"

namespace reporter {

struct IReporterProps {
  char binaryName[50];
  char fileName[50];
  double wage;
};

DWORD WINAPI Reporter(LPVOID iReporterProps);

Employee* readEmployeeFromBinary(std::ifstream& in);
void writeReportLine(Employee* employee, double wage, std::ostream& out);

}  // namespace reporter

#endif  // !REPORTER_H_
