#include "Employee.h"
#include <iostream>
#include <iomanip>

Employee::Employee(int id, const std::string& name, const std::string& pos, const std::string& dept)
    : id(id), fullName(name), position(pos), department(dept) {
}

int Employee::getId() const { return id; }
std::string Employee::getFullName() const { return fullName; }
std::string Employee::getPosition() const { return position; }
std::string Employee::getDepartment() const { return department; }

void Employee::displayInfo() const {
    std::cout << std::left;
    std::cout << "ID: " << std::setw(5) << id
        << " | ФИО: " << std::setw(30) << fullName
        << " | Должность: " << std::setw(20) << position
        << " | Отдел: " << department << std::endl;
}