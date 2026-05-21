#include"Date.h"
#include<ctime>
#include<cstdio>

string Date::getCurrentDate() {
    time_t now=time(0);
    tm* ltm=localtime(&now);
    char buffer[11];
    sprintf(buffer,"%04d-%02d-%02d",
            1900+ltm->tm_year,1+ltm->tm_mon,ltm->tm_mday
    );
    return string(buffer);
}

string Date::calculateDueDate(int days) {
    time_t now=time(0);
    now+=days*24*60*60;
    tm* ltm=localtime(&now);
    char buffer[11];
    sprintf(buffer,"%04d-%02d-%02d",
            1900+ltm->tm_year,1+ltm->tm_mon,ltm->tm_mday
    );
    return string(buffer);
}

int Date::daysBetween(const string &date1, const string &date2) {
    int y1,y2,m1,m2,d1,d2;
    sscanf(date1.c_str(),"%d-%d-%d",&y1,&m1,&d1);
    sscanf(date2.c_str(),"%d-%d-%d",&y2,&m2,&d2);
    tm tm1={0,0,0,d1,m1-1,y1-1900};
    tm tm2={0,0,0,d2,m2-1,y2-1900};
    time_t t1=mktime(&tm1);
    time_t t2=mktime(&tm2);
    return (int)difftime(t2,t1)/(24*60*60);
}
