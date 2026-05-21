#pragma once

#include<string>
using namespace std;

class Date{
public:
    static string getCurrentDate();
    static string calculateDueDate(int days=30);
    static int daysBetween(const string&date1,const string&date2);
};