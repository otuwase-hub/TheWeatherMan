#include "WeatherConditions.h"

WeatherCondition::WeatherCondition(){}

WeatherCondition::WeatherCondition(Date date, Location location, Temperature temperature)
{
  this->date = date;
  this->location = location;
  this->temperature = temperature;
}

void WeatherCondition::setDate(Date date)
{
  this->date = date;
}

bool WeatherCondition::read(istream &in)
{
  date.read(in);
  location.read(in);
  temperature.read(in);
  return true;
}

void WeatherCondition::write(ostream &out) const
{
  date.write(out);
  out << " ";
  location.write(out);
  out << " ";
  temperature.write(out);
  out << " ";
}

void WeatherCondition::setLocation(Location location)
{
  this->location = location;
}

void WeatherCondition::setTemperature(Temperature temperature)
{
  this->temperature = temperature;
}

Date WeatherCondition::getDate()
{
  return date;
}

Location WeatherCondition::getLocation()
{
  return location;
}

Temperature WeatherCondition::getTemperature()
{
  return temperature;
}

Precipitation::Precipitation(){}

Precipitation::Precipitation(Date date, Location location, Temperature temperature, PrecipitationType *type) : WeatherCondition(date, location, temperature)
{
  this->type = type;
}

Precipitation::Precipitation(Date date, Location location, Temperature temperature) : WeatherCondition(date, location, temperature){}

void Precipitation::setType(PrecipitationType *type)
{
  this->type = type;
}

bool Precipitation::read(istream &in)
{
  WeatherCondition::read(in);
  type->read(in);
  return true;
}

void Precipitation::write(ostream &out) const
{
  out << "Precipitation:: ";
  WeatherCondition::write(out);
  type->write(out);
}

Wind::Wind(){}

Wind::Wind(Date date, Location location, Temperature temperature, float speed, string direction) : WeatherCondition(date, location, temperature)
{
  this->speed = speed;
  this->direction = direction;
  setBeaufort();
}

void Wind::setBeaufort()
{
  if(speed < 2)
  {
    beaufortNumber = 0;
  }
  else if(speed >= 2 && speed <= 5)
  {
    beaufortNumber = 1;
  }
  else if(speed >= 6 && speed <= 11)
  {
    beaufortNumber = 2;
  }
  else if(speed >= 12 && speed <= 19)
  {
    beaufortNumber = 3;
  }
  else if(speed >= 20 && speed <= 28)
  {
    beaufortNumber = 4;
  }
  else if(speed >= 29 && speed <= 38)
  {
    beaufortNumber = 5;
  }
  else if(speed >= 39 && speed <= 49)
  {
    beaufortNumber = 6;
  }
  else if(speed >= 50 && speed <= 61)
  {
    beaufortNumber = 7;
  }
  else if(speed >= 62 && speed <= 74)
  {
    beaufortNumber = 8;
  }
  else if(speed >= 75 && speed <= 88)
  {
    beaufortNumber = 9;
  }
  else if(speed >= 89 && speed <= 102)
  {
    beaufortNumber = 10;
  }
  else if(speed >= 103 && speed <= 117)
  {
    beaufortNumber = 11;
  }
  else if(speed >= 118)
  {
    beaufortNumber = 12;
  }
  description = beaufort[beaufortNumber];
}

bool Wind::read(istream &in)
{
  WeatherCondition::read(in);
  cout << "Enter speed: ";
  in >> speed;
  cout << "Enter direction: ";
  in >> direction;
  setBeaufort();
  return true;
}

void Wind::write(ostream &out) const
{
  out << "Wind:: ";
  WeatherCondition::write(out);
  cout << fixed;
  cout << setprecision(2) << speed << "km/hr " << direction << " " << description;
}


SeaState::SeaState(){}

SeaState::SeaState(Date date, Location location, Temperature temperature, float height, int period, float waterTemperature) : WeatherCondition(date, location, temperature)
{
  if(!location.seaState())
  {
    cout << "A sea state is the provided location \"";
    location.write(cout);
    cout << "\" is impossible" << endl;
    this->height = -1;
    this->period = -1;
    this->waterTemperature = -1;
  }
  else
  {
    this->height = height;
    this->period = period;
    this->waterTemperature = waterTemperature;
  }
}

bool SeaState::read(istream &in)
{
  location.read(in);
  if(!location.seaState())
  {
    cout << "A sea state is the provided location \"";
    location.write(cout);
    cout << "\" is impossible" << endl;
    return false;
  }
  date.read(in);
  temperature.read(in);
  cout << "Enter wave height: ";
  in >> height;
  cout << "Enter wave period: ";
  in >> period;
  cout << "Enter water temperature: ";
  in >> waterTemperature;
  return true;
}

void SeaState::write(ostream &out) const
{
  out << "Sea State:: ";
  WeatherCondition::write(out);
  cout << fixed;
  cout << setprecision(2) << "[" << height << " m] " << "[" << period << " s] " << "[" << waterTemperature << "C] ";
}
