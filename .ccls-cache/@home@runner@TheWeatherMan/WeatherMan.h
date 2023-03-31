#ifndef WEATHERMAN_H
#define WEATHERMAN_H

#include <vector>

#include "weatherstore/WeatherStore.h"

class WeatherMan
  {
    public:
      static WeatherMan* getWeatherMan(); // getClassInstance
      void initialize(ostream &out, istream &in); // set sort mode
      void displayMenu(ostream &out, vector<string> &menu); // display menu
      bool processChoice(ostream &out, istream &in); // 
      bool processInputType(WeatherConditionType &condition);
      bool processInputType(string type, WeatherConditionType &condition);
      void import(ifstream &fin);
      void import(string filename, WeatherConditionType condition);
    protected:
      vector<string> mainmenuoptions;
      vector<string> insertsubmenuoptions;
      vector<string> searchsubmenuoptions;
      WeatherStore store;
    private:
      static WeatherMan* weatherMan;
      WeatherMan();
      WeatherMan(const WeatherMan&);
      WeatherMan& operator=(const WeatherMan&);
  };

#endif