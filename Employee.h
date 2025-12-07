#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    int id;
    std::string fullName;
    std::string position;
    std::string department;

public:
    Employee(int id, const std::string& name, const std::string& pos, const std::string& dept);
    int getId() const;
    std::string getFullName() const;
    std::string getPosition() const;
    std::string getDepartment() const;
    void displayInfo() const;
};

#endif