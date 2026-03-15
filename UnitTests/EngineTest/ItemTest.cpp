#include <gtest/gtest.h>
#include <string>
#include <Entity/Item.h>

using namespace Engine::Entity;

namespace UnitTests {

TEST(ItemTest, ConstructorTest) {
    std::string name = "Item";
    std::string desc = "Desc";
    Stats s = Stats{ 1,2,3 };

    Item i(name, desc, s);

    EXPECT_EQ(name, i.getName());
    EXPECT_EQ(desc, i.getDescription());
    EXPECT_TRUE(s == i.stats);
}

TEST(ItemTest, saveAndLoad) {
    Item i{ "It", "Desc", Stats{1,2,3} };
    i.save();

    std::string fName = "ItemTest_Save";
    File::save(fName);
    File::load(fName);

    Item otherI;
    otherI.load();

    EXPECT_TRUE(i == otherI);
}

} // namespace UnitTests
