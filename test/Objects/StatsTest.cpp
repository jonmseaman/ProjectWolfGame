#include <boost/test/unit_test.hpp>
#include "Stats.h"


/**
 * This file is for testing the stats class as well as the savable class.
 * The savable tests are performed here since Savable is partially abstract.
 */
BOOST_AUTO_TEST_SUITE(StatsTest)


BOOST_AUTO_TEST_CASE(Constructor) {

  Stats s = Stats{ 1,2,3 };
  BOOST_CHECK(s.getStamina() == 1);
  BOOST_CHECK(s.getStrength() == 2);
  BOOST_CHECK(s.getIntellect() == 3);

  s = Stats();
  BOOST_CHECK(s.getStamina() == 0);
  BOOST_CHECK(s.getStrength() == 0);
  BOOST_CHECK(s.getIntellect() == 0);
}

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
  File::save("StatsTest1");
}

BOOST_AUTO_TEST_CASE(File_Save_AfterHavingSavedAlready) {
  File::save("StatsTest2");
}

BOOST_AUTO_TEST_SUITE_END()
