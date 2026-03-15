#include <gtest/gtest.h>
#include <string>
#include <fstream>
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

// XML serialization robustness tests

TEST(SavableTest, roundtrip_string_with_spaces) {
    Stats s;
    std::string varName = "msg";
    std::string varValue = "hello world";
    s.Savable::save(varName, varValue);
    File::save("rt_spaces");
    File::load("rt_spaces");
    varValue = "";
    s.Savable::load(varName, varValue);
    EXPECT_EQ("hello world", varValue);
}

TEST(SavableTest, roundtrip_empty_string) {
    Stats s;
    std::string varName = "empty";
    std::string varValue = "";
    s.Savable::save(varName, varValue);
    File::save("rt_empty_str");
    File::load("rt_empty_str");
    varValue = "non-empty";
    s.Savable::load(varName, varValue);
    EXPECT_EQ("", varValue);
}

TEST(SavableTest, roundtrip_large_integer) {
    Stats s;
    std::string varName = "bignum";
    int varValue = 2147483647; // INT_MAX
    s.Savable::save(varName, varValue);
    File::save("rt_large_int");
    File::load("rt_large_int");
    varValue = 0;
    s.Savable::load(varName, varValue);
    EXPECT_EQ(2147483647, varValue);
}

TEST(SavableTest, roundtrip_negative_integer) {
    Stats s;
    std::string varName = "negnum";
    int varValue = -42;
    s.Savable::save(varName, varValue);
    File::save("rt_neg_int");
    File::load("rt_neg_int");
    varValue = 0;
    s.Savable::load(varName, varValue);
    EXPECT_EQ(-42, varValue);
}

TEST(SavableTest, roundtrip_multiple_vars_in_one_savable) {
    Stats s;
    s.Savable::save("a", std::string("alpha"));
    s.Savable::save("b", 99);
    s.Savable::save("c", std::string("gamma"));
    File::save("rt_multi_vars");
    File::load("rt_multi_vars");
    std::string a, c;
    int b = 0;
    s.Savable::load("a", a);
    s.Savable::load("b", b);
    s.Savable::load("c", c);
    EXPECT_EQ("alpha", a);
    EXPECT_EQ(99, b);
    EXPECT_EQ("gamma", c);
}

TEST(SavableTest, xml_file_is_well_formed) {
    // Save a Stats object and verify the resulting file is non-empty
    // and contains expected XML markers.
    Stats s{ 7, 8, 9 };
    s.save();
    File::save("xml_well_formed");

    std::ifstream f("./Saves/xml_well_formed.xml");
    ASSERT_TRUE(f.is_open());
    std::string content((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());
    EXPECT_NE(std::string::npos, content.find("<?xml"));
    EXPECT_NE(std::string::npos, content.find("<Stats>"));
    EXPECT_NE(std::string::npos, content.find("</Stats>"));
    EXPECT_NE(std::string::npos, content.find("<stamina>7</stamina>"));
    EXPECT_NE(std::string::npos, content.find("<strength>8</strength>"));
    EXPECT_NE(std::string::npos, content.find("<intellect>9</intellect>"));
}

TEST(SavableTest, overwrite_then_load_gets_new_data) {
    // Save one set of data, then overwrite with another and load.
    Stats first{ 1, 2, 3 };
    first.save();
    File::save("overwrite_test");

    Stats second{ 10, 20, 30 };
    second.save();
    File::save("overwrite_test");  // overwrite

    File::load("overwrite_test");

    Stats loaded;
    loaded.load();

    EXPECT_EQ(10, loaded.getStamina());
    EXPECT_EQ(20, loaded.getStrength());
    EXPECT_EQ(30, loaded.getIntellect());
}

TEST(SavableTest, deeply_nested_savables) {
    // Save many Stats in sequence and load them all back.
    const int N = 30;
    Stats originals[N];
    for (int i = 0; i < N; i++) {
        originals[i] = Stats{ i * 3, i * 3 + 1, i * 3 + 2 };
        originals[i].save();
    }
    File::save("deeply_nested");
    File::load("deeply_nested");

    for (int i = 0; i < N; i++) {
        Stats loaded;
        loaded.load();
        EXPECT_EQ(originals[i].getStamina(),   loaded.getStamina());
        EXPECT_EQ(originals[i].getStrength(),  loaded.getStrength());
        EXPECT_EQ(originals[i].getIntellect(), loaded.getIntellect());
    }
}

} // namespace UnitTests
