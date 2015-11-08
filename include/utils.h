#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"
void dispList(const std::string headText, const std::vector<std::string> &listItems);
void dispList(const std::vector<std::string> &listItems);
int getInteger();
int getInteger(int min, int max);
const int COLUMN_PADDING{3};

template <typename T> std::string to_string( const T& n )
{
  std::ostringstream stm ;
  stm << n ;
  return stm.str();
}
#endif // UTILS_H
