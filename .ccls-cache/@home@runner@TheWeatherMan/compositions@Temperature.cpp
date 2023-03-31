#include "Temperature.h"

Temperature::Temperature(){}

Temperature::Temperature(int high, int low)
{
  this->high = high;
  this->low = low;
}

int Temperature::getHigh() const
{
  return high;
}

int Temperature::getLow() const
{
  return low;
}

void Temperature::read(istream &in)
{
  cout << "Enter low: ";
  in >> low;
  cout << "Enter high: ";
  in >> high;
}

void Temperature::write(ostream &out) const
{
  out << "[" << low << " " << high << "]";
}