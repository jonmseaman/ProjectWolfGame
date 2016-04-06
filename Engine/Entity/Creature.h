#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <Engine.h>
#include "Equipment.h"
#include "Inventory.h"
#include "Savable.h"
#include "Stats.h"

namespace Engine {
namespace Entity {

/**
 * This class should store all functions for defining what a creature is.
 */
class ENGINE_API Creature : public File::Savable {
    // The data structure for the creatures.
    // This class should contain the data and tools for making functioning actors in the game world,
    // but not actually include a way to _act_

public:
    Creature();
    virtual ~Creature();

    SAVABLE; // load / save

    void combatStop(); // Takes creature out of combat and removes targets

    // Data Access
    char* getName() { return name; }
    void setName(char* name); // sets that name of the creature
    bool getIsInCombat() { return isInCombat; }
    bool getIsLiving() { return isLiving; }
    void setHealth(int health);
    void setMaxHealth(int maxHealth); // Set max hp, also sets hp
    void setIsLiving(bool isLiving); // Can be used to kill a creature

    // Experience
    void levelUp();
    int experienceToNextLevel();
    void addExperience(int xp);

    // Creature stuff

    /**
      * Uses an item. Applies effects to this if the item is 'defensive'
      * or applies the effects to the target if offensive
      * @param item The item being used.
      * @param usedOn The creature that the item is being used on.
      */
    void useItem(Item &item, Creature &usedOn);
    /**
     * T  his function handles creatures being damaged
     * Kills the creature if the damage is sufficient
     * @param dmg The amount of damage that this creature
     */
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
private:
    char* name;
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
}
}

#endif // CREATURE_H
