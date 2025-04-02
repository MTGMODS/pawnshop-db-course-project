#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

using namespace std;

class Client {
private:
    int id;
    string name;
    string phone;
public:
    Client(int id, const string& name, const string& phone);
    Client(const Client& other);
    Client(Client&& other) noexcept;

    ~Client();

    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    string getPhone() const;
    void setPhone(const string& phone);

    void display() const;

    Client& operator=(const Client& other);
    Client& operator=(Client&& other) noexcept;
};

#endif // CLIENT_H
