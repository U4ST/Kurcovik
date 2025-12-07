#include <iostream>
#include <vector>
#include <limits> /
#include "Device.h"
#include "Employee.h"
#include "AssignmentRecord.h"
#include <locale.h>

// прототипы
void displayMainMenu();
void addNewDevice(std::vector<Device>& devices);
void addNewEmployee(std::vector<Employee>& employees);
void listDevices(const std::vector<Device>& devices);
void listEmployees(const std::vector<Employee>& employees);
void assignDevice(std::vector<Device>& devices, std::vector<Employee>& employees, std::vector<AssignmentRecord>& history);
void returnDevice(std::vector<Device>& devices, std::vector<AssignmentRecord>& history);
void showDeviceHistory(const std::vector<AssignmentRecord>& history, const std::vector<Device>& devices);
void showStatistics(const std::vector<Device>& devices);
void clearInputBuffer();

int main() {

    setlocale(LC_ALL, "Ru");
    

    std::vector<Device> devices;
    std::vector<Employee> employees;
    std::vector<AssignmentRecord> assignmentHistory;

    int choice = 0;
    bool running = true;

    // Добавим несколько тестовых устройств и сотрудников для наглядности
    devices.push_back(Device(1, "Apple", "iPhone 14", "123456789012345", 2023, "В эксплуатации", 79999.99));
    devices.push_back(Device(2, "Samsung", "Galaxy S23", "234567890123456", 2023, "На складе", 69999.50));
    devices.push_back(Device(3, "Xiaomi", "Redmi Note 12", "345678901234567", 2022, "На ремонте", 24999.00));

    employees.push_back(Employee(1, "Иванов Иван Иванович", "Разработчик", "IT"));
    employees.push_back(Employee(2, "Петрова Анна Сергеевна", "Менеджер", "Продажи"));

    // Закрепим одно устройство заранее для примера истории
    if (!devices.empty() && !employees.empty()) {
        AssignmentRecord rec(assignmentHistory.size() + 1, devices[0].getId(), employees[0].getId(), "01.09.2023", "");
        devices[0].setStatus("В эксплуатации");
        devices[0].setCurrentOwnerId(employees[0].getId());
        assignmentHistory.push_back(rec);
    }

    while (running) {
        displayMainMenu();
        std::cout << "Введите номер действия: ";
        std::cin >> choice;
        clearInputBuffer(); // Очистка буфера после ввода числа

        switch (choice) {
        case 1:
            addNewDevice(devices);
            break;
        case 2:
            addNewEmployee(employees);
            break;
        case 3:
            listDevices(devices);
            break;
        case 4:
            listEmployees(employees);
            break;
        case 5:
            assignDevice(devices, employees, assignmentHistory);
            break;
        case 6:
            returnDevice(devices, assignmentHistory);
            break;
        case 7:
            showDeviceHistory(assignmentHistory, devices);
            break;
        case 8:
            showStatistics(devices);
            break;
        case 0:
            running = false;
            std::cout << "Выход из программы. Данные не сохранены (режим демонстрации).\n";
            break;
        default:
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }

    return 0;
}

void displayMainMenu() {
    std::cout << "\n";
    std::cout << "=== ИНФОРМАЦИОННАЯ СИСТЕМА УЧЕТА МОБИЛЬНЫХ УСТРОЙСТВ ===\n";
    std::cout << "1. Добавить новое устройство\n";
    std::cout << "2. Добавить нового сотрудника\n";
    std::cout << "3. Показать все устройства\n";
    std::cout << "4. Показать всех сотрудников\n";
    std::cout << "5. Закрепить устройство за сотрудником (Выдать)\n";
    std::cout << "6. Вернуть устройство на склад\n";
    std::cout << "7. Показать историю закреплений устройства\n";
    std::cout << "8. Показать статистику (визуализация)\n";
    std::cout << "0. Выход\n";
    std::cout << "=======================================================\n";
}

void clearInputBuffer() {
    std::cin.clear(); // Сброс флагов ошибок
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера до новой строки
}