#include "Menu.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <locale>
#include "Pawnshop.h"

using namespace std;

Menu::Menu(Pawnshop& p) : pawnshop(p) {}


void Menu::userGuide() const {
    cout << "User Guide:\n";
    cout << "1. Use the menu to navigate through the options.\n";
    cout << "2. Add clients and items before viewing them.\n";
    cout << "3. Use search to find specific clients or items.\n";
    cout << "4. Use sorting and filtering to organize data.\n";
    cout << "5. Edit or delete entries as needed.\n";
    cout << "6. Save data to a file to avoid losing it.\n\n";
}


void Menu::displayMenu() {
    int choice;
    do {
        cout << "\nPawnshop Management System\n";
        cout << "1. View all Clients\n";
        cout << "2. Search Client\n";
        cout << "3. Add new Client\n";
        cout << "4. Edit Client\n";
        cout << "5. Delete Client\n\n";
        cout << "6. View all Items\n";
        cout << "7. Sort Items by Price\n";
        cout << "8. Filter Items\n";
        cout << "9. Search Items\n";
        cout << "10. Add new Item\n";
        cout << "11. Edit Item\n";
        cout << "12. Delete Item\n\n";
        cout << "13. User Guide\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: pawnshop.displayClients(); break;
            case 2: pawnshop.searchClient(); break;
            case 3: pawnshop.addClient(); break;
            case 4: pawnshop.editClient(); break;
            case 5: pawnshop.removeClient(); break;
            case 6: pawnshop.displayItems(); break;
            case 7: pawnshop.sortItemsByPrice(); break;
            case 8: pawnshop.filterItems(); break;
            case 9: pawnshop.searchItem(); break;
            case 10: pawnshop.addItem(); break;
            case 11: pawnshop.editItem(); break;
            case 12: pawnshop.removeItem(); break;
            case 13: userGuide(); break;
            case 14: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 14);
}