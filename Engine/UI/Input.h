#ifndef UTILS_H
#define UTILS_H
#include <Engine.h>
#include <string>
#include <vector>
#include <sstream>
/**
 * Displays a numberd list with a header. Stats numbering at 1.
 * @param headText The string that will be the list's header.
 * @param listItems The strings that will make up the list.
 */
ENGINE_API void dispList(const std::string headText, const std::vector<std::string> &listItems);
/**
 * Displays a numbered list without a header.
 * @param listItems The strings that will make up the list.
 */
ENGINE_API void dispList(const std::vector<std::string> &listItems);
/**
 * Allows user input of a single digit without requiring the user
 * to press enter.
 * @return int in [min, max]
 * @pre min, max in [0, 9]
 */
ENGINE_API int getDigit(int min = 0, int max = 9);
/**
 * Gets input from the player. Takes char input
 * @param validInput A string containing the allowed chars
 * @return a char in validInput
 */
ENGINE_API char getInput(const std::string &validInput = ""); // Unbuffered input to take an action
/**
 * Gets an integer from the user.
 */
ENGINE_API int getInteger();
/**
 * Gets an integer from the user that is between with
 * getInteger in [min, max]
 * @param min the lower bound
 * @param max the upper bound
 * @return getInteger in [min, max]
 */
ENGINE_API int getInteger(int min, int max);
/**
 * The column padding for lists.
 */
const int COLUMN_PADDING{ 3 };

#endif
