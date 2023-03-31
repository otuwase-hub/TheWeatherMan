#include "WeatherStore.h"

Entry::Entry(WeatherCondition *data)
{
  this->data = data;
  next = NULL;
  prev = NULL;
}

WeatherStore::WeatherStore()
{
  first = NULL;
  last = NULL;
  count = 0;
  sort = true;
}

WeatherStore::WeatherStore(bool sort)
{
  first = NULL;
  last = NULL;
  count = 0;
  this->sort = sort;
}

void WeatherStore::setSortMode(bool sort)
{
  this->sort = sort;
}

bool WeatherStore::getSortMode()
{
  return sort;
}

void WeatherStore::fread(ifstream &in, WeatherConditionType condition)
{
  string date, location;
  int low, high, countImport = 0;
  bool found = false;
  vector<int> invalidLines;
  switch(condition)
  {
    case all:
     break;
    case precipitation:
    {
      string type;
      float amount;
      int i = 1;
      while(in >> date >> location >> low >> high >> type >> amount)
      {
        found = true;
        Precipitation *data = new Precipitation(Date(date), Location(location), 
        Temperature(low, high));
        toLower(type);
        if(type == "rain")
        {
          data->setType(new Rain(amount));
        }
        else if(type == "snow")
        {
          data->setType(new Snow(amount));
        }
        else if(type == "freezing")
        {
          data->setType(new FreezingRain(amount));
        }
        else if(type == "hail")
        {
          data->setType(new Hail(amount));
        }
        else if(type == "fog")
        {
          data->setType(new Fog());
        }
        else
        {
          found = false;
          invalidLines.push_back(i); // insert invalid 
        }
        if(found)
        {
          if(sort)
          {
            insertSort(data);
          }
          else
          {
            append(data);
          }
          countImport++;
        }
        i++;
      }
      if(invalidLines.size() > 0)
      {
        cout << endl;
        cout << "ALERT::invalid precipitation type found at line(s): ";
        for(int i = 0; i < invalidLines.size(); i++)
        {
          cout << invalidLines[i];
          if(i != invalidLines.size() - 1)
          {
            cout << ", ";
          }
        }
        cout << endl;
      }
      break;
    }
    case wind:
    {
      float speed;
      string direction;
      while(in >> date >> location >> low >> high >> speed >> direction)
      {
        Wind *data = new Wind(Date(date), Location(location), Temperature(low, high), speed, direction);
        if(sort)
        {
          insertSort(data);
        }
        else
        {
          append(data);
        }
        countImport++;
      }
      break;
    }

    case sea:
    {
      float height, period, temperature;
      int i = 1, j = 0;
      while(in >> date >> location >> low >> high >> height >> period >> temperature)
      {
        Location l = Location(location);
        if(l.seaState())
        {
          SeaState *data = new SeaState(Date(date), l, 
        Temperature(low, high), height, period, temperature);
          if(sort)
          {
            insertSort(data);
          }
          else
          {
            append(data);
          }
          countImport++;
        }
        else
        {
          invalidLines[j++] = i;
        }
        i++;
      }
      if(invalidLines.size() > 0)
      {
        cout << "Invalid location data found at line(s) of input file: ";
        for(int i = 0; i < invalidLines.size(); i++)
        {
          cout << invalidLines[i];
          if(i != invalidLines.size() - 1)
          {
            cout << ", ";
          }
        }
        cout << endl;
      }
      break;
    }
  }
  cout << endl;
  cout << "Lines imported: " << countImport << endl;
  cout << "Failures: " << invalidLines.size() << endl;
  cout << "Total entries: " << count << endl;
}

void WeatherStore::read(istream &in, WeatherCondition *data)
{
  bool valid = data->read(in);
  if(valid)
  {
    int entryId;
    if(sort)
    {
      entryId = insertSort(data);
    }
    else
    {
      entryId = append(data);
    }
    cout << endl;
    cout << "Entry ID: " << entryId << endl;
    cout << "Total entries: " << count << endl;
    return;
  }
}

int WeatherStore::append(WeatherCondition *data)
{
  if(empty(false))
  {
    last = new Entry(data);
    last->prev = first;
    first = last;
  }
  else
  {
    Entry *entry = new Entry(data);
    entry->prev = last;
    last->next = entry;
    last = entry;
  }
  return ++count;
}

int WeatherStore::insertSort(WeatherCondition *data)
{
  int id = 1;
  if(empty(false))
  {
    first = new Entry(data);
    first->next = last;
    last = first;
  }
  else
  {
    Entry *entry = new Entry(data);
    if(Date::isEarlierThan(first->data->getDate(), data->getDate()))
    {
      entry->next = first;
      first->prev = entry;
      first = entry;
    }
    else if(Date::isEarlierThan(data->getDate(), last->data->getDate()))
    {
      last->next = entry;
      entry->prev = last;
      last = entry;
      id = count + 1;
    }
    else
    {
      id = 2;
      Entry *current = first;
      Entry *temp = first->next;
      while(temp != NULL && Date::isEarlierThan(data->getDate(), temp->data->getDate()))
      {
        id++;
        current = current->next;
        temp = temp->next;
      }
      temp->prev = entry;
      entry->next = temp;
      entry->prev = current;
      current->next = entry;
    }
  }
  count++;
  return id;
}

void WeatherStore::deleteEntry(int entryId)
{
  if(entryId == 1 && count == 1)
  {
    first = last = NULL;
  }
  else if(entryId == 1)
  {
    first = first->next;
    first->prev = NULL;
  }
  else if(entryId == count)
  {
    last = last->prev;
    last->next = NULL;
  }
  else
  {
    if((entryId - 1) <= (count - entryId)) // iterate from the front
    {
      Entry *prev = first;
      Entry *curr = first->next;
      for(int i = 2; i < entryId; i++, prev = curr, curr = curr->next);
      prev->next = curr->next;
      curr->next->prev = prev;
    }
    else // iterate from the back
    {
      Entry *next = last;
      Entry *curr = last->prev;
      for(int i = count - 1; i > entryId; i--, next = curr, curr = curr->prev);
      next->prev = curr->prev;
      curr->prev->next = next;
    }
  }
  count--;
  cout << "Deleted entry: " << entryId << endl;
  cout << "Total entries: " << count << endl;
}

bool WeatherStore::empty(bool verbose) const
{
  if(verbose && first == NULL)
  {
    cout << "NO DATA AVAILABLE" << endl;
    return true;
  }
  return (first == NULL);
}

void WeatherStore::write(ostream &out) const
{
  Entry *temp = first;
  int i = 1;
  while(temp != NULL)
  {
    out << i++ << ". ";
    temp->data->write(out);
    out << endl;
    temp = temp->next;
  }
}

void WeatherStore::searchByDate(ostream &out, istream &in, Date date)
{
  out << endl;
  date.read(in);
  out << endl;
  Entry *temp = first;
  int i = 0;
  while(temp != NULL)
  {
    if(Date::equals(temp->data->getDate(), date))
    {
      out << ++i << ". ";
      temp->data->write(out);
      out << endl;
    }
    temp = temp->next;
  }
  if(i == 0)
  {
    out << "NO SEARCH RESULT" << endl;
  }
}

void WeatherStore::searchByLocation(ostream &out, istream &in, Location location, string searchKey)
{
  out << endl;
  location.read(in, searchKey);
  out << endl;
  Entry *temp = first;
  int i = 0;
  if(searchKey == "city")
  {
    while(temp != NULL)
    {
      if(Location::cityMatch(temp->data->getLocation(), location))
      {
        out << ++i << ". ";
        temp->data->write(out);
        out << endl;
      }
      temp = temp->next;
    }
  }
  else if(searchKey == "province")
  {
    while(temp != NULL)
    {
      if(Location::provinceMatch(temp->data->getLocation(), location))
      {
        out << ++i << ". ";
        temp->data->write(out);
        out << endl;
      }
      temp = temp->next;
    }
  }
  else if(searchKey == "location")
  {
    while(temp != NULL)
    {
      if(Location::equals(temp->data->getLocation(), location))
      {
        out << ++i << ". ";
        temp->data->write(out);
        out << endl;
      }
      temp = temp->next;
    }
  }
  if(i == 0)
  {
    out << "NO SEARCH RESULT" << endl;
  }
}

int WeatherStore::size() const
{
  return count;
}
