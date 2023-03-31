#include "Location.h"

Location::Location(){}

Location::Location(string location)
{
  parse(location);
}

Location::Location(string city, string province)
{
  this->city = city;
  this->province = province;
}

void Location::read(istream &in)
{
  cout << "Enter city: ";
  in >> city;
  cout << "Enter province: ";
  in >> province;
}

void Location::read(istream &in, string key)
{
  if(key == "city")
  {
    cout << "Enter city: ";
    in >> city;
  }
  else if(key == "province")
  {
    cout << "Enter province: ";
    in >> province;
  }
  else if(key == "location")
  {
    read(in);
  }
}

void Location::parse(string location)
{
  bool commaFound = false;
  for(int i = 0; i < location.length(); i++)
  {
    if(commaFound)
    {
      if(location[i] != ' ')
        province += location[i];
    }
    else
    {
      if(location[i] == ',')
      {
        commaFound = true;
      }
      else
      {
        if(location[i] != ' ')
          city += location[i];
      }
    }
  }
}

void Location::write(ostream &out) const
{
  out << "[" << city << ", " << province << "]";
}

bool Location::cityMatch(Location location1, Location location2)
{
  return (toUpper(location1.city) == toUpper(location2.city));
}

bool Location::provinceMatch(Location location1, Location location2)
{
  return (toUpper(location1.province) == toUpper(location2.province));
}

bool Location::equals(Location location1, Location location2)
{
  return (toUpper(location1.city) == toUpper(location2.city) && toUpper(location1.province) == toUpper(location2.province));
}

bool Location::seaState()
{
  // checks if location is in a list of locations with sea states
  return true;
}
