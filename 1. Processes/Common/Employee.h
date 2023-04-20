#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

struct Employee {
  int num;  // идентификационный номер сотрудника
  char name[10];  // имя сотрудника
  double hours;   // количество отработанных часов
};

#endif  // !EMPLOYEE_H_