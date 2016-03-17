#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "Stats.h"
class Creature;

/**
 * This is an item.
 */
class Item : public File::Savable
{
  public:
    Item();
    Item(std::string name, std::string description, Stats stats);
    Item(std::string name, Stats stats);
    virtual ~Item();
    SAVABLE; // load and save functions

    /**
     * Shows information about the item on std::cout
     * Shows name, description, stats.
     */
    void showInfo() const;

    /**
     * Returns the name of the item.
     */
    std::string getName() const { return name; }
    /**
     * Returns the description of the item.
     */
    std::string getDescription() const { return description; }

    void setDescription(const std::string &description) { this->description = description; }

    int getDamage() const { return baseDamage; }
    int getHeal() const { return baseHeal; }
    void setDamage(int damage) { baseDamage = damage; }
    void setHeal(int heal) { baseHeal = heal; }

    /**
     * This function allows the this to be used. Stats are gathered from usedBy
     * then the damage or healing to actually deal is computed and sent to
     * usedOn so that usedOn may receive damage or healing.
     *
     * @param usedBy The creature using the item. Stats are used from this
     * creature to compute the damage to deal.
     * @param usedOn The creature the item is actually affecting.
     * @post usedOn will have been affected by the item.
     */
     virtual void use(const Creature &usedBy, Creature &usedOn);
     Stats stats;
    bool operator==(const Item& r);
  protected:
    std::string name;
    std::string description;
    int baseDamage;
    int baseHeal;
};


#endif // ITEM_H
