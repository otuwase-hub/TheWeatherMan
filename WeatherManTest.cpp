#include "WeatherMan.h"

int main() 
{
  WeatherMan *ono = WeatherMan::getWeatherMan();
  ono->initialize(cout, cin);
  while(ono->processChoice(cout, cin));
  cout << "END OF PROGRAM" << endl;
}