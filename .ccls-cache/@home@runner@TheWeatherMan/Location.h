#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <vector>

using namespace std;

class Location
{
  private:
    string city;
    string province;
  public:
    Location(string location);
    Location(string city, string location);
    void read(istream &in);
    void parse(string location);
    string GetLocation();
    static bool equals(Location location1, Location location2);
};

#endif