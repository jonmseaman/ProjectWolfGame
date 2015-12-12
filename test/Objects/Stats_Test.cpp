#include <boost/test/unit_test.hpp>
#include "Stats.h"

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
  Stats s = Stats{ 1,2,3 } +Stats{ 2,2,2 };
  BOOST_CHECK(s.getStamina() == 1 + 2);
  BOOST_CHECK(s.getStrength() == 2 + 2);
  BOOST_CHECK(s.getIntellect() == 3 + 2);
}

BOOST_AUTO_TEST_SUITE_END()
