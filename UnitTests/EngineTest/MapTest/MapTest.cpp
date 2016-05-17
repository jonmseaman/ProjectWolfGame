#include <CppUnitTest.h>
#include <Map/Map.h>
#include <Map/Node.h>
#include <Entity/Actor.h>
#include <Creation/Create.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

namespace UnitTests {
TEST_CLASS(MapTest) {
  TEST_METHOD(mapDefaultConstructor) {
    Map m{};
    int mSize = m.getMapSize();
    Assert::IsTrue(m.grid.size() == mSize * mSize, (ToString(m.grid.size()) + L" == " + ToString(mSize * mSize)).c_str());
    Assert::IsTrue(m.grid.size() > 0);
  }

  TEST_METHOD(mapSaveDefaultMap) {
    Map* m = Create::newMap("TestableMap");
    m->save();
    File::save("MapTest_mapSaveDefaultMap");

    delete m;
  }

  TEST_METHOD(mapSaveTestableMap) {
    Map* m = Create::newMap("TestableMap");
    m->save();
    File::save("MapTest_mapSaveTestableMap");

    delete m;
  }

  TEST_METHOD(mapLoad) {
    Map* m = Create::newMap("TestableMap");
    m->save();
    File::save("mapLoadTest");
    File::load("mapLoadTest");

    Map* loadedM = Create::loadNewMap();
    Assert::AreEqual(m->getMapSize(), m->getMapSize(), L"Maps are not the same size.");

    delete loadedM;
    delete m;
  }
};
}