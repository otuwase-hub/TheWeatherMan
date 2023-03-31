#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <iostream>

using namespace std;

class Temperature
{
  private:
    float high;
    float low;
  public:
    Temperature(float high, float low);
    void read(istream &in);
    float getHigh() const;
    float getLow() const;
};

#endif