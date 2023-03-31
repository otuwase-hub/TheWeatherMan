#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits> // This header defines elements with the characteristics of arithmetic types. More specifically, it defines a numeric_limits class template and a specialization of it for each of the fundamental types

using namespace std;

namespace utils
{
  static void toLower(string &input)
  {
    for(int i = 0; i < input.size(); i++)
    {
      input[i] = tolower(input[i]);
    }
  }

  static string toUpper(string input)
  {
    string output;
    for(int i = 0; i < input.size(); i++)
    {
      output += toupper(input[i]);
    }
    return output;
  }

  static void proofRead(ostream &out, istream &in, int &input)
  {
    in >> input;
    if(in.fail())
    {
      input = -1;
      in.clear(); // clear error
      in.ignore(numeric_limits<streamsize>::max(), '\n'); // eats up the remaining characters if any left in the input stream
      out << "error::invalid input type" << endl;
    }
  }

  static void proofRead(ostream &out, istream &in, int &input, int lowerbound, int upperbound)
  {
    in >> input;
    if(in.fail())
    {
      input = -1;
      in.clear(); // clear error
      in.ignore(numeric_limits<streamsize>::max(), '\n'); // eats up the remaining characters if any left in the input stream
      out << "error::invalid input type" << endl;
    }
    if(input <= lowerbound || input >= upperbound)
    {
      input = -1;
      out << "warning::invalid choice" << endl;
    }
  }
}

#endif