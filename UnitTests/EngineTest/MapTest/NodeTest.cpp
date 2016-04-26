#include <string>
#include "CppUnitTest.h"
#include <Map/Node.h>
#include <Creation/Create.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

namespace UnitTests {

TEST_CLASS(NodeTest) {
  TEST_METHOD(testContainsActorWhenNotContained) {
    Node n;
    Actor* a = Creation::Create::newActor("TestableActor");
    Assert::IsTrue(a != nullptr);
    n.addActor(a);

    Assert::IsTrue(n.containsActor(a));
  }

  TEST_METHOD(testContainsActorWhenContained) {
    Node n;
    Actor* a = Creation::Create::newActor("TestableActor");
    Assert::IsFalse(a == nullptr);
    Assert::IsFalse(n.containsActor(a));
  }

  TEST_METHOD(testNodeSave) {
    Node n;
    Assert::IsFalse(n.canLoad("Node"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.save();

    Assert::IsTrue(n.canLoad("Node"));
  }

  TEST_METHOD(testNodeLoad) {
    Node n;
    Node saved;
    Actor* a = Create::newActor("TestableActor");
    saved.addActor(a);
    saved.save();

    Assert::IsTrue(n.canLoad("Node"));
    n.load();
    Assert::IsTrue(n.getNumActors() == 1, L"Incorrect number of Actors in node.");
    Assert::IsTrue(n.getActorPtr(0) != nullptr, L"First actor is null");
  }
};

}