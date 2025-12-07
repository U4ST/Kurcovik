#include "AssignmentRecord.h"
#include <iostream>
#include <iomanip>

AssignmentRecord::AssignmentRecord(int id, int devId, int empId, const std::string& assignDate, const std::string& retDate)
    : id(id), deviceId(devId), employeeId(empId), assignmentDate(assignDate), returnDate(retDate) {
}

int AssignmentRecord::getDeviceId() const { return deviceId; }
int AssignmentRecord::getEmployeeId() const { return employeeId; }
std::string AssignmentRecord::getAssignmentDate() const { return assignmentDate; }
std::string AssignmentRecord::getReturnDate() const { return returnDate; }
void AssignmentRecord::setReturnDate(const std::string& retDate) { returnDate = retDate; }

void AssignmentRecord::displayInfo(int deviceIdx, int employeeIdx) const {
    std::cout << std::left;
    std::cout << "Запись ID: " << std::setw(3) << id
        << " | Устройство ID: " << std::setw(3) << deviceId;
    if (deviceIdx != -1) {
       //будет передаваться индекс/название устройства
        std::cout << " (Индекс в списке: " << deviceIdx << ")";
    }
    std::cout << " | Сотрудник ID: " << std::setw(3) << employeeId;
    if (employeeIdx != -1) {
        std::cout << " (Индекс в списке: " << employeeIdx << ")";
    }
    std::cout << " | Выдано: " << std::setw(12) << assignmentDate
        << " | Возвращено: " << returnDate << std::endl;
}