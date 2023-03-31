#include "PrecipitationType.h"

PrecipitationType::PrecipitationType(){}

PrecipitationType::PrecipitationType(float amount)
{
  this->amount = amount;
}

float PrecipitationType::getAmount() const
{
  return amount;
}

rain::rain(float amount) : PrecipitationType(amount){}

void rain::write(ostream &out) const
{
  out << getAmount() << "mm";
}

snow::snow(float amount) : PrecipitationType(amount){}

void snow::write(ostream &out) const
{
  out << getAmount() << "cm";
}

hail::hail(float amount) : PrecipitationType(amount){}

void hail::write(ostream &out) const
{
  out << getAmount();
}

freezingRain::freezingRain(float amount) : PrecipitationType(amount){}

void freezingRain::write(ostream &out) const
{
  out << getAmount() << "mm";
}

fog::fog() : PrecipitationType(){}