#include "WeatherMan.h"

WeatherMan* WeatherMan::weatherMan = NULL;

WeatherMan::WeatherMan() : store()
{
  mainmenuoptions = 
    {
      "Import",
      "Insert weather report",
      "Search entry",
      "Delete entry",
      "Print state",
      "Display",
      "Export",
      "Clear screen",
      "Exit"
    };
  insertsubmenuoptions = 
    {
      "Precipitation",
      "Wind",
      "Sea State"
    };
  searchsubmenuoptions = 
    {
      "Date",
      "City",
      "Province",
      "Location"
    };
}

WeatherMan* WeatherMan::getWeatherMan()
{
  if(weatherMan == NULL)
  {
    weatherMan = new WeatherMan();
  }
  return (weatherMan);
}

void WeatherMan::initialize(ostream &out, istream &in)
{
  char choice;
  out << "Would you like the data to be sorted [default sorted]? (Y/N): "; 
  in >> choice;
  choice = tolower(choice);
  if(choice == 'n')
  {
    store.setSortMode(false);
  }
}

void WeatherMan::displayMenu(ostream &out, vector<string> &inmenu)
{
  out << endl;
  for(int i = 0; i < inmenu.size(); i++)
  {
    out << i+1 << ". " << inmenu[i] << endl;
  }
  out << endl;
  out << "Choice: ";
}

bool WeatherMan::processChoice(ostream &out, istream &in)
{
  displayMenu(out, mainmenuoptions); // print out menu
  int choice;
  proofRead(out, in, choice, 0, 10);
  if(choice != -1)
  {
    out << endl;
    out << "-: " << toUpper(mainmenuoptions[choice-1]) << endl;
    out << endl;
    if(choice == 9)
    {
      return false;
    }
    
    switch(choice)
    {
      case 1: // Import
      {
        WeatherConditionType condition;
        if(processInputType(condition))
        {
          string filename;
          out << "Enter filepath (without extension): ";
          in >> filename;
          if(condition == all)
          {
            ifstream fin(filename+".txt");
            import(fin);
          }
          else
          {
            import(filename, condition);
          }
        }
        break;
      }
      case 2: // Insert
      {
        int type;
        out << "Choose report type:";
        displayMenu(out, insertsubmenuoptions);
        proofRead(out, in, type, 0, 4);
        if(type != -1)
        {
          switch(type)
          {
            case 1:
            {
              Precipitation *data = new Precipitation();
              store.read(in, data);
              break;
            }
            case 2:
            {
              Wind *data = new Wind();
              store.read(in, data);
              break;
            }
            case 3:
            {
              SeaState *data = new SeaState();
              store.read(in, data);
              break;
            }
          }
        }
        break;
      }
      case 3: // Search
      {
        if(!store.empty(true))
        {
          int searchKey;
          out << "Search by:";
          displayMenu(out, searchsubmenuoptions);
          proofRead(out, in, searchKey, 0, 5);
          if(searchKey != -1)
          {
            switch(searchKey)
            {
              case 1:
              {
                store.searchByDate(out, in, Date());
                break;
              }
              case 2:
              {
                store.searchByLocation(out, in, Location(), "city");
                break;
              }
              case 3:
              {
                store.searchByLocation(out, in, Location(), "province");
                break;
              }
              case 4:
              {
                store.searchByLocation(out, in, Location(), "location");
                break;
              }
            }
          }
        }
        break;
      }
      case 4: // Delete entry
      {
        if(!store.empty(true))
        {
          int entryId;
          out << "Enter entry number: ";
          proofRead(out, in, entryId, 0, store.size() + 1);
          if(entryId != -1)
          {
            store.deleteEntry(entryId);
          }
        }
        break;
      }
      case 5: // Print state
      {
        out << "Total Entries: " << store.size() << endl;
        out << boolalpha << "Sort Settings: " << store.getSortMode() << endl;
        break;
      }
      case 6: // Display
      {
        if(!store.empty(true))
        {
          out << endl;
          store.write(out);
          out << endl;
        }
        break;
      }
      case 7: // Export
      {
        if(!store.empty(true))
        {
          string filename;
          out << "Enter output filename (without extension): ";
          in >> filename;
          ofstream fout(filename + ".txt");
          store.write(fout);
        }
        break;
      }
      case 8: // Clear Screen
      {
        system("clear");
        break;
      }
    }
  }
  return true;
}

bool WeatherMan::processInputType(WeatherConditionType &condition)
{
  string type;
  cout << "Enter report type: ";
  cin >> type;
  toLower(type);
  if(type == "precipitation")
  {
    condition = precipitation;
    return true;
  }
  else if(type == "wind")
  {
    condition = wind;
    return true;
  }
  else if(type == "sea")
  {
    condition = sea;
    return true;
  }
  else if(type == "all")
  {
    condition = all;
    return true;
  }
  cout << "Invalid type \"" << type << "\". [precipitation, wind, sea, all]" << endl;
  return false;
}

bool WeatherMan::processInputType(string type, WeatherConditionType &condition)
{
  if(type == "precipitation")
  {
    condition = precipitation;
    return true;
  }
  else if(type == "wind")
  {
    condition = wind;
    return true;
  }
  else if(type == "sea")
  {
    condition = sea;
    return true;
  }
  return false;
}

void WeatherMan::import(string filename, WeatherConditionType condition)
{
  ifstream fin(filename+".txt");
  store.fread(fin, condition);
}

void WeatherMan::import(ifstream &fin)
{
  string filename, type;
  WeatherConditionType condition;
  while(fin >> filename >> type)
  {
    if(processInputType(type, condition))
    {
      import(filename, condition);
    }
  }
}



