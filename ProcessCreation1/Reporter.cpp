#include "Reporter.h"

namespace reporter {

DWORD __stdcall reporter::Reporter(LPVOID iReporterProps) {
  const IReporterProps* props = static_cast<IReporterProps*>(iReporterProps);
  std::cout << "REPORTER Started\n\n";

  std::ifstream input(props->binaryName, std::ios::in | std::ios::binary);
  std::ofstream output(props->fileName, std::ios::out);

  output << "Report for file " << props->fileName << "\n";

  while (!input.eof()) {
    Employee* employee = readEmployeeFromBinary(input);

    if (!employee) {
      continue;
    }

    writeReportLine(employee, props->wage, output);
    delete employee;
  }

  input.close();
  output.close();

  std::cout << "REPORTER ended work\n\n";

  return 0;
}

Employee* reporter::readEmployeeFromBinary(std::ifstream& in) {
  int num;
  char name[50];
  double hours;

  if (!(in >> num)) {
    return nullptr;
  }

  in >> name;
  in >> hours;

  Employee* employee = new Employee();

  employee->num = num;
  strcpy_s(employee->name, name);
  employee->hours = hours;

  return employee;
}

void reporter::writeReportLine(Employee* employee, double wage,
                               std::ostream& out) {
  double earnedAmount = wage * employee->hours;
  out << employee->num << ", ";
  out << employee->name << ", ";
  out << employee->hours << ", ";
  out << earnedAmount << "\n";
}

}  // namespace reporter
