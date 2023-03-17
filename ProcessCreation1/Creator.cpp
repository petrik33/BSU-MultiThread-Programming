#include "Creator.h"

namespace creator {

DWORD __stdcall Creator(LPVOID iCreatorProps) {
  ICreatorProps* props = static_cast<ICreatorProps*>(iCreatorProps);
  std::ofstream output(props->fileName, std::ios::out | std::ios::binary);

  for (int i = 0; i < props->recordsNum; i++) {
    Employee* employee = readEmployeeFromConsole();
    writeEmployeeToStream(employee, output);
    // Debug
    writeEmployeeToStream(employee, std::clog);
  }

  output << "\n";
  output.close();
}

Employee* readEmployeeFromConsole() {
  Employee* employee = new Employee();

  std::cout << "Please enter employee id: ";
  std::cin >> employee->num;

  std::cout << "Please enter employee name: ";
  std::cin >> employee->name;

  std::cout << "Please enter employee working hours: ";
  std::cin >> employee->hours;
}

void writeEmployeeToStream(Employee* employee, std::ostream& out) {
  out << employee->num << " ";
  out << employee->name << " ";
  out << employee->hours << "\n";
}

}  // namespace creator
