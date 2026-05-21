#pragma once
#include<string>
#include<fstream>
using namespace std;

class Reader{
private:
    string id;
    string name;
    string phone;
    string email;
    string address;
    int maxBorrow;
    int borrowedCount;
    string registerDate;
public:
    Reader();
    Reader(const string&id,const string&name);

    string getId()const{return id;}
    string getName()const{return name;}
    string getPhone()const{return phone;}
    string getEmail()const{return email;}
    string getAddress()const{return address;}
    int getMaxBorrow()const{return maxBorrow;}
    int getBorrowedCount()const{return borrowedCount;}
    string getRegisterDate()const{return registerDate;}
    int getRemaining()const{return maxBorrow-borrowedCount;}

    void setReaderId(const string& id);
    void setName(const string& name);
    void setPhone(const string& phone);
    void setEmail(const string& email);
    void setAddress(const string& address);
    void setMaxBorrow(int max);
    void setBorrowedCount(int count);
    void setRegisterDate(const string& date);

    bool canBorrow()const;
    void borrowOne();
    void returnOne();

    void serialize(ofstream& ofs)const;
    void deserialize(ifstream& ifs);
    void display() const;
    static void displayHeader();
};