#ifndef ASSIGNMENTRECORD_H
#define ASSIGNMENTRECORD_H

#include <string>

class AssignmentRecord {
private:
    int id;
    int deviceId;
    int employeeId;
    std::string assignmentDate;
    std::string returnDate; 

public:
    AssignmentRecord(int id, int devId, int empId, const std::string& assignDate, const std::string& retDate);
    int getDeviceId() const;
    int getEmployeeId() const;
    std::string getAssignmentDate() const;
    std::string getReturnDate() const;
    void setReturnDate(const std::string& retDate);
    void displayInfo(int deviceIdx = -1, int employeeIdx = -1) const; // Индексы для поиска имен
};

#endif