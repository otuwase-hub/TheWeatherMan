#ifndef WEATHERSTORE_H
#define WEATHERSTORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "WeatherConditions.h"
#include "utils/utils.h"

using namespace std;
using namespace utils;

enum WeatherConditionType {precipitation, wind, sea, all};

class Entry
{
  friend class WeatherStore;
  private:
    WeatherCondition *data;
    Entry *next;
    Entry *prev;
  public:
    Entry(WeatherCondition *data);
};

class WeatherStore
{
  private:
    Entry *first;
    Entry *last;
    int count;
    bool sort;
  public:
    WeatherStore();
    WeatherStore(bool sort);
    void setSortMode(bool sort);
    bool getSortMode();
    void fread(ifstream &in, WeatherConditionType condition);
    void read(istream &in, WeatherCondition *data);
    int append(WeatherCondition *data);
    int insertSort(WeatherCondition *data);
    void deleteEntry(int index);
    bool empty(bool verbose) const;
    void write(ostream &out) const;
    void searchByDate(ostream &out, istream &in, Date date);
    void searchByLocation(ostream &out, istream &in, Location location, string searchKey);
    int size() const;
};

#endif