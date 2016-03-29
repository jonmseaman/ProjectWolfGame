#include "CppUnitTest.h"
#include <Entity/Item.h>
#include <Creation/Createable.h>
#include <Creation/Create.h>

using namespace Engine::Entity;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Class to test registration for;
class TestableItem : public Engine::Entity::Item {
public:
  CREATABLE_ITEM(TestableItem)
};

CREATEABLE_REGISTRATION(TestableItem);



TEST_CLASS(RegistrationTest) {
public:
  TEST_METHOD(testItemRegistration) {
    Item* t = Creation::Create::newItem("TestableItem");
    Assert::IsTrue(t != nullptr);
  }
};
