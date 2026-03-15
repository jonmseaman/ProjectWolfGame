#include <gtest/gtest.h>
#include <string>
#include <Entity/Actor.h>
#include <Map/Node.h>
#include <Creation/Create.h>

using namespace Engine::Maps;
using namespace Engine::Entity;
using namespace Creation;

namespace UnitTests {

TEST(NodeTest, testContainsActorWhenNotContained) {
    Node n;
    auto a = Creation::Create::newActor("TestableActor");
    Actor* rawA = a.get();
    EXPECT_TRUE(rawA != nullptr);
    n.addActor(std::move(a));

    EXPECT_TRUE(n.containsActor(rawA));
}

TEST(NodeTest, testContainsActorWhenContained) {
    Node n;
    auto a = Creation::Create::newActor("TestableActor");
    Actor* rawA = a.get();
    EXPECT_FALSE(rawA == nullptr);
    EXPECT_FALSE(n.containsActor(rawA));
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
    saved.addActor(Create::newActor("TestableActor"));
    saved.save();
    File::save("NodeTest_testNodeLoad");
    File::load("NodeTest_testNodeLoad");

    EXPECT_TRUE(n.canLoad("Node"));
    n.load();
    EXPECT_EQ(n.getNumActors(), 1);
    EXPECT_TRUE(n.getActorPtr(0) != nullptr);
}

} // namespace UnitTests
