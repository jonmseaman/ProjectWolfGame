#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

/**
 * Prints a numbered list starting at one.
 * each list item is a string from textList
 */
void dispList(const std::vector<std::string> &listItems)
{
  for (int i(0); i<listItems.size(); i++)
  {
    std::cout << std::setw(COLUMN_PADDING) << std::right << i+1 << ": " << listItems.at(i) << std::endl;
  }
}

/**
 * Prints headText followed by a list starting at one
 * each list item is a string from textList
 */
void dispList(const std::string headText, const std::vector<std::string> &listItems)
{
  std::cout << headText << std::endl;
  dispList(listItems);
}


int getInteger()
{
  int input;
  std::cout <<  " >> ";
  std::cin >> input;
  while (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(36,'\n');
    std::cout << " >> ";
    std::cin >> input;
  }
  return input;
}

int getInteger(int minVal, int maxVal)
{
  int input;
  std::cout << " >> ";
  std::cin >> input;
  while (input < minVal || input > maxVal) {
    input = getInteger();
    while (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(36,'\n');
    }
    std::cout << " >> ";
    std::cin >> input;
  }
  return input;
}
