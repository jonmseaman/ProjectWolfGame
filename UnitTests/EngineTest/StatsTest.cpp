#include <gtest/gtest.h>
#include <Entity/Stats.h>

using namespace Engine::Entity;

namespace UnitTests {

TEST(StatsTest, Constructor) {
    Stats s = Stats{ 1,2,3 };
    EXPECT_EQ(1, s.getStamina());
    EXPECT_EQ(2, s.getStrength());
    EXPECT_EQ(3, s.getIntellect());

    s = Stats();
    EXPECT_EQ(0, s.getStamina());
    EXPECT_EQ(0, s.getStrength());
    EXPECT_EQ(0, s.getIntellect());
}

TEST(StatsTest, additionOperator) {
    Stats s = Stats{ 1,2,3 } + Stats{ 3,2,1 };
    EXPECT_EQ(4, s.getStamina());
    EXPECT_EQ(4, s.getStrength());
    EXPECT_EQ(4, s.getIntellect());
}

TEST(StatsTest, save) {
    Stats s{ 1,2,3 };
    for (int i = 0; i < 3; i++) {
        s.save();
    }

    File::save("StatsTest1");
    // Testing to see if save structure was cleared after save
    File::save("StatsTest_EmptyFile");
}

TEST(StatsTest, File_Load) {
    // The two files should be identical
    File::load("StatsTest1");
    File::save("StatsTest1_Copy");
}

} // namespace UnitTests
