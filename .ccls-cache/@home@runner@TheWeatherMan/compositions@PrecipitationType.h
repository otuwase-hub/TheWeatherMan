#ifndef PRECIPITATIONTYPE_H
#define PRECIPITATIONTYPE_H

#include <iostream>
#include <iomanip>

using namespace std;

class PrecipitationType
{
  private:
    float amount;
  public:
    PrecipitationType();
    PrecipitationType(float amount);
    float getAmount() const;
    virtual void read(istream &in);
    virtual void write(ostream &out) const;
};

class Rain : public PrecipitationType
{
  public:
    Rain(float amount);
    void write(ostream &out) const;
};

class Snow : public PrecipitationType
{
  public:
    Snow(float amount);
    void write(ostream &out) const;
};

class Hail : public PrecipitationType
{
  public:
    Hail(float amount);
    void write(ostream &out) const;
};

class FreezingRain : public PrecipitationType
{
  public:
    FreezingRain(float amount);
    void write(ostream &out) const;
};

class Fog : public PrecipitationType
{
  public:
    Fog();
    void write(ostream &out) const;
};

#endif