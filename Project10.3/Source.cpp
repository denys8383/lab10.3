#include <iostream>
#include <string>

// Визначення констант для максимальної кількості офісів та працівників на офіс
const int MAX_OFFICES = 100;
const int MAX_EMPLOYEES_PER_OFFICE = 4;

// Визначення структури для представлення працівника
struct Employee {
    std::string lastName;  // Прізвище працівника
    std::string phoneNumber;  // Номер телефону працівника
};

// Визначення структури для представлення офісу
struct Office {
    int roomNumber;  // Номер кімнати офісу
    Employee employees[MAX_EMPLOYEES_PER_OFFICE];  // Масив працівників офісу
    int employeeCount;  // Кількість працівників в офісі

    // Конструктор з параметром за замовчуванням
    Office(int room = 0) : roomNumber(room), employeeCount(0) {}

    // Метод для додавання працівника до офісу
    void addEmployee(const std::string& phoneNumber, const std::string& lastName) {
        if (employeeCount < MAX_EMPLOYEES_PER_OFFICE) {
            employees[employeeCount] = { lastName, phoneNumber };
            employeeCount++;
        }
        else {
            std::cout << "Office is full. Cannot add more employees.\n";
        }
    }

    // Метод для знаходження працівника за номером телефону
    int findEmployeeByPhoneNumber(const std::string& phoneNumber, Employee& foundEmployee) const {
        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].phoneNumber == phoneNumber) {
                foundEmployee = employees[i];
                return 1; // Успішно знайдено працівника
            }
        }
        return 0; // Працівник не знайдений
    }

    // Метод для знаходження номера телефону за прізвищем
    int findPhoneNumberByLastName(const std::string& lastName, std::string& foundPhoneNumber) const {
        for (int i = 0; i < employeeCount; ++i) {
            if (employees[i].lastName == lastName) {
                foundPhoneNumber = employees[i].phoneNumber;
                return 1; // Успішно знайдено відповідність
            }
        }
        return 0; // Відповідність не знайдена
    }
};

// Функція для додавання працівника до офісу
void addEmployee(Office* offices, int& officeCount, const std::string& phoneNumber, const std::string& lastName, int roomNumber) {
    int index = -1;
    for (int i = 0; i < officeCount; ++i) {
        if (offices[i].roomNumber == roomNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        if (officeCount < MAX_OFFICES) {
            offices[officeCount] = Office(roomNumber);
            index = officeCount;
            officeCount++;
        }
        else {
            std::cout << "Cannot add more offices. Maximum limit reached.\n";
            return;
        }
    }

    offices[index].addEmployee(phoneNumber, lastName);
}

// Функція для виведення інформації про кімнату за номером телефону
void displayRoomInfo(const Office* offices, int officeCount, const std::string& phoneNumber) {
    Employee foundEmployee;
    for (int i = 0; i < officeCount; ++i) {
        if (offices[i].findEmployeeByPhoneNumber(phoneNumber, foundEmployee)) {
            std::cout << "Room Number: " << offices[i].roomNumber << "\n";
            std::cout << "Employees in the Room:\n";
            for (int j = 0; j < offices[i].employeeCount; ++j) {
                std::cout << "  Last Name: " << offices[i].employees[j].lastName << "\n";
                std::cout << "  Phone Number: " << offices[i].employees[j].phoneNumber << "\n";
                std::cout << "-------------------------\n";
            }
            return;
        }
    }
    std::cout << "No information found for the given phone number.\n";
}

// Функція для виведення номера телефону за прізвищем
void displayPhoneNumberByLastName(const Office* offices, int officeCount, const std::string& lastName) {
    std::string foundPhoneNumber;
    for (int i = 0; i < officeCount; ++i) {
        if (offices[i].findPhoneNumberByLastName(lastName, foundPhoneNumber)) {
            std::cout << "Phone Number for " << lastName << ": " << foundPhoneNumber << "\n";
            std::cout << "Room Number: " << offices[i].roomNumber << "\n";
            return;
        }
    }
    std::cout << "No information found for the given last name.\n";
}

// Основна функція програми
int main() {
    // Ініціалізація масиву офісів та змінної для кількості офісів
    Office* offices = new Office[MAX_OFFICES];
    int officeCount = 0;

    // Безкінечний цикл для взаємодії з користувачем
    do {
        // Виведення меню телефонного довідника
        std::cout << "\nTelephone Directory Menu:\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Display Room Info\n";
        std::cout << "3. Display Phone Number by Last Name\n";
        std::cout << "0. Exit\n";

        // Зчитування вибору користувача
        int choice;
        std::cout << "Enter your choice (0-3): ";
        std::cin >> choice;

        // Обробка вибору користувача
        switch (choice) {
        case 1: {
            // Додавання працівника
            std::string phoneNumber, lastName;
            int roomNumber;
            std::cout << "Enter phone number: ";
            std::cin >> phoneNumber;
            std::cout << "Enter last name: ";
            std::cin >> lastName;
            std::cout << "Enter room number: ";
            std::cin >> roomNumber;
            addEmployee(offices, officeCount, phoneNumber, lastName, roomNumber);
            break;
        }
        case 2: {
            // Виведення інформації про кімнату за номером телефону
            std::string phoneNumber;
            std::cout << "Enter phone number to display room info: ";
            std::cin >> phoneNumber;
            displayRoomInfo(offices, officeCount, phoneNumber);
            break;
        }
        case 3: {
            // Виведення номера телефону за прізвищем
            std::string lastName;
            std::cout << "Enter last name to display phone number: ";
            std::cin >> lastName;
            displayPhoneNumberByLastName(offices, officeCount, lastName);
            break;
        }
        case 0:
            // Вихід з програми
            std::cout << "Exiting the program. Goodbye!\n";
            delete[] offices;
            return 0;
        default:
            // Обробка некоректного вибору
            std::cout << "Invalid choice. Please enter a number between 0 and 3.\n";
        }
    } while (true);

    // Звільнення пам'яті та завершення програми
    delete[] offices;
    return 0;
}
