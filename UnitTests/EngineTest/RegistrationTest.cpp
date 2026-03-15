#include <gtest/gtest.h>
#include <Entity/Item.h>
#include <Entity/Actor.h>
#include <Map/Node.h>
#include <Map/Map.h>
#include <Creation/Creatable.h>
#include <Creation/Create.h>
#include <Engine.h>

using namespace Engine::Entity;

namespace UnitTests {

#pragma region TestClassesForRegistration

// Class to test registration for;
class TestableItem : public Engine::Entity::Item {
public:
    CREATABLE_ITEM(TestableItem);
};
CREATABLE_REGISTRATION(TestableItem);

class TestableActor : public Engine::Entity::Actor {
public:
    CREATABLE_ACTOR(TestableActor);
};
CREATABLE_REGISTRATION(TestableActor);

class TestableNode : public Engine::Maps::Node {
public:
    CREATABLE_NODE(TestableNode);
};
CREATABLE_REGISTRATION(TestableNode);

class TestableMap : public Engine::Maps::Map {
public:
    TestableMap() : Map(5) {
        for (auto& n : this->grid) {
            n = new Node;
        }
        buildMoveData();
    }
    CREATABLE_MAP(TestableMap);
};
CREATABLE_REGISTRATION(TestableMap);

#pragma endregion

///<summary>
/// Tests that registration works for items.
/// Tests are also completed for Actors, Nodes, as well as Maps.
///</summary>
TEST(RegistrationTest, testItemRegistration) {
    void* ent = Creation::Create::newItem("TestableItem");
    EXPECT_TRUE(ent != nullptr);
}

TEST(RegistrationTest, testActorRegistration) {
    void* ent = Creation::Create::newActor("TestableActor");
    EXPECT_TRUE(ent != nullptr);
}

TEST(RegistrationTest, testNodeRegistration) {
    void* node = Creation::Create::newNode("TestableNode");
    EXPECT_TRUE(node != nullptr);
}

TEST(RegistrationTest, testMapRegisration) {
    void* map = Creation::Create::newMap("TestableMap");
    EXPECT_TRUE(map != nullptr);
}

} // namespace UnitTests
