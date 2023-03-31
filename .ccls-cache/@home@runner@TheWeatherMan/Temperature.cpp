#include "Temperature.h"

Temperature::Temperature(float high, float low)
{
  this->high = high;
  this->low = low;
}

float Temperature::getHigh() const
{
  return high;
}

float Temperature::getLow() const
{
  return low;
}