#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include "Stats.h"
#include "Inventory.h"
#include "Equipment.h"

/**
 * This class should store all functions for defining what a creature is.
 */
class Creature
{
    // The data structure for the creatures.
    // This class should contain the data and tools for making functioning actors in the game world,
    //    but not actually include a way to _act_
  public:
    Creature();
    virtual ~Creature();
    void combatStop(); // Takes creature out of combat and removes targets

    // Data Access
    std::string getName() { return name; }
    bool getIsInCombat() { return isInCombat; }
    bool getIsLiving() { return isLiving; }
    Creature *getTarget() { return targetPtr; } // returns target of creature
    void setHealth(int health);
    void setMaxHealth(int maxHealth); // Set max hp, also sets hp
    void setIsLiving(bool isLiving); // Can be used to kill a creature
    void setTarget(Creature* creature);
    bool hasTarget() { return targetPtr != nullptr; }
    // Experience
    void levelUp();
    int experienceToNextLevel();
    void addExperience(int xp);

    // Creature stuff

    /**
     * Uses an item. Applys effects to this if the item is 'defensive'
     * or applies the effects to the target if offensive
     * @param item The item being used.
     * @param usedOn The creature that the item is being used on.
     */
    void useItem(Item &item, Creature &usedOn);
    void onAttack();
    void onDamage(int dmg);
    void onHeal(int heal);
    void kill(); // Reduces creature health to zero. Sets isLiving to false

    // Display
    void displayHUDLine();

    Equipment equipment;
    Inventory inventory;

    // Stats
    Stats stats;


  protected:
    void flagInCombat(bool val); // sets combat status
    void setName(std::string name); // sets that name of the creature
    // Targets
    Creature* targetPtr;
  private:
    std::string name;
    // Utility vars
    bool isLiving; // TODO: Remove this variable
    bool isInCombat;

    // XP Variables
    int level; // Creatures level
    int experience; // Experience earned this level

    // Derived stats
    int health;
    int maxHealth; // This should be calculated.
};

#endif // CREATURE_H
