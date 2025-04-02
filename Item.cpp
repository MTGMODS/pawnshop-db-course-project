#include "Item.h"

using namespace std;

Item::Item(int id, const string& name, double appraisalValue, double loanAmount, const string& pledgeDate, const string& storagePeriod, const Client& owner)
    : id(id), name(name), appraisalValue(appraisalValue), loanAmount(loanAmount), pledgeDate(pledgeDate), storagePeriod(storagePeriod), owner(owner) {}

Item::Item(const Item& other) : id(other.id), name(other.name), appraisalValue(other.appraisalValue), loanAmount(other.loanAmount), pledgeDate(other.pledgeDate), storagePeriod(other.storagePeriod), owner(other.owner) {}

Item::Item(Item&& other) noexcept : id(other.id), name(move(other.name)), appraisalValue(other.appraisalValue), loanAmount(other.loanAmount), pledgeDate(move(other.pledgeDate)), storagePeriod(move(other.storagePeriod)), owner(move(other.owner)) {
    other.id = 0;
}

Item::~Item() { if (!id == 0) {cout << "[DEBUG] Item object with ID " << id << " destroyed.\n";}}

int Item::getId() const { return id; }
void Item::setId(int id) { this->id = id; }

string Item::getName() const { return name; }
void Item::setName(const string& name) { this->name = name; }

double Item::getAppraisalValue() const { return appraisalValue; }
void Item::setAppraisalValue(double value) { this->appraisalValue = value; }

double Item::getLoanAmount() const { return loanAmount; }
void Item::setLoanAmount(double amount) { this->loanAmount = amount; }

string Item::getPledgeDate() const { return pledgeDate; }
void Item::setPledgeDate(const string& date) { this->pledgeDate = date; }

string Item::getStoragePeriod() const { return storagePeriod; }
void Item::setStoragePeriod(const string& period) { this->storagePeriod = period; }

Client Item::getOwner() const { return owner; }
void Item::setOwner(const Client& owner) { this->owner = owner; }


void Item::display() const {
    cout << "Item ID: " << id << "\nName: " << name
              << "\nAppraisal Value: $" << appraisalValue
              << "\nLoan Amount: $" << loanAmount
              << "\nPledge Date: " << pledgeDate
              << "\nStorage Period: " << storagePeriod << "\nOwner:\n";
    owner.display();
}


Item& Item::operator=(const Item& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        appraisalValue = other.appraisalValue;
        loanAmount = other.loanAmount;
        pledgeDate = other.pledgeDate;
        storagePeriod = other.storagePeriod;
        owner = other.owner;
    }
    return *this;
}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        id = other.id;
        name = move(other.name);
        appraisalValue = other.appraisalValue;
        loanAmount = other.loanAmount;
        pledgeDate = move(other.pledgeDate);
        storagePeriod = move(other.storagePeriod);
        owner = move(other.owner);
        other.id = 0;
    }
    return *this;
}
