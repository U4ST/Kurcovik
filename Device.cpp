#include "Device.h"
#include <iostream>
#include <iomanip>

Device::Device(int id, const std::string& manuf, const std::string& mod,
    const std::string& imeiNum, int year, const std::string& stat, double cst)
    : id(id), manufacturer(manuf), model(mod), imei(imeiNum),
    purchaseYear(year), status(stat), cost(cst), currentOwnerId(-1) {
}

int Device::getId() const { return id; }
std::string Device::getManufacturer() const { return manufacturer; }
std::string Device::getModel() const { return model; }
std::string Device::getImei() const { return imei; }
std::string Device::getStatus() const { return status; }
int Device::getCurrentOwnerId() const { return currentOwnerId; }
double Device::getCost() const { return cost; }

void Device::setStatus(const std::string& newStatus) { status = newStatus; }
void Device::setCurrentOwnerId(int ownerId) { currentOwnerId = ownerId; }

void Device::displayInfo() const {
    std::cout << std::left;
    std::cout << "ID: " << std::setw(5) << id
        << " | " << std::setw(15) << (manufacturer + " " + model)
        << " | IMEI: " << std::setw(18) << imei
        << " | Статус: " << std::setw(15) << status
        << " | Стоимость: " << std::setw(10) << cost << " руб.";
    if (currentOwnerId != -1) {
        std::cout << " | Владелец ID: " << currentOwnerId;
    }
    std::cout << std::endl;
}