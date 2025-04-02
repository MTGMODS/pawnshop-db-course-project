#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "Client.h"

using namespace std;

class Item {
private:
    int id;
    string name;
    double appraisalValue;
    double loanAmount;
    string pledgeDate;
    string storagePeriod;
    Client owner;

public:
    Item();
    Item(int id, const string& name, double appraisalValue, double loanAmount,
         const string& pledgeDate, const string& storagePeriod, const Client& owner);
    Item(const Item& other);
    Item(Item&& other) noexcept;

    ~Item();

    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    double getAppraisalValue() const;
    void setAppraisalValue(double value);

    double getLoanAmount() const;
    void setLoanAmount(double amount);

    string getPledgeDate() const;
    void setPledgeDate(const string& date);

    string getStoragePeriod() const;
    void setStoragePeriod(const string& period);

    Client getOwner() const;
    void setOwner(const Client& owner);

    void display() const;

    Item& operator=(const Item& other);
    Item& operator=(Item&& other) noexcept;
};

#endif // ITEM_H
