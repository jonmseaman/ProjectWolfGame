#include <gtest/gtest.h>
#include <Map/Map.h>
#include <Map/Node.h>
#include <Entity/Actor.h>
#include <Creation/Create.h>

using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

namespace UnitTests {

TEST(MapTest, mapDefaultConstructor) {
    Map m{};
    int mSize = m.getMapSize();
    EXPECT_EQ(m.grid.size(), (size_t)(mSize * mSize));
    EXPECT_TRUE(m.grid.size() > 0);
}

TEST(MapTest, mapSaveDefaultMap) {
    auto m = Create::newMap("TestableMap");
    m->save();
    File::save("MapTest_mapSaveDefaultMap");
}

TEST(MapTest, mapSaveTestableMap) {
    auto m = Create::newMap("TestableMap");
    m->save();
    File::save("MapTest_mapSaveTestableMap");
}

TEST(MapTest, mapLoad) {
    auto m = Create::newMap("TestableMap");
    m->save();
    File::save("mapLoadTest");
    File::load("mapLoadTest");

    auto loadedM = Create::loadNewMap();
    EXPECT_EQ(m->getMapSize(), m->getMapSize());
}

} // namespace UnitTests
