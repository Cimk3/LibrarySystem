#pragma once

#include<string>
#include<fstream>

class Book{
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string publisher;
    int publishYear;
    int totalCopies;//总册数
    int availableCopies;//可借册数
    std::string categoty;//分类
    double price;

public:
    Book();
    Book(const std::string&isbn,const std::string&title,const std::string&author,
         const std::string&publisher,int year,int copies,const std::string&categoty,
         double price);

    std::string getIsbn()const;
    std::string getTitle()const;
    std::string getAuthor()const;
    std::string getPublisher()const;
    int getPublishYear()const;
    int getTotalCopies()const;
    int getAvailableCopies()const;
    std::string getCategoty()const;
    double getPrice()const;
    int getBorrowedCount()const;
    
    void setTitle(const std::string&title);
    void setAuthor(const std::string&author);
    void setPublisher(const std::string&publihser);
    void setPublishYear(int year);
    void setTotalCopies(int count);
    void setCategory(const std::string&category);
    void setPrice(double price);

    bool isAvailable()const;
    void borrowOne();
    void returnOne();

    void serialize(std::ofstream&ofs)const;
    void deserialize(std::ifstream&ifs);

    void display();
    static void displayHeader();
};

