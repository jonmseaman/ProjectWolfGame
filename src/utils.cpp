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

void dispList(const std::vector<std::string> &listItems) {
  for (int i(0); i<listItems.size(); i++) {
    std::cout << std::setw(COLUMN_PADDING) << std::right << i+1 << ": " << listItems.at(i) << std::endl;
  }
}

void dispList(const std::string headText, const std::vector<std::string> &listItems) {
  std::cout << headText << std::endl;
  dispList(listItems);
}

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

char getInput(const std::string &validInput) {
  int input = _getch();
  // Make sure we get valid input. If valid input is empty, all input valid.
  while (validInput.find(char(input)) == -1 && validInput != "") {
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
