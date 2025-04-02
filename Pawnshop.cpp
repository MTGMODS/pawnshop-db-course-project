#include "Pawnshop.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <sstream>
#include "Item.h"
#include "Client.h"
#include "Menu.h"

Pawnshop::Pawnshop() {
    loadDataFromFile("pawnshop_data.txt");
}

void Pawnshop::displayClients() const {
    if (clients.empty()) {
        cout << "No clients to display.\n\n";
        return;
    }
    std::cout << "---------------------------------------------------------------------\n";
    for (const auto& client : clients) {
        client.display();
        std::cout << "---------------------------------------------------------------------\n";
    }
}
void Pawnshop::addClient() {
    int id = 2;
    if (!clients.empty()) {
        id = max_element(clients.begin(), clients.end(),[](const Client& a, const Client& b) {
                return a.getId() < b.getId();
        })->getId() + 1;
    }
    string name, phone;
    cout << "Enter Client Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Client Phone: ";
    getline(cin, phone);
    clients.emplace_back(id, name, phone);
    cout << "Succes created new Client.\n\n";
    saveDataToFile("pawnshop_data.txt");
}
void Pawnshop::removeClient() {
    int clientId;
    cout << "Enter Client ID to remove: ";
    cin >> clientId;

    // Пошук клієнта за ID
    auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& client) {
        return client.getId() == clientId;
    });

    if (it == clients.end()) {
        cout << "Client with ID " << clientId << " not found.\n";
    } else {
        // Підтвердження на видалення
        char confirm;
        cout << "Are you sure you want to delete this client? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            clients.erase(it);
            cout << "Client with ID " << clientId << " has been deleted.\n";
        } else {
            cout << "Client deletion canceled.\n";
        }
    }
}
void Pawnshop::searchClient() {
    int choice;
    std::cout << "Search client by:\n";
    std::cout << "1. Client ID\n";
    std::cout << "2. Part of Client Name\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // Пошук за ID
        int clientId;
        while (true) {
            std::cout << "Enter 0 to cancel action or enter Client ID: ";

            // Перевірка на коректний ввід
            if (!(std::cin >> clientId)) {
                std::cin.clear(); // Скидання стану потоку
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid numeric ID.\n";
                continue;
            }

            if (clientId == 0) {
                return; // Скасування дії
            }

            // Пошук клієнта за ID
            auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& client) {
                return client.getId() == clientId;
            });

            if (it == clients.end()) { // Клієнт не знайдений
                std::cout << "Client with ID " << clientId << " not found!\n";
            } else { // Клієнт знайдений
                std::cout << "---------------------------------------------------------------------\n";
                it->display();
                std::cout << "---------------------------------------------------------------------\n";
                return;
            }
        }
    } else if (choice == 2) {
        // Пошук за частиною імені
        std::string partOfName;
        std::cout << "Enter part of the client's name: ";
        std::cin.ignore(); // Очистка буфера
        std::getline(std::cin, partOfName);

        bool found = false;
        for (const auto& client : clients) {
            if (client.getName().find(partOfName) != std::string::npos) {
                std::cout << "---------------------------------------------------------------------\n";
                client.display();
                std::cout << "---------------------------------------------------------------------\n";
                found = true;
            }
        }

        if (!found) {
            std::cout << "No clients found with the name containing \"" << partOfName << "\".\n";
        }
    } else {
        std::cout << "Invalid choice. Please choose either 1 or 2.\n";
    }
}
void Pawnshop::editClient() {
    int clientId;

    while (true) {
        std::cout << "Enter 0 to cancel action or enter Client ID: ";

        // Перевірка на коректний ввід
        if (!(std::cin >> clientId)) {
            std::cin.clear(); // Скидання стану потоку
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric ID.\n";
            continue;
        }

        if (clientId == 0) {
            return; // Скасування дії
        }

        // Пошук клієнта за ID
        auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& client) {
            return client.getId() == clientId;
        });

        if (it == clients.end()) { // Клієнт не знайдений
            std::cout << "Client with ID " << clientId << " not found!\n";
        } else { // Клієнт знайдений
            std::string name, phone;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буфера

            std::cout << "Enter new Name (old " << it->getName() << "): ";
            std::getline(std::cin, name);

            std::cout << "Enter new Phone (old " << it->getPhone() <<"): ";
            std::getline(std::cin, phone);

            // Оновлення даних клієнта
            it->setName(name);
            it->setPhone(phone);

            std::cout << "Client data updated successfully.\n";

            // Збереження змін у файл
            saveDataToFile("pawnshop_data.txt");
            return;
        }
    }
}

void Pawnshop::displayItems() const {
    if (items.empty()) {
        cout << "No items to display.\n\n";
        return;
    }
    std::cout << "---------------------------------------------------------------------\n";
    for (const auto& item : items) {
        item.display();
        std::cout << "---------------------------------------------------------------------\n";
    }
}
void Pawnshop::addItem() {
    if (clients.empty()) {
        std::cout << "No clients available. Add a client first.\n";
        return;
    }

    int id = 1;
    if (!items.empty()) {
        id = max_element(items.begin(), items.end(),
                         [](const Item& a, const Item& b) {
                             return a.getId() < b.getId();
                         })->getId() + 1;
    }

    std::string name, pledgeDate, storagePeriod;
    double appraisalValue, loanAmount;
    int ownerId;

    std::cout << "Enter Item Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter Appraisal Value: ";
    std::cin >> appraisalValue;

    std::cout << "Enter Loan Amount: ";
    std::cin >> loanAmount;

    std::cout << "Enter Pledge Date (YYYY-MM-DD): ";
    std::cin >> pledgeDate;

    std::cout << "Enter Storage Period (in months): ";
    std::cin >> storagePeriod;

    std::cout << "Select Owner by ID:\n";
    for (const auto& client : clients) {
        std::cout << "ID: " << client.getId() << ", Name: " << client.getName() << "\n";
    }

    while (true) {
        std::cout << "Enter Owner ID: ";
        std::cin >> ownerId;

        auto ownerIt = std::find_if(clients.begin(), clients.end(),
                                    [ownerId](const Client& client) {
                                        return client.getId() == ownerId;
                                    });

        if (ownerIt != clients.end()) {
            // Створення нового предмета з передачею об'єкта owner
            items.emplace_back(id, name, appraisalValue, loanAmount, pledgeDate, storagePeriod, *ownerIt);
            std::cout << "Successfully created new Item.\n\n";
            saveDataToFile("pawnshop_data.txt");
            return;
        } else {
            std::cout << "Owner with ID " << ownerId << " not found. Try again.\n";
        }
    }
}
void Pawnshop::editItem() {
    if (items.empty()) {
        std::cout << "No items to edit.\n";
        return;
    }

    int itemId;
    while (true) {
        std::cout << "Enter 0 to cancel action or enter Item ID: ";
        if (!(std::cin >> itemId)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric ID.\n";
            continue;
        }

        if (itemId == 0) {
            return;
        }

        auto it = std::find_if(items.begin(), items.end(),
                               [itemId](const Item& item) {
                                   return item.getId() == itemId;
                               });

        if (it == items.end()) {
            std::cout << "Item with ID " << itemId << " not found!\n";
        } else {
            std::string name, pledgeDate, storagePeriod;
            double appraisalValue, loanAmount;
            int ownerId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буфера

            std::cout << "Enter new Name (old: " << it->getName() << "): ";
            std::getline(std::cin, name);
            if (name.empty()) name = it->getName();

            std::cout << "Enter new Appraisal Value (old: " << it->getAppraisalValue() << "): ";
            std::string input;
            std::getline(std::cin, input);
            appraisalValue = input.empty() ? it->getAppraisalValue() : std::stod(input);

            std::cout << "Enter new Loan Amount (old: " << it->getLoanAmount() << "): ";
            std::getline(std::cin, input);
            loanAmount = input.empty() ? it->getLoanAmount() : std::stod(input);

            std::cout << "Enter new Pledge Date (old: " << it->getPledgeDate() << "): ";
            std::getline(std::cin, pledgeDate);
            if (pledgeDate.empty()) pledgeDate = it->getPledgeDate();

            std::cout << "Enter new Storage Period (old: " << it->getStoragePeriod() << "): ";
            std::getline(std::cin, storagePeriod);
            if (storagePeriod.empty()) storagePeriod = it->getStoragePeriod();

            // Вибір нового власника
            std::cout << "Select new Owner by ID (old: " << it->getOwner().getName() << "):\n";
            for (const auto& client : clients) {
                std::cout << "ID: " << client.getId() << ", Name: " << client.getName() << "\n";
            }

            while (true) {
                std::cout << "Enter Owner ID: ";
                std::cin >> ownerId;

                auto ownerIt = std::find_if(clients.begin(), clients.end(),
                                            [ownerId](const Client& client) {
                                                return client.getId() == ownerId;
                                            });

                if (ownerIt != clients.end()) {
                    it->setName(name);
                    it->setAppraisalValue(appraisalValue);
                    it->setLoanAmount(loanAmount);
                    it->setPledgeDate(pledgeDate);
                    it->setStoragePeriod(storagePeriod);
                    it->setOwner(*ownerIt);

                    std::cout << "Item data updated successfully.\n";
                    saveDataToFile("pawnshop_data.txt");
                    return;
                } else {
                    std::cout << "Owner with ID " << ownerId << " not found. Try again.\n";
                }
            }
        }
    }
}
void Pawnshop::removeItem() {
    int itemId;
    cout << "Enter Item ID to remove: ";
    cin >> itemId;

    // Пошук предмета за ID
    auto it = std::find_if(items.begin(), items.end(), [itemId](const Item& item) {
        return item.getId() == itemId;
    });

    if (it == items.end()) {
        cout << "Item with ID " << itemId << " not found.\n";
    } else {
        // Підтвердження на видалення
        char confirm;
        cout << "Are you sure you want to delete this item? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            items.erase(it);
            cout << "Item with ID " << itemId << " has been deleted.\n";
        } else {
            cout << "Item deletion canceled.\n";
        }
    }
}

void Pawnshop::searchItem() {
    int itemId;
    while (true) {
        std::cout << "Enter 0 to cancel action or enter Item ID: ";
        if (!(std::cin >> itemId)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric ID.\n";
            continue;
        }

        if (itemId == 0) {
            return;
        }

        auto it = std::find_if(items.begin(), items.end(),
                               [itemId](const Item& item) {
                                   return item.getId() == itemId;
                               });

        if (it == items.end()) {
            std::cout << "Item with ID " << itemId << " not found!\n";
        } else {
            std::cout << "---------------------------------------------------------------------\n";
            it->display();
            std::cout << "---------------------------------------------------------------------\n";
            return;
        }
    }
}


void Pawnshop::sortItemsByPrice() {
    if (items.empty()) {
        std::cout << "No items to sort.\n";
        return;
    }

    int choice;
    std::cout << "Sort items by price:\n";
    std::cout << "1. From lowest to highest (min to max)\n";
    std::cout << "2. From highest to lowest (max to min)\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getAppraisalValue() < b.getAppraisalValue();
        });
        std::cout << "Items sorted from lowest to highest price.\n";
    } else if (choice == 2) {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getAppraisalValue() > b.getAppraisalValue();
        });
        std::cout << "Items sorted from highest to lowest price.\n";
    } else {
        std::cout << "Invalid choice. Sorting not applied.\n";
    }

    // Display sorted items
    displayItems();
}
void Pawnshop::filterItems() {
    if (items.empty()) {
        cout << "No items to filter.\n";
        return;
    }

    double minAppraisalValue;
    cout << "Enter minimum appraisal value: ";
    cin >> minAppraisalValue;

    bool found = false;
    for (const auto& item : items) {
        if (item.getAppraisalValue() >= minAppraisalValue) {
            item.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No items match the given filter.\n";
    }
}

void Pawnshop::saveDataToFile(const std::string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file for saving!\n";
        return;
    }

    // Збереження клієнтів
    file << "Clients:\n";
    for (const auto& client : clients) {
        file << client.getId() << "," << client.getName() << "," << client.getPhone() << "\n";
    }

    // Збереження предметів
    file << "Items:\n";
    for (const auto& item : items) {
        file << item.getId() << "," << item.getName() << ","
             << item.getAppraisalValue() << "," << item.getLoanAmount() << ","
             << item.getPledgeDate() << "," << item.getStoragePeriod() << ","
             << item.getOwner().getId() << "\n";
    }
}
void Pawnshop::loadDataFromFile(const std::string& filename) {
    ifstream file(filename);
    string line;
    bool readingClients = true;



    if (!file.is_open()) {
        clients.emplace_back(1, "ADMIN (Owner Pawnshop)", "");
        saveDataToFile("pawnshop_data.txt");
        return;
    }

    clients.clear();
    items.clear();

    while (getline(file, line)) {
        if (line == "Clients:") {
            readingClients = true;
        } else if (line == "Items:") {
            readingClients = false;
        } else {
            stringstream ss(line);
            string idStr, name, address, phone;
            if (readingClients) {
                // Завантаження клієнтів
                getline(ss, idStr, ',');
                int id = stoi(idStr);
                getline(ss, name, ',');
                getline(ss, phone);
                clients.emplace_back(id, name, phone);
            } else {
                string idStr, itemName, appraisalValueStr, loanAmountStr, pledgeDate, storagePeriod, clientIdStr;
                getline(ss, idStr, ',');
                int id = stoi(idStr);
                getline(ss, itemName, ',');
                getline(ss, appraisalValueStr, ',');
                double appraisalValue = stod(appraisalValueStr);
                getline(ss, loanAmountStr, ',');
                double loanAmount = stod(loanAmountStr);
                getline(ss, pledgeDate, ',');
                getline(ss, storagePeriod, ',');
                getline(ss, clientIdStr);
                int clientId = stoi(clientIdStr);

                auto clientIt = find_if(clients.begin(), clients.end(), [clientId](const Client& c) {
                    return c.getId() == clientId;
                });

                if (clientIt != clients.end()) {
                    items.emplace_back(id, itemName, appraisalValue, loanAmount, pledgeDate, storagePeriod, *clientIt);
                }
            }
        }
    }
}
