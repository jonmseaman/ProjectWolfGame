#ifndef UTILS_H
#define UTILS_H
#include <Engine.h>
#include <string>
#include <vector>
#include <sstream>

ENGINE_API void dispList(const std::string headText, const std::vector<std::string> &listItems);

ENGINE_API void dispList(const std::vector<std::string> &listItems);

ENGINE_API int getDigit(int min = 0, int max = 9);
/**
 * Gets input from the player. Takes char input
 * @param validInput A string containing the allowed chars
 * @return a char in validInput
 */
ENGINE_API char getInput(const std::string &validInput = ""); // Unbuffered input to take an action

ENGINE_API int getInteger();

ENGINE_API int getInteger(int min, int max);
/**
 * The column padding for lists.
 */
const int COLUMN_PADDING{ 3 };

#endif
