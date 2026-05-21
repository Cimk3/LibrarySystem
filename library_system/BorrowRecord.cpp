#include "BorrowRecord.h"
#include"Date.h"
#include<iostream>
#include<iomanip>

BorrowRecord::BorrowRecord()
    : recordId(""), readerId(""), isbn(""),
      borrowDate(""), dueDate(""), returnDate(""),
      isReturned(false), fine(0.0) {}

BorrowRecord::BorrowRecord(const string &recordId, const string &readerId,
                           const string &isbn) 
                           : recordId(recordId), readerId(readerId), isbn(isbn),
                             borrowDate(""), dueDate(""), returnDate(""),
                             isReturned(false), fine(0.0) {}

void BorrowRecord::setRecordId(const string &id) {
    this->recordId=id;
}

void BorrowRecord::setReaderId(const string &id) {
    this->readerId=id;
}

void BorrowRecord::setIsbn(const string &isbn) {
    this->isbn=isbn;
}

void BorrowRecord::setBorrowDate(const string &date) {
    this->borrowDate=date;
}

void BorrowRecord::setDueDate(const string &date) {
    this->dueDate=date;
}

void BorrowRecord::setReturnDate(const string &date) {
    this->returnDate=date;
}

void BorrowRecord::setIsReturned(bool returned) {
    this->isReturned=returned;
}

void BorrowRecord::setFine(double fine) {
    this->fine=fine;
}

void BorrowRecord::doReturn(const string &returnDate) {
    this->returnDate=returnDate;
    this->isReturned=true;
    this->fine=calculateFine(returnDate);
}

double BorrowRecord::calculateFine(const string &today) const {
    int over_due_days=getOverdueDays(today);
    if(over_due_days>0){
        return over_due_days*0.5;
    }
    return 0.0;
}

int BorrowRecord::getOverdueDays(const string &today) const {
    return Date::daysBetween(dueDate,today);
}

bool BorrowRecord::isOverdue(const string &today) const {
    return !isReturned&&getOverdueDays(today)>0;
}

void BorrowRecord::serialize(ofstream &ofs) const {
    ofs << recordId << "\n"
        << readerId << "\n"
        << isbn << "\n"
        << borrowDate << "\n"
        << dueDate << "\n"
        << returnDate << "\n"
        << isReturned << "\n"
        << fine << "\n";
}

void BorrowRecord::deserialize(ifstream &ifs) {
    getline(ifs, recordId);
    getline(ifs, readerId);
    getline(ifs, isbn);
    getline(ifs, borrowDate);
    getline(ifs, dueDate);
    getline(ifs, returnDate);
    ifs >> isReturned;
    ifs >> fine;
    ifs.ignore();
}

void BorrowRecord::display() const {
    cout << left << setw(15) << recordId
         << setw(15) << readerId
         << setw(15) << isbn
         << setw(12) << borrowDate
         << setw(12) << dueDate
         << setw(8)  << (isReturned ? "Returned" : "Not Returned")
         << setw(8)  << fine << endl;
}

void BorrowRecord::displayHeader() {
    cout << left << setw(15) << "Record Id"
         << setw(15) << "Reader Id"
         << setw(15) << "ISBN"
         << setw(12) << "Borrow Date"
         << setw(12) << "Due Date"
         << setw(8)  << "Return Status"
         << setw(8)  << "Fine" << endl;
    cout << string(90, '-') << endl;
}
