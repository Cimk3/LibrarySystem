#include "Reader.h"
#include <iomanip>
#include <iostream>

Reader::Reader()
    : id(""), name(""), phone(""), email(""), address(""), maxBorrow(5),
      borrowedCount(0), registerDate("") {}

Reader::Reader(const string &id, const string &name)
    : id(id), name(name), phone(""), email(""), address(""), maxBorrow(5),
      borrowedCount(0), registerDate("") {}

void Reader::setReaderId(const string &id) { this->id = id; }

void Reader::setName(const string &name) { this->name = name; }

void Reader::setPhone(const string &phone) { this->phone = phone; }

void Reader::setEmail(const string &email) { this->email = email; }

void Reader::setAddress(const string &address) { this->address = address; }

void Reader::setMaxBorrow(int max) { this->maxBorrow = max; }

void Reader::setBorrowedCount(int count) { this->borrowedCount = count; }

void Reader::setRegisterDate(const string &date) { this->registerDate = date; }

bool Reader::canBorrow() const { return borrowedCount < maxBorrow; }

void Reader::borrowOne() {
    if (canBorrow())
        borrowedCount++;
    else
        return;
}

void Reader::returnOne() {
    if (borrowedCount > 0)
        borrowedCount--;
    else
        return;
}

void Reader::serialize(ofstream &ofs) const {
    ofs << id << "\n"
        << name << "\n"
        << phone << "\n"
        << email << "\n"
        << address << "\n"
        << maxBorrow << "\n"
        << borrowedCount << "\n"
        << registerDate << "\n";
}

void Reader::deserialize(ifstream &ifs) {
    getline(ifs, id);
    getline(ifs, name);
    getline(ifs, phone);
    getline(ifs, email);
    getline(ifs, address);
    ifs >> maxBorrow;
    ifs >> borrowedCount;
    ifs.ignore();
    getline(ifs, registerDate);
}

void Reader::display() const {
    cout << left << setw(15) << id << setw(12) << name << setw(15) << phone
         << setw(8) << borrowedCount << setw(8) << this->getRemaining() << endl;
}

void Reader::displayHeader() {
    cout << left << setw(15) << "Reader Id" << setw(12) << "Reader Name"
         << setw(15) << "Phone" << setw(8) << "Borrow Counts" << setw(8)
         << "Remaining Borrow Counts" << endl;
    cout << string(70, '-') << endl;
}
