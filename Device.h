#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
private:
    int id;
    std::string manufacturer;
    std::string model;
    std::string imei;
    int purchaseYear;
    std::string status; // "На складе", "В эксплуатации", "На ремонте", "Списан"
    double cost;
    int currentOwnerId; // ID сотрудника, если закреплено, иначе -1

public:
    // Конструктор
    Device(int id, const std::string& manuf, const std::string& mod,
        const std::string& imeiNum, int year, const std::string& stat, double cst);

    // Геттеры
    int getId() const;
    std::string getManufacturer() const;
    std::string getModel() const;
    std::string getImei() const;
    std::string getStatus() const;
    int getCurrentOwnerId() const;
    double getCost() const;

    // Сеттеры
    void setStatus(const std::string& newStatus);
    void setCurrentOwnerId(int ownerId);

    // Метод для отображения информации
    void displayInfo() const;
};

#endif