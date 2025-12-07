#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>  
#include "Device.h"
#include "Employee.h"
#include "AssignmentRecord.h"

// --- Объявления функций из main.cpp ---
void addNewDevice(std::vector<Device>& devices) {
    int id, year;
    std::string manuf, model, imei, status;
    double cost;

    std::cout << "--- Добавление нового устройства ---\n";
    std::cout << "Введите ID устройства (уникальный номер): ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Производитель: ";
    std::getline(std::cin, manuf);
    std::cout << "Модель: ";
    std::getline(std::cin, model);
    std::cout << "IMEI: ";
    std::getline(std::cin, imei);
    std::cout << "Год покупки: ";
    std::cin >> year;
    std::cin.ignore();
    std::cout << "Статус (На складе, В эксплуатации, На ремонте, Списан): ";
    std::getline(std::cin, status);
    std::cout << "Стоимость (руб): ";
    std::cin >> cost;

    devices.emplace_back(id, manuf, model, imei, year, status, cost);
    std::cout << "Устройство успешно добавлено!\n";
}

void addNewEmployee(std::vector<Employee>& employees) {
    int id;
    std::string name, pos, dept;

    std::cout << "--- Добавление нового сотрудника ---\n";
    std::cout << "Введите ID сотрудника (уникальный номер): ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "ФИО: ";
    std::getline(std::cin, name);
    std::cout << "Должность: ";
    std::getline(std::cin, pos);
    std::cout << "Отдел: ";
    std::getline(std::cin, dept);

    employees.emplace_back(id, name, pos, dept);
    std::cout << "Сотрудник успешно добавлен!\n";
}

void listDevices(const std::vector<Device>& devices) {
    std::cout << "--- Список всех устройств ---\n";
    if (devices.empty()) {
        std::cout << "Устройств нет.\n";
        return;
    }
    for (const auto& device : devices) {
        device.displayInfo();
    }
}

void listEmployees(const std::vector<Employee>& employees) {
    std::cout << "--- Список всех сотрудников ---\n";
    if (employees.empty()) {
        std::cout << "Сотрудников нет.\n";
        return;
    }
    for (const auto& emp : employees) {
        emp.displayInfo();
    }
}

void assignDevice(std::vector<Device>& devices, std::vector<Employee>& employees, std::vector<AssignmentRecord>& history) {
    if (devices.empty() || employees.empty()) {
        std::cout << "Недостаточно данных для выдачи (нужны устройства и сотрудники).\n";
        return;
    }

    std::cout << "--- Закрепление устройства за сотрудником ---\n";
    listDevices(devices);
    listEmployees(employees);

    int deviceId, employeeId;
    std::string date;

    std::cout << "Введите ID устройства для выдачи: ";
    std::cin >> deviceId;
    std::cin.ignore();

    auto deviceIt = std::find_if(devices.begin(), devices.end(),
        [deviceId](const Device& d) { return d.getId() == deviceId; });
    if (deviceIt == devices.end()) {
        std::cout << "Устройство с таким ID не найдено.\n";
        return;
    }
    if (deviceIt->getStatus() != "На складе") {
        std::cout << "Устройство не может быть выдано. Текущий статус: " << deviceIt->getStatus() << std::endl;
        return;
    }

    std::cout << "Введите ID сотрудника: ";
    std::cin >> employeeId;
    std::cin.ignore();

    auto empIt = std::find_if(employees.begin(), employees.end(),
        [employeeId](const Employee& e) { return e.getId() == employeeId; });
    if (empIt == employees.end()) {
        std::cout << "Сотрудник с таким ID не найдено.\n";
        return;
    }

    std::cout << "Введите дату выдачи (например, 12.04.2024): ";
    std::getline(std::cin, date);

    // Обновляем устройство
    deviceIt->setStatus("В эксплуатации");
    deviceIt->setCurrentOwnerId(employeeId);

    // Создаем запись в истории
    int newRecordId = history.size() + 1;
    history.emplace_back(newRecordId, deviceId, employeeId, date, "");

    std::cout << "Устройство успешно закреплено за сотрудником!\n";
}

void returnDevice(std::vector<Device>& devices, std::vector<AssignmentRecord>& history) {
    if (devices.empty() || history.empty()) {
        std::cout << "Нет данных для возврата.\n";
        return;
    }

    std::cout << "--- Возврат устройства на склад ---\n";
    // Показываем устройства в эксплуатации
    bool foundInUse = false;
    for (const auto& dev : devices) {
        if (dev.getStatus() == "В эксплуатации") {
            if (!foundInUse) {
                std::cout << "Устройства в эксплуатации:\n";
                foundInUse = true;
            }
            dev.displayInfo();
        }
    }
    if (!foundInUse) {
        std::cout << "Нет устройств в эксплуатации.\n";
        return;
    }

    int deviceId;
    std::string returnDate;

    std::cout << "Введите ID возвращаемого устройства: ";
    std::cin >> deviceId;
    std::cin.ignore();

    auto deviceIt = std::find_if(devices.begin(), devices.end(),
        [deviceId](const Device& d) { return d.getId() == deviceId && d.getStatus() == "В эксплуатации"; });
    if (deviceIt == devices.end()) {
        std::cout << "Устройство с таким ID не найдено или его статус не 'В эксплуатации'.\n";
        return;
    }

    // Ищем активную запись в истории (без даты возврата)
    auto recordIt = std::find_if(history.rbegin(), history.rend(),
        [deviceId](const AssignmentRecord& rec) {
            return rec.getDeviceId() == deviceId && rec.getReturnDate().empty();
        });
    if (recordIt == history.rend()) {
        std::cout << "Не найдена активная запись о выдаче этого устройства.\n";
        return;
    }

    std::cout << "Введите дату возврата (например, 12.04.2024): ";
    std::getline(std::cin, returnDate);

    // Обновляем запись и устройство
    recordIt->setReturnDate(returnDate);
    deviceIt->setStatus("На складе");
    deviceIt->setCurrentOwnerId(-1);

    std::cout << "Устройство успешно возвращено на склад!\n";
}

void showDeviceHistory(const std::vector<AssignmentRecord>& history, const std::vector<Device>& devices) {
    if (history.empty()) {
        std::cout << "История закреплений пуста.\n";
        return;
    }

    std::cout << "--- История закреплений устройств ---\n";
    for (const auto& record : history) {
        // Простой вывод без поиска имен устройств/сотрудников по ID для упрощения
        record.displayInfo();
    }
}

void showStatistics(const std::vector<Device>& devices) {
    if (devices.empty()) {
        std::cout << "Нет данных для статистики.\n";
        return;
    }

    std::cout << "--- СТАТИСТИКА ПО УСТРОЙСТВАМ ---\n";
    std::cout << "Всего устройств: " << devices.size() << std::endl;

    // Подсчет по статусам
    std::vector<std::string> statuses = { "На складе", "В эксплуатации", "На ремонте", "Списан" };
    std::vector<int> counts(statuses.size(), 0);

    for (const auto& dev : devices) {
        for (size_t i = 0; i < statuses.size(); ++i) {
            if (dev.getStatus() == statuses[i]) {
                counts[i]++;
                break;
            }
        }
    }

    // Визуализация простой гистограммой в консоли
    std::cout << "\nРаспределение по статусам:\n";
    const int MAX_BAR_WIDTH = 40;
    int maxCount = *std::max_element(counts.begin(), counts.end());

    for (size_t i = 0; i < statuses.size(); ++i) {
        std::cout << statuses[i] << ": [" << std::setw(3) << counts[i] << "] ";
        if (maxCount > 0) {
            int barLength = (counts[i] * MAX_BAR_WIDTH) / maxCount;
            for (int j = 0; j < barLength; ++j) {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }
}