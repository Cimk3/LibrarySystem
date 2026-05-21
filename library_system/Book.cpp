#include "Book.h"
#include <iostream>
#include <iomanip>

Book::Book(){
    isbn="";
    title="";
    author="";
    publisher="";
    publishYear=0;
    totalCopies=0;
    availableCopies=0;
    categoty="";
    price=0.0;
}

Book::Book(const std::string&isbn,const std::string&title,const std::string&author,
        const std::string&publisher,int year,int copies,const std::string&categoty,
        double price)
        :isbn(isbn),title(title),author(author),publisher(publisher),
         publishYear(year),totalCopies(copies),availableCopies(copies),
         categoty(categoty),price(price){}

std::string Book::getIsbn()const{
    return this->isbn;
}

std::string Book::getTitle()const{
    return this->title;
}

std::string Book::getAuthor()const{
    return this->author;
}

std::string Book::getPublisher()const{
    return this->publisher;
}

int Book::getPublishYear()const{
    return this->publishYear;
}

int Book::getTotalCopies()const{
    return this->totalCopies;
}

int Book::getAvailableCopies()const{
    return this->availableCopies;
}

std::string Book::getCategoty()const{
    return this->categoty;
}

double Book::getPrice()const{
    return this->price;
}

int Book::getBorrowedCount()const{
    return this->totalCopies-this->availableCopies;
}

void Book::setTitle(const std::string &title){
    this->title=title;
}

void Book::setAuthor(const std::string &author){
    this->author=author;
}

void Book::setPublisher(const std::string &publihser){
    this->publisher=publihser;
}

void Book::setPublishYear(int year){
    this->publishYear=year;
}

void Book::setTotalCopies(int count){
    this->totalCopies=count;
    availableCopies=count-getBorrowedCount();
    if(availableCopies<0){
        availableCopies=0;
    }
}

void Book::setCategory(const std::string &category){
    this->categoty=category;
}

void Book::setPrice(double price){
    this->price=price;
}

bool Book::isAvailable() const{
    return availableCopies>0;
}

void Book::borrowOne(){
    if(availableCopies>0)
        availableCopies--;
    else
        return;
}

void Book::returnOne(){
    if(availableCopies<totalCopies)
        availableCopies++;
    else
        return;
}

void Book::serialize(std::ofstream &ofs) const{
    ofs<<isbn<<"\n"
       <<title<<"\n"
       <<author<<"\n"
       <<publisher<<"\n"
       <<publishYear<<"\n"
       <<totalCopies<<"\n"
       <<availableCopies<<"\n"
       <<categoty<<"\n"
       <<price<<"\n" ;
}

void Book::deserialize(std::ifstream &ifs){
    std::getline(ifs,isbn);
    std::getline(ifs,title);
    std::getline(ifs,author);
    std::getline(ifs,publisher);
    ifs>>publishYear;
    ifs>>totalCopies;
    ifs>>availableCopies;
    ifs.ignore();
    std::getline(ifs,categoty);
    ifs>>price;
    ifs.ignore();
}

void Book::displayHeader(){
    std::cout<<std::left<<std::setw(15)<<"ISBN"
             <<std::setw(32)<<"Title"
             <<std::setw(24)<<"Author"
             <<std::setw(16)<<"Category"
             <<std::setw(10)<<"Availavle Copies"
             <<std::setw(6)<<"Total Copies"
             <<std::setw(8)<<"Price"<<std::endl;
    std::cout<<std::string(85,'-')<<std::endl;
}

void Book::display(){
    std::string shortTitle=getTitle().length()>100?getTitle().substr(0,50)+"...":getTitle();
    std::string shortAuthor=getAuthor().length()>60?getAuthor().substr(0,30)+"...":getAuthor();
    std::cout<<std::left<<std::setw(15)<<getIsbn()
             <<std::setw(32)<<shortTitle
             <<std::setw(24)<<shortAuthor
             <<std::setw(16)<<getCategoty()
             <<std::setw(10)<<getAvailableCopies
             <<std::setw(6)<<getTotalCopies
             <<std::setw(8)<<getPrice()<<std::endl;
}
