#include <gtest/gtest.h>
#include <string>
#include <Savable.h>
#include <Entity/Stats.h>

using namespace Engine::Entity;

namespace UnitTests {

TEST(SavableTest, testGetAndSetId) {
    auto s = Stats{ 1,2,3 };
    s.setID("Stats");

    EXPECT_TRUE("Stats" == s.getID());
}

TEST(SavableTest, testNextId) {
}

TEST(SavableTest, saveAndLoadStringString) {
    Stats s;

    std::string varName = "StringSave";
    std::string varValue = "StringValue";
    std::string varValueOriginal = varValue;
    s.Savable::save(varName, varValue);

    std::string fname = "saveAndLoadStringString";
    File::save(fname);
    File::load(fname);

    // Just in case a value isn't actually loaded
    varValue = "";
    s.Savable::load(varName, varValue);

    EXPECT_EQ(varValueOriginal, varValue);
}

TEST(SavableTest, save_string_int) {
    Stats s;

    std::string varName = "StringSave";
    int varValue = 125;
    int varValueOriginal = varValue;
    s.Savable::save(varName, varValue);
    std::string fname = "SavableTest_string_int";
    File::save(fname);
    File::load(fname);

    // Just in case a value isn't actually loaded
    varValue = 0;
    s.Savable::load(varName, varValue);

    EXPECT_EQ(varValueOriginal, varValue);
}

/**
* Makes sure loading and saving is working for many consecutive
* saves and loads
*/
TEST(SavableTest, stats_load_multipleSavables) {
    const int numSavs = 15;
    Stats s[numSavs];
    Stats loadedStats[numSavs];
    Stats sOriginal[numSavs];
    // Init arrays
    for (int i = 0; i < numSavs; i++) {
        s[i] = Stats{ i + 1, i + 2, i + 3 };
        sOriginal[i] = s[i];
    }

    // Make sure nothing is left over from previous loading / saving
    File::clear();

    // Save
    for (auto i = 0; i < numSavs; i++) {
        s[i].save();
    }

    std::string fName = "stats_load_test";
    File::save(fName);
    File::load(fName);

    // Load
    for (auto i = 0; i < numSavs; i++) {
        loadedStats[i].load();
    }

    // Make sure loaded stats are correct
    for (auto i = 0; i < numSavs; i++) {
        EXPECT_TRUE(sOriginal[i] == loadedStats[i]);
        EXPECT_TRUE(sOriginal[i] == s[i]);
    }
}

TEST(SavableTest, canLoadTest) {
    std::string className = "Stats";
    Stats s{ 1,2,3 };
    s.save();

    // Get ready for loading.
    File::save("canLoadTest");
    File::load("canLoadTest");

    EXPECT_TRUE(s.canLoad(className));

    // canLoad should now return false
    s.load();

    EXPECT_FALSE(s.canLoad(className));
}

} // namespace UnitTests
