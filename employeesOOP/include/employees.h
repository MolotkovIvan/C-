#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>

class Employee {
public:
  virtual ~Employee() {delete [] _name;};
  friend std::ostream& operator<<(std::ostream&, const Employee&);
  friend std::ofstream& operator<<(std::ofstream&, const Employee&);
  virtual void print(std::ostream&) const {};
  virtual void print(std::ofstream&) const {};
  virtual int salary() const = 0;
protected:
  char *_name;
  int32_t _base_salary;
};

class Developer: public Employee {
public:
  friend std::istream& operator>>(std::istream&, Developer&);
  friend std::ifstream& operator>>(std::ifstream&, Developer&);
  Developer() {};
  Developer(char* name, int32_t base_salary, bool has_bonus);
  virtual void print(std::ostream&) const;
  virtual void print(std::ofstream&) const;
  virtual int salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
  }
private:
  bool _has_bonus;
};

class SalesManager: public Employee {
public:
  friend std::istream& operator>>(std::istream&, SalesManager&);
  friend std::ifstream& operator>>(std::ifstream&, SalesManager&);
  SalesManager() {};
  SalesManager(char* name, int32_t base_salary, int32_t sold_nm, int32_t price);
  virtual void print(std::ostream&) const;
  virtual void print(std::ofstream&) const;
  virtual int salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
  }
private:
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();
  friend std::ostream& operator<<(std::ostream&, const EmployeesArray&);
  friend std::ofstream& operator<<(std::ofstream&, const EmployeesArray&);
  friend std::ifstream& operator>>(std::ifstream&, EmployeesArray&);
  void add(const Employee *e);
  int total_salary() const;
private:
  Employee **_employees;
  int32_t _len;
  int32_t _cp;
};

/*
std::ostream& operator<<(std::ostream& os, const Employee& employee);
std::istream& operator>>(std::istream&, Developer&);
std::istream& operator>>(std::istream&, SalesManager&);
*/
#endif
