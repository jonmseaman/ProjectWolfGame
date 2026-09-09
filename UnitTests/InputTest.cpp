#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <UI/Input.h>

namespace UnitTests {

/**
 * Feeds a fixed string to the input functions and swallows their prompts, so
 * that a test can drive them without a terminal.
 */
class InputTest : public ::testing::Test {
protected:
    void feed(const std::string &text) {
        input.str(text);
        input.clear();
        std::cin.clear();
        originalIn = std::cin.rdbuf(input.rdbuf());
        originalOut = std::cout.rdbuf(sink.rdbuf());
    }
    void TearDown() override {
        if (originalIn) { std::cin.rdbuf(originalIn); }
        if (originalOut) { std::cout.rdbuf(originalOut); }
        std::cin.clear();
    }
    std::string printed() const { return sink.str(); }

private:
    std::istringstream input;
    std::ostringstream sink;
    std::streambuf* originalIn = nullptr;
    std::streambuf* originalOut = nullptr;
};

// --- getInteger(min, max) ---

TEST_F(InputTest, getIntegerInRangeReturnsTheValue) {
    feed("5\n");
    EXPECT_EQ(5, getInteger(1, 10));
}

TEST_F(InputTest, getIntegerRejectsOutOfRangeAndKeepsAsking) {
    feed("99\n-4\n7\n");
    EXPECT_EQ(7, getInteger(1, 10));
}

TEST_F(InputTest, getIntegerNeverReturnsAValueOutsideTheRange) {
    // This is the regression. getInteger(min, max) used to read twice per
    // pass and return the second value unchecked, so this returned 99.
    feed("9\n5\n99\n2\n");
    int value = getInteger(1, 3);
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 3);
    EXPECT_EQ(2, value);
}

TEST_F(InputTest, getIntegerRecoversFromNonNumericInput) {
    feed("abc\n42\n");
    EXPECT_EQ(42, getInteger(1, 100));
}

TEST_F(InputTest, getIntegerDoesNotLoopForeverAtEndOfInput) {
    // Fed nothing acceptable and then nothing at all, this used to spin
    // forever printing prompts. It has to give up instead.
    feed("99\n");
    EXPECT_THROW(getInteger(1, 3), InputClosed);
}

TEST_F(InputTest, getIntegerWithNoInputAtAllThrows) {
    feed("");
    EXPECT_THROW(getInteger(), InputClosed);
}

TEST_F(InputTest, getIntegerRejectsInvertedBounds) {
    feed("1\n");
    EXPECT_THROW(getInteger(10, 1), std::invalid_argument);
}

// --- getDigit ---

TEST_F(InputTest, getDigitReturnsADigitInRange) {
    feed("4");
    EXPECT_EQ(4, getDigit(1, 9));
}

TEST_F(InputTest, getDigitSkipsDigitsOutsideTheRange) {
    feed("098x3");
    EXPECT_EQ(3, getDigit(1, 3));
}

TEST_F(InputTest, getDigitThrowsAtEndOfInput) {
    feed("99999");
    EXPECT_THROW(getDigit(1, 3), InputClosed);
}

TEST_F(InputTest, getDigitRejectsBoundsOutsideZeroToNine) {
    feed("5");
    EXPECT_THROW(getDigit(-1, 9), std::invalid_argument);
    EXPECT_THROW(getDigit(0, 10), std::invalid_argument);
    EXPECT_THROW(getDigit(5, 2), std::invalid_argument);
}

// --- getInput ---

TEST_F(InputTest, getInputAcceptsOnlyListedCharacters) {
    feed("xyzq");
    EXPECT_EQ('q', getInput("wasdq"));
}

TEST_F(InputTest, getInputWithNoFilterAcceptsAnything) {
    feed("~");
    EXPECT_EQ('~', getInput());
}

TEST_F(InputTest, getInputThrowsAtEndOfInput) {
    feed("xyz");
    EXPECT_THROW(getInput("wasd"), InputClosed);
}

// --- dispList ---

TEST_F(InputTest, dispListNumbersFromOne) {
    feed("");
    dispList("Header", { "first", "second" });
    const std::string out = printed();
    EXPECT_NE(std::string::npos, out.find("Header"));
    EXPECT_NE(std::string::npos, out.find("1: first"));
    EXPECT_NE(std::string::npos, out.find("2: second"));
}

} // namespace UnitTests
