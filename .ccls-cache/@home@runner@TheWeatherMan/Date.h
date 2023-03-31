#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>

using namespace std;

const static vector<string> Months  = 
{
  "January", "February", "March", "April", "May", "June", 
  "July", "August", "September", "October", "November", "December"
};

class Date
{
  private:
    int day;
    int month;
    int year;
  public:
    Date(string date);
    Date(int day, int month, int year);
    string GetDate(string format);
    void read(istream &in);
    void parse(string date);
    static bool isGreaterThan(Date date1, Date date2);
    static bool equals(Date date1, Date date2);
};

#endif