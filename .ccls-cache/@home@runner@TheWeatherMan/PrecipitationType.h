#ifndef PRECIPITATIONTYPE_H
#define PRECIPITATIONTYPE_H

#include <iostream>

using namespace std;

class PrecipitationType
{
  private:
    float amount;
  public:
    PrecipitationType();
    PrecipitationType(float amount);
    float getAmount() const;
    virtual void write(ostream &out) const;
};

class rain : public PrecipitationType
{
  public:
    rain(float amount);
    void write(ostream &out) const;
};

class snow : public PrecipitationType
{
  public:
    snow(float amount);
    void write(ostream &out) const;
};

class hail : public PrecipitationType
{
  public:
    hail(float amount);
    void write(ostream &out) const;
};

class freezingRain : public PrecipitationType
{
  public:
    freezingRain(float amount);
    void write(ostream &out) const;
};

class fog : public PrecipitationType
{
  public:
    fog();
    void write(ostream &out) const;
};

#endif