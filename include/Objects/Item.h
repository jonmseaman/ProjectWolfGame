#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
#include "Creature_Interface.h"

/**
 * This is an item.
 */
class Item
{
  friend std::ostream &operator<<(std::ostream &os, const Item &item);
  friend std::istream &operator>>(std::istream &is, Item &item);
  public:
    Item();
    Item(int damage, int heal, bool isDepletedOnUse, int stackSize, std::string name);
    virtual ~Item();

    /**
     * Returns the amount of damage stat of the item.
     * Equivalent to the amount of damage done in one hit
     */
    int getDamage();

    /**
     * Returns the amount of healing the item does
     */
    int getHeal();

    /**
     * Returns true if the quantity of the item decreases when
     * the item is used
     */
    bool getIsDepletedOnUse();

    /**
     * Returns the maximum amount of the item that can be stacked
     */
    int getStackSize();
    /**
     * Returns the name of the item
     */
    std::string getName();
    virtual void onUse(Creature_Interface* user);
  protected:
    int damage; /// The damage that the item deals when used
    int heal;
    bool isDepletedOnUse;
    std::string name;
    int stackSize;
  private:

};

// Operators
std::ostream &operator<<(std::ostream &os, const Item &item);
std::istream &operator>>(std::istream &is, Item &item);

#endif // ITEM_H
