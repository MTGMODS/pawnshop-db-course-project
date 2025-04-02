#ifndef PAWNSHOP_H
#define PAWNSHOP_H

#include <vector>
#include <string>
#include "Client.h"
#include "Item.h"

using namespace std;

class Pawnshop {
private:
    vector<Client> clients;
    vector<Item> items;
public:
    Pawnshop();

    void displayClients() const;
    void addClient();
    void searchClient();
    void editClient();
    void removeClient();

    void displayItems() const;
    void addItem();
    void searchItem();
    void sortItems();
    void filterItems();
    void sortItemsByPrice();
    void editItem();
    void removeItem();

    void saveDataToFile(const string& filename) const;
    void loadDataFromFile(const string& filename);
};

#endif // PAWNSHOP_H
