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
    Map* loadedM = new Map();
    m->save();

    loadedM->load();
    Assert::AreEqual(m->getID(), loadedM->getID(), L"Ids are not the same.");
    Assert::AreEqual(m->getMapSize(), m->getMapSize(), L"Maps are not the same size.");

    delete loadedM;
    delete m;
  }
};

}
