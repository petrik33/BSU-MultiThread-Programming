#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Employee.h"

Employee* readEmployeeFromBinary(std::ifstream& in);
void writeReportLine(Employee* employee, double wage, std::ostream& out);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Error: Expected 3 arguments, but got " << argc - 1
              << std::endl;
    std::cerr << "Usage: " << argv[0] << " <binaryName> <fileName> <wage>"
              << std::endl;
    return 1;
  }
  std::cout << "REPORTER started work\n";
  const char* binaryName = argv[1];
  const char* fileName = argv[2];
  double wage = std::stod(argv[3]);

  std::ifstream input(binaryName, std::ios::in | std::ios::binary);
  std::ofstream output(fileName, std::ios::out);

  output << "Report for file " << fileName << "\n";

  while (!input.eof()) {
    Employee* employee = readEmployeeFromBinary(input);

    if (!employee) {
      continue;
    }

    writeReportLine(employee, wage, output);
    delete employee;
  }

  input.close();
  output.close();

  std::cout << "REPORTER ended work\n\n";

  return 0;
}

Employee* readEmployeeFromBinary(std::ifstream& in) {
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

void writeReportLine(Employee* employee, double wage, std::ostream& out) {
  double earnedAmount = wage * employee->hours;
  out << employee->num << ", ";
  out << employee->name << ", ";
  out << employee->hours << ", ";
  out << earnedAmount << "\n";
}
