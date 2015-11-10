#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <conio.h>
#include <assert.h>

/**
 * Miscellaneous functions
 */

/**
 * Prints a numbered list starting at one.
 * each list item is a string from textList
 */
void dispList(const std::vector<std::string> &listItems) {
  for (int i(0); i<listItems.size(); i++) {
    std::cout << std::setw(COLUMN_PADDING) << std::right << i+1 << ": " << listItems.at(i) << std::endl;
  }
}

/**
 * Prints headText followed by a list starting at one
 * each list item is a string from textList
 */
void dispList(const std::string headText, const std::vector<std::string> &listItems) {
  std::cout << headText << std::endl;
  dispList(listItems);
}

/**
 * @return int in [min, max]
 * @pre min, max in [0, 9]
 */
int getDigit(int min, int max) {
  assert (min >= 0 && max <= 9);
  std::string digits = "0123456789";
  int input = _getch();
  int pos = digits.find(char(input));
  while (pos < min || pos > max) {
    input = _getch();
    pos = digits.find(char(input));
  }
  return pos;
}

/**
 * Gets input from the player. Takes char input
 * @param validInput A string containing the allowed chars
 * @return a char in validInput
 */
char getInput(const std::string &validInput) {
  int input = _getch();
  while (validInput.find(char(input)) == -1) {
    input = _getch();
  }
  return char(input);
}

int getInteger() {
  int input;
  std::cout <<  " >> ";
  std::cin >> input;
  while (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(36,'\n');
    std::cout << " >> ";
    std::cin >> input;
  }
  return input;
}

int getInteger(int minVal, int maxVal) {
  int input;
  std::cout << " >> ";
  std::cin >> input;
  while (input < minVal || input > maxVal) {
    input = getInteger();
    while (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(36,'\n');
    }
    std::cout << " >> ";
    std::cin >> input;
  }
  return input;
}
