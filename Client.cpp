#include "Client.h"

using namespace std;

Client::Client(int id, const string& name, const string& phone) : id(id), name(name), phone(phone) {}

Client::Client(const Client& other) : id(other.id), name(other.name), phone(other.phone) {}

Client::Client(Client&& other) noexcept : id(other.id), name(move(other.name)), phone(move(other.phone)) {
    other.id = 0;
}

Client::~Client() { if (!id == 0) { cout << "[DEBUG] Object Client (ID " << id << ") destroyed!\n"; } }


int Client::getId() const { return id; }
void Client::setId(int id) { this->id = id; }

string Client::getName() const { return name; }
void Client::setName(const string& name) { this->name = name; }

string Client::getPhone() const { return phone; }
void Client::setPhone(const string& phone) { this->phone = phone; }

void Client::display() const {
    cout << "| ID: " << id << "\t| Name: " << name << "\t| Phone: " << phone << "\t|\n";
}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        phone = other.phone;
    }
    return *this;
}

Client& Client::operator=(Client&& other) noexcept {
    if (this != &other) {
        id = other.id;
        name = move(other.name);
        phone = move(other.phone);
        other.id = 0;
    }
    return *this;
}
