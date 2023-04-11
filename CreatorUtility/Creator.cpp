#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Employee.h"

Employee* readEmployeeFromConsole();
void writeEmployeeToStream(Employee* employee, std::ostream& out);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <filename> <number of records>" << std::endl;
    return 1;
  }

  std::cout << "CREATOR started work\n";
  const char* fileName = argv[1];
  const int recordsNum = std::stoi(argv[2]);

  if (recordsNum <= 0) {
    std::cerr << "Error: The number of records must be positive" << std::endl;
    return 1;
  }

  std::ofstream output(fileName, std::ios::out | std::ios::binary);

  for (int i = 0; i < recordsNum; i++) {
    Employee* employee = readEmployeeFromConsole();
    writeEmployeeToStream(employee, output);
    writeEmployeeToStream(employee, std::cout);
    delete employee;
  }

  output.close();

  std::cout << "CREATOR ended work\n\n";
  return 0;
}

Employee* readEmployeeFromConsole() {
  Employee* employee = new Employee();

  std::cout << "Please enter employee id: ";
  std::cin >> employee->num;

  std::cout << "Please enter employee name: ";
  std::cin >> employee->name;

  std::cout << "Please enter employee working hours: ";
  std::cin >> employee->hours;

  return employee;
}

void writeEmployeeToStream(Employee* employee, std::ostream& out) {
  out << employee->num << " ";
  out << employee->name << " ";
  out << employee->hours << "\n";
}
