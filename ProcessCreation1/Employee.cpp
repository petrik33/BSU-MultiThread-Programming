#include "Employee.h"

Employee* readEmployeeFromStream(std::istream& in)
{
    Employee* employee = new Employee();
    in >> employee->num;
    in >> employee->name;
    in >> employee->hours;
    return employee;
}

Employee* readEmployeeFromConsole()
{
    Employee* employee = new Employee();

    std::cout << "Please enter employee id: ";
    std::cin >> employee->num;

    std::cout << "Please enter employee name: ";
    std::cin >> employee->name;

    std::cout << "Please enter employee working hours: ";
    std::cin >> employee->hours;
}
