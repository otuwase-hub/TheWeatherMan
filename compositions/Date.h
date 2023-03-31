#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Date
{
  private:
    int day;
    int month;
    int year;
  public:
    Date();
    Date(string date);
    Date(int day, int month, int year);
    void write(ostream &out) const;
    void read(istream &in);
    void parse(string date);
    static bool isGreaterThan(Date date1, Date date2);
    static bool equals(Date date1, Date date2);
};

#endif