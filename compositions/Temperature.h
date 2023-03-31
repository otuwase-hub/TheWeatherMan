#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <iostream>

using namespace std;

class Temperature
{
  private:
    int high;
    int low;
  public:
    Temperature();
    Temperature(int high, int low);
    void read(istream &in);
    void write(ostream &out) const;
    int getHigh() const;
    int getLow() const;
};

#endif