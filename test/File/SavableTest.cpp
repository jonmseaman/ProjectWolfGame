#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include "Stats.h"

using std::string;
using std::cout;
using std::endl;

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

/**
 * Tests to make sure all variables are loaded from file correctly.
 */
BOOST_AUTO_TEST_CASE(stats_load_singleSavable) {
  Stats s(1,2,3);
  Stats loadedStats;
  Stats sOriginal = s;
  // Make sure nothing is left over from previous loading / saving
  File::close();

  s.save();
  File::save("stats_load_test");
  File::load("stats_load_test");

  // Load stats
  loadedStats.load();

  // Make sure loaded stats are correct
  BOOST_CHECK(loadedStats == sOriginal);
}

/**
 * Makes sure loading and saving is working for many consecutive
 * saves and loads
 */
BOOST_AUTO_TEST_CASE(stats_load_multipleSavables) {
  const int numSavs = 15;
  Stats s [numSavs];
  Stats loadedStats [numSavs];
  Stats sOriginal [numSavs];
  // Init arrays
  for (int i = 0; i < numSavs; i++) {
    s[i] = Stats{i + 1, i + 2, i + 3};
    sOriginal[i] = s[i];
  }

  // Make sure nothing is left over from previous loading / saving
  File::close();

  // Save
  for (auto i = 0; i < numSavs; i++) {
    s[i].save();
  }

  File::save("stats_load_test");
  File::load("stats_load_test");

  // Save
  for (auto i = 0; i < numSavs; i++) {
    loadedStats[i].load();
  }

  // Make sure loaded stats are correct
  for (auto i = 0; i < numSavs; i++) {
    BOOST_CHECK(loadedStats[i] == sOriginal[i]);
    BOOST_CHECK(s[i] == sOriginal[i]);
  }
}


BOOST_AUTO_TEST_SUITE_END()
