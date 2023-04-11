#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Employee.h"

int main(int argc, char* argv[]) {
  std::cout << "CREATOR started work\n\n";
  const char* fileName = argv[1];
  const int recordsNum = std::stoi(argv[2]);

  std::ofstream output(fileName, std::ios::out | std::ios::binary);

  for (int i = 0; i < recordsNum; i++) {
    Employee* employee = readEmployeeFromConsole();
    writeEmployeeToStream(employee, output);
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
