
void utils::processChoice(int choice)
{
  system("cls");
  cout << "Choice: " << menu[choice-1];
  switch(choice)
  {
    case 0:
      {
        string filename;
        WeatherConditions condition;
        if(processInputType(condition))
        {
          cout << "Please enter filename: ";
          cin >> filename;
        }
        break;
      }
  }
}

bool utils::processInputType(WeatherConditions &condition)
{
  string type;
  WeatherCondition data;
  cout << "Please enter report type: ";
  cin >> type;
  tolower(type);
  if(type ==)
}

void utils::import(ifstream &fin)
{
  
}

void utils::import(string filename, WeatherConditions condition)
{
  ifstream fin(filename);
  store.fread(fin, condition);
}