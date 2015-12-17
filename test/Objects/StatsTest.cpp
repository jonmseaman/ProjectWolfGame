#include "Test.h"
#include "Stats.h"


/**
 * This file is for testing the stats class as well as the savable class.
 * The savable tests are performed here since Savable is partially abstract.
 */
BOOST_AUTO_TEST_SUITE(StatsTest)


BOOST_AUTO_TEST_CASE(Constructor) {

  Stats s = Stats{ 1,2,3 };
  Check(s.getStamina() == 1);
  Check(s.getStrength() == 2);
  Check(s.getIntellect() == 3);

  s = Stats();
  Check(s.getStamina() == 0);
  Check(s.getStrength() == 0);
  Check(s.getIntellect() == 0);
}

Test(showStatsTest) {
  Stats s{ 1,2,3 };
  s.showStats();
}

Test(additionOperator) {
  Stats s = Stats{ 1,2,3 } +Stats{ 2,2,2 };
  Check(s.getStamina() == 1 + 2);
  Check(s.getStrength() == 2 + 2);
  Check(s.getIntellect() == 3 + 2);
}

Stats s{ 1,2,3 };

Test(save) {
  Stats sOriginal = s;
  for (int i = 0; i < 10; i++) {
    s.save();
  }
  
  BOOST_CHECK(s == sOriginal);
}

Test(File_Save) {
  File::save("StatsTest1");
}

Test(File_Save_AfterHavingSavedAlready) {
  File::save("StatsTest2");
}

BOOST_AUTO_TEST_SUITE_END()
