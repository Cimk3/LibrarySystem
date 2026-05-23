#pragma once

#include "Book.h"
#include "BorrowRecord.h"
#include "Reader.h"
#include <string>
#include <vector>

class Manager {
  private:
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> records;

    static int id_counter;

    static const string BOOKS_FILE;
    static const string READERS_FILE;
    static const string RECORDS_FILE;

    Manager() {}

    string generateId(const string &prefix);

    void saveBooks();
    void loadBooks();
    void saveReaders();
    void loadReaders();
    void saveRecords();
    void loadRecords();

    int findBookIndex(const string &isbn) const;
    int findReaderIndex(const string &id) const;
    int findRecordIndex(const string &id) const;

  public:
    static Manager &getInstance();
    Manager(const Manager &) = delete;
    Manager &operator=(const Manager &) = delete;

    void init();
    void saveAllData();

    bool addBook(const Book &book);
    bool deleteBook(const string &isbn);
    bool updateBook(const string &isbn, int field, const string &value);
    bool updateBookInt(const string &isbn, int field, int value);
    bool updateBookDouble(const string &isbn, int field, double value);
    vector<Book> searchBooksByIsbn(const string &isbn) const;
    vector<Book> searchBooksByTitle(const string &keyword) const;
    vector<Book> searchBooksByAuthor(const string &author) const;
    vector<Book> searchBooksByCategory(const string &category) const;
    const vector<Book> &getAllBooks() const;

    bool addReader(Reader &reader); // 会自动分配readerId
    bool deleteReader(const string &readerId);
    vector<Reader> searchReadersById(const string &id) const;
    vector<Reader> searchReadersByName(const string &name) const;
    vector<Reader> searchReadersByPhone(const string &phone) const;
    const vector<Reader> &getAllReaders() const;

    bool borrowBook(const string &readerId, const string &isbn,
                    string &outRecordId);
    bool returnBook(const string &recordId);
    vector<BorrowRecord> searchRecordsByReader(const string &readerId) const;
    vector<BorrowRecord> searchRecordsByIsbn(const string &isbn) const;
    vector<BorrowRecord> getUnreturnedRecords() const;
    const vector<BorrowRecord> &getAllRecords() const;

    struct Statistics {
        int totalBookKinds;  // 图书种类数
        int totalCopies;     // 图书总册数
        int borrowedCopies;  // 已借出册数
        int availableCopies; // 可借册数
        int totalReaders;    // 注册读者数
        int activeReaders;   // 活跃读者数
        int totalRecords;    // 借阅记录总数
        int activeBorrows;   // 当前借阅中
        int overdueCount;    // 逾期记录数
        double totalFine;    // 累计罚款
    };

    Statistics getStatistics() const;
};