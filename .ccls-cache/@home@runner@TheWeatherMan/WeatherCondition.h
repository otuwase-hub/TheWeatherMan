#ifndef WEATHERCONDITION_H
#define WEATHERCONDITION_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Temperature.h"
#include "Date.h"
#include "Location.h"

using namespace std;

enum precipitationType {rain, snow, freezingRain, hail, fog};
const static string beaufort[] = 
{
  "Calm", "Light Air", "Light Breeze", "Gentle Breeze", "Moderate Breeze",
  "Fresh Breeze", "Strong Breeze", "High Wind", "Fresh Gale", "Strong Gale", "Storm",
  "Violent Storm", "Hurricane Force"
};

// base class
class WeatherCondition 
{
  private:
    Date date;
    Location location;
    Temperature temperature;
  public:
    WeatherCondition(Date date, Location location, Temperature temperature);
    void setDate(Date date);
    void setLocation(Location location);
    void setTemperature(Temperature temperature);
    Date getDate() const;
    Location getLocation() const;
    Temperature getTemperature() const;
    virtual void read(istream &in);
    virtual void write(ostream &out) const;
};

class Precipitation: public WeatherCondition
{
  private:
    precipitationType type;
    float amount;
  public:
    Precipitation(precipitationType type);
    Precipitation(precipitationType type, float amount);
    void read(istream &in);
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
    Wind(float speed, string direction);
    void read(istream &in);
    void write(ostream &out) const;
};

class SeaState: public WeatherCondition
{
  private:
    float height;
    float period;
    float waterTemperature;
  public:
    SeaState(float height, float period, float waterTemperature);
    void read(istream &in);
    void write(ostream &out) const;
};

#endif /* WEATHERCONDITIONS_H */