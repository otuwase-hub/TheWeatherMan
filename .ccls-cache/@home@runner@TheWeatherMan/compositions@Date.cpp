#include "Date.h"

Date::Date(){}

Date::Date(string date)
{
  parse(date);
}

Date::Date(int day, int month, int year)
{
  this->day = day;
  this->month = month;
  this->year = year;
}

void Date::write(ostream &out) const
{
  out << "[" << day << "/" << month << "/" << year << "]";
}

void Date::parse(string date)
{
  string day, month, year;
  int slashFound = 0;
  for(int i = 0; i < date.length(); i++)
  {
    switch(slashFound)
    {
      case 0:
      {
        if(date[i] == '/')
        {
          slashFound++;
        }
        else
        {
          day += date[i];
        }
        break;
      }
      case 1:
      {
        if(date[i] == '/')
        {
          slashFound++;
        }
        else
        {
          month += date[i];
        }
        break;
      }
      case 2:
      {
        year += date[i];
        break;
      }
    }
  }
  this->day = stoi(day);
  this->month = stoi(month);
  this->year = stoi(year);
}

bool Date::isGreaterThan(Date date1, Date date2)
{
  if(date1.year != date2.year)
  {
    return date1.year < date2.year;
  }
  if(date1.month != date2.month)
  {
    return date1.month < date2.month;
  }
  return date1.day <= date2.day;
}

bool Date::equals(Date date1, Date date2)
{
  return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}

void Date::read(istream &in)
{
  cout << "Enter date: ";
  in >> day >> month >> year;
}

