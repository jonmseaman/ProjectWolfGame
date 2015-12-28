#include <boost/test/unit_test.hpp>
#include "Stats.h"


/**
 * This file is for testing the stats class.
 */
BOOST_AUTO_TEST_SUITE(StatsTest)


BOOST_AUTO_TEST_CASE(showStatsTest) {
  Stats s{ 1,2,3 };
  s.showStats();
}

BOOST_AUTO_TEST_CASE(additionOperator) {
  Stats s = Stats{ 1,2,3 } + Stats{ 2,2,2 };
  BOOST_CHECK(s.getStamina() == 1 + 2);
  BOOST_CHECK(s.getStrength() == 2 + 2);
  BOOST_CHECK(s.getIntellect() == 3 + 2);
}

Stats s{ 1,2,3 };

BOOST_AUTO_TEST_CASE(save) {
  Stats sOriginal = s;
  for (int i = 0; i < 3; i++) {
    s.save();
  }

  BOOST_CHECK(s == sOriginal);
}

BOOST_AUTO_TEST_CASE(File_Save) {
  // This file can be inspected manually
  File::save("StatsTest1");
}

BOOST_AUTO_TEST_CASE(File_Save_AfterHavingSavedAlready) {
  // This file can be inspected for manually
  File::save("StatsTest2");
}

BOOST_AUTO_TEST_CASE(File_Load) {
  // The two files generated should have exactly the same content.
  File::load("StatsTest1");
  File::save("StatsTest1_AfterLoad");
}

BOOST_AUTO_TEST_SUITE_END()
