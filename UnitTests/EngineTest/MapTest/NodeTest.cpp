#include <gtest/gtest.h>
#include <string>
#include <Map/Node.h>
#include <Creation/Create.h>

using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

namespace UnitTests {

TEST(NodeTest, testContainsActorWhenNotContained) {
    Node n;
    Actor* a = Creation::Create::newActor("TestableActor");
    EXPECT_TRUE(a != nullptr);
    n.addActor(a);

    EXPECT_TRUE(n.containsActor(a));
}

TEST(NodeTest, testContainsActorWhenContained) {
    Node n;
    Actor* a = Creation::Create::newActor("TestableActor");
    EXPECT_FALSE(a == nullptr);
    EXPECT_FALSE(n.containsActor(a));
}

TEST(NodeTest, testNodeSave) {
    Node n;
    EXPECT_FALSE(n.canLoad("Node"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.addActor(Create::newActor("TestableActor"));
    n.save();

    EXPECT_TRUE(n.canLoad("Node"));
}

TEST(NodeTest, testNodeLoad) {
    File::clear(); // Clear progress from other saves.
    Node n;
    Node saved;
    Actor* a = Create::newActor("TestableActor");
    saved.addActor(a);
    saved.save();
    File::save("NodeTest_testNodeLoad");
    File::load("NodeTest_testNodeLoad");

    EXPECT_TRUE(n.canLoad("Node"));
    n.load();
    EXPECT_EQ(n.getNumActors(), 1);
    EXPECT_TRUE(n.getActorPtr(0) != nullptr);
}

} // namespace UnitTests
