#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <vector>
#include "../utils/utils.h"

using namespace std;
using namespace utils;

class Location
{
  private:
    string city;
    string province;
  public:
    Location();
    Location(string location);
    Location(string city, string province);
    void read(istream &in);
    void read(istream &in, string key);
    void parse(string location);
    void write(ostream &out) const;
    bool seaState();
    static bool cityMatch(Location location1, Location location2);
    static bool provinceMatch(Location location1, Location location2);
    static bool equals(Location location1, Location location2);
};

#endif