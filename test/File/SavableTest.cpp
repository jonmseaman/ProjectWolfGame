#include <boost/test/unit_test.hpp>
#include <string>
#include "Stats.h"

using std::string;

/**
 * This document is for testing the Savable class.
 */
BOOST_AUTO_TEST_SUITE(SavableTest)

BOOST_AUTO_TEST_CASE(save_void) {
  Stats s;
  s.save();
}

BOOST_AUTO_TEST_CASE(save_string_string) {
  Stats s;
  s.Savable::save("StringSave", "StringSave");
}

BOOST_AUTO_TEST_CASE(save_string_int) {
  Stats s;
  s.Savable::save("Int_15", 15);
}

BOOST_AUTO_TEST_CASE(file_save) {
  File::save("Test/SavableTest");
}

// We have to laod from a file to test the load functions
BOOST_AUTO_TEST_CASE(file_load) {
  File::load("Test/SavableTest");
}

BOOST_AUTO_TEST_CASE(load_string_string) {
  std::string stringVar = "";
  Stats s;
  s.Savable::load("StringSave", stringVar);

  BOOST_CHECK(stringVar == "StringSave");
}

BOOST_AUTO_TEST_CASE(load_string_int) {
  Stats s;
  int intVar = 0;
  s.Savable::load("Int_15", intVar);

  BOOST_CHECK(intVar == 15);
}


BOOST_AUTO_TEST_SUITE_END()
