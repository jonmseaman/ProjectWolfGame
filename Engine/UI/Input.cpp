module;

#ifdef _WIN32
#  include <conio.h>
#else
#  include <termios.h>
#  include <unistd.h>
#endif

module Engine;

import std;

/**
 * Miscellaneous functions
 */

namespace {

// EOF is a macro from <cstdio>, and macros do not come from `import std`.
constexpr int kEndOfFile = std::char_traits<char>::eof();

#ifndef _WIN32
/**
 * Puts the terminal into unbuffered, non-echoing mode for as long as it is
 * alive, and restores the previous settings on the way out -- including when
 * the read below throws. Does nothing when input is not a terminal, which is
 * the case for piped input and for the tests.
 */
class RawMode {
public:
  RawMode() {
    if (!isatty(STDIN_FILENO)) { return; }
    if (tcgetattr(STDIN_FILENO, &original) != 0) { return; }
    restore = true;
    termios raw = original;
    raw.c_lflag &= ~(static_cast<tcflag_t>(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
  }
  ~RawMode() {
    if (restore) { tcsetattr(STDIN_FILENO, TCSANOW, &original); }
  }
  RawMode(const RawMode&) = delete;
  RawMode& operator=(const RawMode&) = delete;

private:
  termios original{};
  bool restore = false;
};
#endif

/**
 * Reads a single character.
 *
 * Everything outside Windows reads through std::cin so that the character
 * functions and getInteger() draw from one stream rather than mixing C stdio
 * with iostreams, and so that redirected input works.
 *
 * @throws InputClosed when there is nothing left to read.
 */
int readChar() {
#ifdef _WIN32
  int ch = _getch();
#else
  RawMode rawMode;
  int ch = std::cin.get();
#endif
  if (ch == kEndOfFile) {
    throw InputClosed("input: no more input to read");
  }
  return ch;
}

} // namespace

void dispList(const std::vector<std::string> &listItems) {
  for (std::size_t i = 0; i < listItems.size(); i++) {
    std::cout << std::setw(COLUMN_PADDING) << std::right << i + 1 << ": "
              << listItems.at(i) << std::endl;
  }
}

void dispList(const std::string &headText, const std::vector<std::string> &listItems) {
  std::cout << headText << std::endl;
  dispList(listItems);
}

int getDigit(int min, int max) {
  // This was an assert, which does nothing in a release build.
  if (min < 0 || max > 9 || min > max) {
    throw std::invalid_argument("getDigit: requires 0 <= min <= max <= 9");
  }
  while (true) {
    int input = readChar();
    if (input >= '0' && input <= '9') {
      int digit = input - '0';
      if (digit >= min && digit <= max) {
        return digit;
      }
    }
  }
}

char getInput(const std::string &validInput) {
  while (true) {
    int input = readChar();
    // An empty validInput accepts anything.
    if (validInput.empty() ||
        validInput.find(static_cast<char>(input)) != std::string::npos) {
      return static_cast<char>(input);
    }
  }
}

int getInteger() {
  int input = 0;
  while (true) {
    std::cout << " >> ";
    if (std::cin >> input) {
      return input;
    }
    if (std::cin.eof()) {
      throw InputClosed("input: no more input to read");
    }
    // Not a number. Clear the error and drop the rest of the line, otherwise
    // the offending characters are read again on every pass.
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int getInteger(int minVal, int maxVal) {
  if (minVal > maxVal) {
    throw std::invalid_argument("getInteger: min must not be greater than max");
  }
  while (true) {
    // Previously this read twice per pass and returned the second value
    // without checking it, so it could return a number outside the range.
    int input = getInteger();
    if (input >= minVal && input <= maxVal) {
      return input;
    }
    std::cout << "Enter a number between " << minVal << " and " << maxVal
              << "." << std::endl;
  }
}
