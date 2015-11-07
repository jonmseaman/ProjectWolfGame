#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

/**
 * Prints headText followed by a list starting at one 
 * each list item is a string from textList
 */
void dispList(std::string headText, std::vector<std::string> listItems)
{
  std::cout << headText << std::endl;
  for (int i(0); i<listItems.size(); i++)
  {
    std::cout << std::setw(3) << std::right << i+1 << ": " << listItems.at(i) << std::endl;
  }
}

/**
 * Prints a numbered list starting at one.
 * each list item is a string from textList
 */
void dispList(std::vector<std::string> listItems)
{
  for (int i(0); i<listItems.size(); i++)
  {
    std::cout << std::setw(3) << std::right << i+1 << ": " << listItems.at(i) << std::endl;
  }
}

int getInteger()
{
  int input;
  std::cout <<  " >> ";
  std::cin >> input;
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(36,'\n');
    return -1;
  }
  return input;
}

int getInteger(int minVal, int maxVal)
{
  int input;
  std::cout << " >> ";
  std::cin >> input;
  while ( (input < minVal) || (input > maxVal) )
  {
    while ( std::cin.fail() )
    {
      std::cin.clear();
      std::cin.ignore(36,'\n');
    }
    std::cout << " >> ";
    std::cin >> input;
  }
  return input;
}
