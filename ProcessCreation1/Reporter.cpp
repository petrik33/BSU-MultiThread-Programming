#include "Reporter.h"

namespace reporter {

DWORD __stdcall reporter::Reporter(LPVOID iReporterProps) {
  const IReporterProps* props = static_cast<IReporterProps*>(iReporterProps);

  std::ifstream input(props->binaryName, std::ios::in | std::ios::binary);
  std::ofstream output(props->fileName, std::ios::out);

  output << "Report for file " << props->fileName << "\n";

  while (!input.eof()) {
    Employee* employee = readEmployeeFromBinary(input);
    writeReportLine(employee, props->wage, output);
    delete employee;
  }

  input.close();
  output.close();

  return 0;
}

Employee* reporter::readEmployeeFromBinary(std::ifstream& in) {
  Employee* employee = new Employee();
  in >> employee->num;
  in >> employee->name;
  in >> employee->hours;
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
