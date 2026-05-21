#pragma once

#include<string>
#include<fstream>
using namespace std;

class BorrowRecord{
private:
    string recordId;//记录编号
    string readerId;//读者编号
    string isbn;
    string borrowDate;//借书日期
    string dueDate;//应还日期
    string returnDate;//实际归还日期
    bool isReturned;//是否归还
    double fine;//罚款
public:
    BorrowRecord();
    BorrowRecord(const string&recordId,const string&readerId,const string&isbn);

    string getRecordId()const{return this->recordId;}
    string getReaderId()const{return this->readerId;}
    string getIsbn()const{return this->isbn;}
    string getBorrowDate()const{return this->borrowDate;}
    string getDueDate()const{return this->dueDate;}
    string getReturnDate()const{return returnDate;}
    bool getIsReturned()const{return isReturned;}
    double getFine()const{return fine;}

    void setRecordId(const string& id);
    void setReaderId(const string& id);
    void setIsbn(const string& isbn);
    void setBorrowDate(const string& date);
    void setDueDate(const string& date);
    void setReturnDate(const string& date);
    void setIsReturned(bool returned);
    void setFine(double fine);

    void doReturn(const string& returnDate);//执行归还
    double calculateFine(const string& today) const;//计算逾期罚款
    int getOverdueDays(const string& today) const;//逾期天数
    bool isOverdue(const string& today) const;//是否逾期
    
    void serialize(ofstream& ofs) const;
    void deserialize(ifstream& ifs);
    void display() const;
    static void displayHeader();
};