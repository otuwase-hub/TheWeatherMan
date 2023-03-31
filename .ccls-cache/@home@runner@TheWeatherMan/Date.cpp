#include "Date.h"

Date::Date(string date)
{
  parse(date);
}

bool Date::isGreaterThan(Date date1, Date date2)
{
  if(date1.year != date2.year)
  {
    return date1.year > date2.year;
  }
  if(date1.month != date2.month)
  {
    return date1.month > date2.month;
  }
  return date1.day >= date2.day;
}

bool Date::equals(Date date1, Date date2)
{
  return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}

