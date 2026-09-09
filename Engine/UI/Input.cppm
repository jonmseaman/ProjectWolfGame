module;
#include "EngineMacros.h"

export module Engine:Input;

import std;

export {

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
 */
ENGINE_API void dispList(const std::string &headText, const std::vector<std::string> &listItems);
/**
 * Displays a numbered list without a header.
 */
ENGINE_API void dispList(const std::vector<std::string> &listItems);
/**
 * Allows user input of a single digit without requiring the user to press
 * enter. Input outside the range is ignored.
 * @throws std::invalid_argument unless 0 <= min <= max <= 9
 * @throws InputClosed if input ends before a digit in range is entered.
 */
ENGINE_API int getDigit(int min = 0, int max = 9);
/**
 * Gets input from the player. Takes char input.
 * @param validInput The allowed chars; empty accepts anything.
 * @throws InputClosed if input ends before an accepted character is entered.
 */
ENGINE_API char getInput(const std::string &validInput = "");
/**
 * Gets an integer from the user, re-prompting until one is entered.
 * @throws InputClosed if input ends first.
 */
ENGINE_API int getInteger();
/**
 * Gets an integer from the user in [min, max], re-prompting until one is
 * entered. The returned value is always within the range.
 * @throws std::invalid_argument if min > max
 * @throws InputClosed if input ends first.
 */
ENGINE_API int getInteger(int min, int max);

/** The column padding for lists. */
inline constexpr int COLUMN_PADDING{ 3 };

}
