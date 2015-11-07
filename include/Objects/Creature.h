#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include "Stats.h"
#include "Inventory.h"
#include "Equipment.h"
class Creature : public Creature_Interface
{
    // The data structure for the creatures.
    // This class should contain the data and tools for making functioning actors in the game world,
    //    but not actually include a way to _act_
  public:
    Creature();
    virtual ~Creature();
    void combatStop(); // Takes creature out of combat and removes targets

    std::string getName() { return name; }
    bool getIsInCombat() { return isInCombat; } // returns true if the creature is in combat.
    bool getIsLiving() { return isLiving; } // Returns true if the creature is still alive
    Creature *getTarget() { return targetPtr; } // returns target of creature
    void kill(); // Reduces creature health to zero. Sets isLiving to false
    int onAttack();
    void onAssistDamage(int dmg); // Tries to damage this creature's target
    void onAssistHeal(int heal); // Tries to heal this creature's target
    int onDamage(int dmg); // Returns damage taken
    int onHeal(int heal); // Returns health gained

    void setHealth(int health);
    void setMaxHealth(int maxHealth); // Set max hp, also sets hp
    //void setInventory(const Inventory& inventory); // Sets inventory. Deletes old inv
    void setIsLiving(bool isLiving); // Can be used to kill a creature
    void setTarget(Creature* creature);
    void setStrength(int strength);
    void useItemFromInventory(int itemNumber);
    Inventory inventory;

    Stats stats;
  protected:
    void flagInCombat(bool val); // sets combat status
    void setName(std::string name); // sets that name of the creature
    // Targets
    Creature* targetPtr;
    // Inventory
    //TODO: Add equipment
    Equipment equipment;
  private:
    std::string name;
    // Utility vars
    bool isLiving; // TODO: Remove this variable
    bool isInCombat;
};

#endif // CREATURE_H
