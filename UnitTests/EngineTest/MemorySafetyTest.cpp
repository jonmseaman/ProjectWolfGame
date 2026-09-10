#include <gtest/gtest.h>
#include <Creation/Creatable.h>

import std;
import Engine;

using namespace Engine::Entity;
using namespace Engine::Maps;
using namespace Creation;

namespace UnitTests {
    class SafetyActor : public Actor {
    public:
        CREATABLE_ACTOR(SafetyActor)
    };

    CREATABLE_REGISTRATION(SafetyActor);

    // --- Node::getActorPtr bounds ---

    TEST(MemorySafetyTest, getActorPtrRejectsIndexEqualToCount) {
        // The bound was `> size`, so this index slipped through and the function
        // dereferenced an end() iterator, returning a garbage pointer.
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        ASSERT_EQ(1, node.getNumActors());
        EXPECT_THROW(node.getActorPtr(node.getNumActors()), std::out_of_range);
        EXPECT_THROW(node.getActorPtr(1), std::out_of_range);
    }

    TEST(MemorySafetyTest, getActorPtrRejectsNegativeAndFarIndices) {
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        EXPECT_THROW(node.getActorPtr(-1), std::out_of_range);
        EXPECT_THROW(node.getActorPtr(99), std::out_of_range);
    }

    TEST(MemorySafetyTest, getActorPtrOnAnEmptyNodeThrows) {
        Node node;
        EXPECT_THROW(node.getActorPtr(0), std::out_of_range);
    }

    TEST(MemorySafetyTest, getActorPtrReturnsEachActorInOrder) {
        Node node;
        auto first = Create::newActor("SafetyActor");
        auto second = Create::newActor("SafetyActor");
        Actor *firstRaw = first.get();
        Actor *secondRaw = second.get();
        node.addActor(std::move(first));
        node.addActor(std::move(second));
        EXPECT_EQ(firstRaw, node.getActorPtr(0));
        EXPECT_EQ(secondRaw, node.getActorPtr(1));
    }

    // --- Members that used to be left indeterminate ---

    TEST(MemorySafetyTest, freshActorHasNoTargetAndNoNode) {
        Actor actor;
        EXPECT_EQ(nullptr, actor.getTarget());
        EXPECT_FALSE(actor.getIsTurnUsed());
        EXPECT_EQ(Dir::STOP, actor.getMoveDir());
    }

    TEST(MemorySafetyTest, freshCreatureHasDefinedStats) {
        // health / maxHealth / level / experience were all indeterminate, and
        // displayHUDLine() and onDamage() read them immediately.
        Actor actor;
        EXPECT_FALSE(actor.getIsLiving());
        EXPECT_FALSE(actor.getIsInCombat());
        EXPECT_EQ("Creature", actor.getName());
    }

    TEST(MemorySafetyTest, freshActorDoesNotActOnAnIndeterminateTarget) {
        // hasValidTarget() reads targetPtr and then currentNode. With both
        // indeterminate this was undefined behaviour on the very first turn.
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        Actor *actor = node.getActorPtr(0);
        EXPECT_NO_THROW(actor->takeTurn());
    }

    // --- Actor::dropItem ---

    TEST(MemorySafetyTest, dropItemWithoutANodeThrowsInsteadOfDereferencingNull) {
        Actor actor;
        EXPECT_THROW(actor.dropItem(0), std::logic_error);
    }

    TEST(MemorySafetyTest, dropItemRejectsIndicesOutsideTheInventory) {
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        Actor *actor = node.getActorPtr(0);
        EXPECT_THROW(actor->dropItem(-1), std::out_of_range);
        EXPECT_THROW(actor->dropItem(actor->inventory.getSlots()), std::out_of_range);
    }

    TEST(MemorySafetyTest, droppingAnEmptySlotReportsFailure) {
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        Actor *actor = node.getActorPtr(0);
        // A Creature is built with a zero slot inventory, so give it some room.
        actor->inventory = Inventory{"Pack", 4};
        ASSERT_GT(actor->inventory.getSlots(), 0);
        EXPECT_FALSE(actor->dropItem(0));
    }

    TEST(MemorySafetyTest, droppingAnItemMovesItToTheNode) {
        Node node;
        node.addActor(Create::newActor("SafetyActor"));
        Actor *actor = node.getActorPtr(0);
        actor->inventory = Inventory{"Pack", 4};
        ASSERT_TRUE(actor->inventory.addItem(Create::newItem("Item")));
        EXPECT_TRUE(actor->dropItem(0));
        EXPECT_TRUE(actor->inventory.isSlotEmpty(0));
        EXPECT_FALSE(node.inventory.isSlotEmpty(0));
    }

    // --- Inventory sizing across a save / load ---

    TEST(MemorySafetyTest, loadingRestoresTheInventorySize) {
        File::clear();
        Inventory saved{"Backpack", 10};
        ASSERT_TRUE(saved.addItem(Create::newItem("Item")));
        saved.save();
        File::save("safety_inventory");
        File::load("safety_inventory");

        // Deliberately a different size, so a load that does not resize leaves
        // getSlots() and the saved size disagreeing.
        Inventory loaded{"Pouch", 2};
        loaded.load();

        EXPECT_EQ(10, loaded.getSlots());
        EXPECT_EQ("Backpack", loaded.getName());
        EXPECT_FALSE(loaded.isSlotEmpty(0));
        // Every reported slot must be addressable.
        for (int i = 0; i < loaded.getSlots(); i++) {
            EXPECT_NO_THROW(loaded.isSlotEmpty(i));
        }
    }

    TEST(MemorySafetyTest, aNegativeSavedInventorySizeIsRejected) {
        // Build an Inventory entry by hand carrying a negative size.
        File::clear();
        struct Forged : public File::Savable {
            void save() override {
                startSave("Inventory");
                Savable::save("name", std::string("Forged"));
                Savable::save("size", -5);
                endSave();
            }

            void load() override {
            }
        } forged;
        forged.save();
        File::save("safety_bad_inventory");
        File::load("safety_bad_inventory");

        Inventory loaded{"Pouch", 2};
        EXPECT_THROW(loaded.load(), File::SaveError);
    }

    // --- Map::save with an unfilled grid ---

    TEST(MemorySafetyTest, savingAMapWithAnEmptySlotThrows) {
        File::clear();
        class HalfBuilt : public Map {
        public:
            HalfBuilt() : Map(2) {
            } // Map(int) leaves every slot null
        } map;
        EXPECT_THROW(map.save(), std::logic_error);
    }

    // --- Item equality is const ---

    TEST(MemorySafetyTest, constItemsCompareEqual) {
        const Item a{"Sword", "sharp", Stats{1, 2, 3}};
        const Item b{"Sword", "sharp", Stats{1, 2, 3}};
        EXPECT_TRUE(a == b);
    }
} // namespace UnitTests
