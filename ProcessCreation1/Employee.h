#pragma once

#include <iostream>
#include <fstream>

struct Employee
{
	int num; // ����������������� ����� ����������
	char name[10]; // ��� ����������
	double hours; // ���������� ������������ �����
};

Employee* readEmployeeFromStream(std::istream& in);
Employee* readEmployeeFromConsole();