#ifndef WEATHERCONDITIONS_H
#define WEATHERCONDITIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "../compositions/PrecipitationType.h"
#include "../compositions/Temperature.h"
#include "../compositions/Date.h"
#include "../compositions/Location.h"

using namespace std;

const static string beaufort[] = 
{
  "Calm", "Light Air", "Light Breeze", "Gentle Breeze", "Moderate Breeze",
  "Fresh Breeze", "Strong Breeze", "High Wind", "Fresh Gale", "Strong Gale", "Storm",
  "Violent Storm", "Hurricane Force"
};

// base class
class WeatherCondition 
{
 friend class SeaState;
  private:
    Date date;
    Location location;
    Temperature temperature;
  public:
    WeatherCondition();
    WeatherCondition(Date date, Location location, Temperature temperature);
    void setDate(Date date);
    void setLocation(Location location);
    void setTemperature(Temperature temperature);
    Date getDate();
    Location getLocation();
    Temperature getTemperature();
    virtual bool read(istream &in);
    virtual void write(ostream &out) const;
};

class Precipitation: public WeatherCondition
{
  private:
    PrecipitationType *type;
  public:
    Precipitation();
    Precipitation(Date date, Location location, Temperature temperature, PrecipitationType *type);
    Precipitation(Date date, Location location, Temperature temperature);
    void setType(PrecipitationType *type);
    bool read(istream &in);
    void write(ostream &out) const;
};

class Wind: public WeatherCondition
{
  private:
    float speed;
    string direction;
    int beaufortNumber;
    string description;
  public:
    Wind();
    Wind(Date date, Location location, Temperature temperature, float speed, string direction);
    void setBeaufort();
    bool read(istream &in);
    void write(ostream &out) const;
};

class SeaState: public WeatherCondition
{
  private:
    float height;
    int period;
    float waterTemperature;
  public:
    SeaState();
    SeaState(Date date, Location location, Temperature temperature, float height, int period, float waterTemperature);
    bool read(istream &in);
    void write(ostream &out) const;
};

#endif /* WEATHERCONDITIONS_H */