#include "Manager.h"
#include "Date.h"
#include <algorithm>
#include <cstdio>
#include <iostream>

int Manager::id_counter = 0;
const string Manager::BOOKS_FILE = "books.dat";
const string Manager::READERS_FILE = "readers.dat";
const string Manager::RECORDS_FILE = "records.dat";

Manager &Manager::getInstance() {
    static Manager instance;
    return instance;
}

void Manager::init() {
    loadBooks();
    loadReaders();
    loadRecords();
    cout << "Load" << books.size() << " books, " << readers.size()
         << " readers, " << records.size() << " records." << endl;
}

void Manager::saveAllData() {
    saveBooks();
    saveReaders();
    saveRecords();
}

bool Manager::addBook(const Book &book) {
    if (findBookIndex(book.getIsbn()) != -1) {
        cout << "failed to add book. This book is exist!\n";
        return false;
    }
    books.push_back(book);
    saveBooks();
    cout << "success: add " << book.getIsbn() << endl;
    return true;
}

bool Manager::deleteBook(const string &isbn) {
    int idx = findBookIndex(isbn);
    if (idx == -1) {
        cout << "failed to delete. This book is not exist!\n";
        return false;
    }
    for (const auto &r : records) {
        if (r.getIsbn() == isbn && !r.getIsReturned()) {
            cout << "failed to delete. This book has unreturned record!\n";
            return false;
        }
    }
    books.erase(books.begin() + idx);
    saveBooks();
    cout << "success: delete " << isbn << endl;
    return true;
}

bool Manager::updateBook(const string &isbn, int field, const string &value) {
    int idx = findBookIndex(isbn);
    if (idx == -1)
        return false;
    Book &b = books[idx];
    switch (field) {
    case 1:
        b.setTitle(value);
        break;
    case 2:
        b.setAuthor(value);
        break;
    case 3:
        b.setPublisher(value);
        break;
    case 6:
        b.setCategory(value);
        break;
    default:
        return false;
    }
    saveBooks();
    return true;
}

bool Manager::updateBookInt(const string &isbn, int field, int value) {
    int idx = findBookIndex(isbn);
    if (idx == -1)
        return false;
    Book &b = books[idx];
    switch (field) {
    case 4:
        b.setPublishYear(value);
        break;
    case 5:
        if (value < b.getBorrowedCount())
            return false;
        b.setTotalCopies(value);
        break;
    }
    saveBooks();
    return true;
}

bool Manager::updateBookDouble(const string &isbn, int field, double value) {
    int idx = findBookIndex(isbn);
    if (idx == -1)
        return false;
    Book &b = books[idx];
    if (field == 7) {
        b.setPrice(value);
        saveBooks();
        return true;
    }
    return false;
}

vector<Book> Manager::searchBooksByIsbn(const string &isbn) const {
    vector<Book> result;
    for (const auto &b : books) {
        if (b.getIsbn() == isbn)
            result.push_back(b);
    }
    return result;
}

vector<Book> Manager::searchBooksByTitle(const string &keyword) const {
    vector<Book> result;
    for (const auto &b : books) {
        if (b.getTitle().find(keyword) != string::npos)
            result.push_back(b);
    }
    return result;
}

vector<Book> Manager::searchBooksByAuthor(const string &author) const {
    vector<Book> result;
    for (const auto &b : books) {
        if (b.getAuthor().find(author) != string::npos)
            result.push_back(b);
    }
    return result;
}

vector<Book> Manager::searchBooksByCategory(const string &category) const {
    vector<Book> result;
    for (const auto &b : books) {
        if (b.getCategoty() == category)
            result.push_back(b);
    }
    return result;
}

const vector<Book> &Manager::getAllBooks() const { return books; }

bool Manager::addReader(Reader &reader) {
    reader.setReaderId(generateId("R"));
    reader.setRegisterDate(Date::getCurrentDate());
    readers.push_back(reader);
    saveReaders();
    return true;
}

bool Manager::deleteReader(const string &readerId) {
    int idx = findReaderIndex(readerId);
    if (idx == -1)
        return false;
    if (readers[idx].getBorrowedCount() > 0)
        return false;
    readers.erase(readers.begin() + idx);
    saveReaders();
    return true;
}

vector<Reader> Manager::searchReadersById(const string &id) const {
    vector<Reader> result;
    for (const auto &r : readers) {
        if (r.getId() == id)
            result.push_back(r);
    }
    return result;
}

vector<Reader> Manager::searchReadersByName(const string &name) const {
    vector<Reader> result;
    for (const auto &r : readers) {
        if (r.getName().find(name) != string::npos)
            result.push_back(r);
    }
    return result;
}

vector<Reader> Manager::searchReadersByPhone(const string &phone) const {
    vector<Reader>result;
    for(const auto&r:readers){
        if(r.getPhone()==phone)result.push_back(r);
    }
    return result;
}

const vector<Reader> &Manager::getAllReaders() const {
    return readers;
}

string Manager::generateId(const string &prefix) {
    char buffer[30];
    string date = Date::getCurrentDate();
    sprintf(buffer, "%s%s%04d", prefix.c_str(), date.c_str(), ++id_counter);
    string id(buffer);
    return id;
}

void Manager::saveBooks() {
    ofstream ofs(BOOKS_FILE);
    if (!ofs) {
        cout << "error: failed to save books data!\n";
        return;
    }
    ofs << books.size() << "\n";
    for (const auto &b : books) {
        b.serialize(ofs);
    }
    ofs.close();
}

void Manager::loadBooks() {
    ifstream ifs(BOOKS_FILE);
    if (!ifs)
        return;
    size_t count;
    ifs >> count;
    ifs.ignore();
    books.clear();
    for (size_t i = 0; i < count; i++) {
        Book b;
        b.deserialize(ifs);
        books.push_back(b);
    }
    ifs.close();
}

void Manager::saveReaders() {
    ofstream ofs(READERS_FILE);
    if (!ofs) {
        cout << "error: failed to save readers' data!\n";
        return;
    }
    ofs << readers.size() << "\n";
    for (const auto &r : readers)
        r.serialize(ofs);
    ofs.close();
}

void Manager::loadReaders() {
    ifstream ifs(READERS_FILE);
    if (!ifs)
        return;
    size_t count;
    ifs >> count;
    ifs.ignore();
    readers.clear();
    for (size_t i = 0; i < count; i++) {
        Reader r;
        r.deserialize(ifs);
        readers.push_back(r);
    }
    ifs.close();
}

void Manager::saveRecords() {
    ofstream ofs(RECORDS_FILE);
    if (!ofs) {
        cout << "error: failed to save records' data!\n" << endl;
        return;
    }
    ofs << records.size() << "\n";
    for (const auto &r : records)
        r.serialize(ofs);
    ofs.close();
}

void Manager::loadRecords() {
    ifstream ifs(RECORDS_FILE);
    if (!ifs)
        return;
    size_t count;
    ifs >> count;
    ifs.ignore();
    records.clear();
    for (size_t i = 0; i < count; i++) {
        BorrowRecord r;
        r.deserialize(ifs);
        records.push_back(r);
    }
    ifs.close();
}

int Manager::findBookIndex(const string &isbn) const {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn)
            return i;
    }
    return -1;
}

int Manager::findReaderIndex(const string &id) const {
    for (int i = 0; i < readers.size(); i++) {
        if (readers[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

int Manager::findRecordIndex(const string &id) const {
    for (int i = 0; i < records.size(); i++) {
        if (records[i].getRecordId() == id)
            return i;
    }
    return -1;
}
