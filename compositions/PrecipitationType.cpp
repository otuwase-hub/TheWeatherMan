#include "PrecipitationType.h"

PrecipitationType::PrecipitationType()
{
  amount = 0;
}

PrecipitationType::PrecipitationType(float amount)
{
  this->amount = amount;
}

float PrecipitationType::getAmount() const
{
  return amount;
}

void PrecipitationType::read(istream &in)
{
  cout << "Enter amount: ";
  in >> amount;
}

void PrecipitationType::write(ostream &out) const
{
  out << "[" << amount << "]";
}

Rain::Rain(float amount) : PrecipitationType(amount){}

void Rain::write(ostream &out) const
{
  out << fixed;
  out << setprecision(2) << "[rain:" << getAmount() << "mm] ";
}

Snow::Snow(float amount) : PrecipitationType(amount){}

void Snow::write(ostream &out) const
{
  out << fixed;
  out << setprecision(2) << "[snow:" << getAmount() << "cm] ";
}

Hail::Hail(float amount) : PrecipitationType(amount){}

void Hail::write(ostream &out) const
{
  out << fixed;
  out << setprecision(2) << "[hail:" << getAmount() << "] ";
}

FreezingRain::FreezingRain(float amount) : PrecipitationType(amount){}

void FreezingRain::write(ostream &out) const
{
  out << fixed;
  out << setprecision(2) << "[freezing rain:" << getAmount() << "mm] ";
}

Fog::Fog(){}

void Fog::write(ostream &out) const
{
  out << "[fog] ";
}