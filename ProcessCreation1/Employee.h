#pragma once

#include <iostream>
#include <fstream>

struct Employee
{
	int num; // идентификационный номер сотрудника
	char name[10]; // имя сотрудника
	double hours; // количество отработанных часов
};

Employee* readEmployeeFromStream(const std::istream& in);