#include <string>
#include "CppUnitTest.h"
#include <Map/Node.h>
#include <Creation/Create.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maps;
using namespace Engine::Entity;

namespace UnitTests {

TEST_CLASS(NodeTest) {
  TEST_METHOD(testContainsActorWhenNotContained) {
    Node* n = Creation::Create::newNode("TestableNode");
    Actor* a = Creation::Create::newActor("TestableActor");
    Assert::IsTrue(a != nullptr);
    n->addActor(a);

    Assert::IsTrue(n->containsActor(a));
    delete n;
  }

  TEST_METHOD(testContainsActorWhenContained) {
    Node n;
    Actor* a = Creation::Create::newActor("TestableActor");
    Assert::IsFalse(a == nullptr);
    Assert::IsFalse(n.containsActor(a));
    delete a;
  }
};

}