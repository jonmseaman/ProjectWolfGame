#ifndef ENGINE_UI_INPUT_H
#define ENGINE_UI_INPUT_H
#include <Engine.h>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * Thrown when there is no more input to read, because standard input reached
 * end of file. None of the functions below can return a meaningful value in
 * that case, and waiting for input that will never arrive spins forever, so
 * they report it instead. main() treats it as a request to quit.
 */
class ENGINE_API InputClosed : public std::runtime_error {
public:
  explicit InputClosed(const std::string &what) : std::runtime_error(what) {}
};

/**
 * Displays a numbered list with a header. Starts numbering at 1.
 * @param headText The string that will be the list's header.
 * @param listItems The strings that will make up the list.
 */
ENGINE_API void dispList(const std::string &headText, const std::vector<std::string> &listItems);
/**
 * Displays a numbered list without a header.
 * @param listItems The strings that will make up the list.
 */
ENGINE_API void dispList(const std::vector<std::string> &listItems);
/**
 * Allows user input of a single digit without requiring the user
 * to press enter. Input outside the range is ignored.
 * @return int in [min, max]
 * @throws std::invalid_argument unless 0 <= min <= max <= 9
 * @throws InputClosed if input ends before a digit in range is entered.
 */
ENGINE_API int getDigit(int min = 0, int max = 9);
/**
 * Gets input from the player. Takes char input.
 * @param validInput A string containing the allowed chars. An empty string
 * accepts any character.
 * @return a char in validInput
 * @throws InputClosed if input ends before an accepted character is entered.
 */
ENGINE_API char getInput(const std::string &validInput = ""); // Unbuffered input to take an action
/**
 * Gets an integer from the user, re-prompting until one is entered.
 * @throws InputClosed if input ends first.
 */
ENGINE_API int getInteger();
/**
 * Gets an integer from the user in [min, max], re-prompting until one is
 * entered. The returned value is always within the range.
 * @param min the lower bound
 * @param max the upper bound
 * @throws std::invalid_argument if min > max
 * @throws InputClosed if input ends first.
 */
ENGINE_API int getInteger(int min, int max);
/**
 * The column padding for lists.
 */
const int COLUMN_PADDING{ 3 };

#endif // ENGINE_UI_INPUT_H
