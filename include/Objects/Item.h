#ifndef ITEM_H
#define ITEM_H
#include <assert.h>
#include <iostream>
#include <string>
#include "Stats.h"
class Creature;

/**
 * This is an item.
 */
class Item
{
  public:
    Item();
	Item(std::string name, std::string description, Stats stats);
	Item(std::string name, Stats stats);
    virtual ~Item();

    /**
     * Shows information about the item on std::cout
     * Shows name, description, stats.
     */
    void showInfo();

    /**
     * Returns the name of the item.
     */
    std::string getName() { return name; }
    /**
     * Returns the description of the item.
     */
    std::string getDescription() { return description; }

	void setDescription(const std::string &description) { this->description = description; }

    /**
     * @param creature The creature being affected by the item
     * @pre creature != nullptr
     */
    virtual void useOn(Creature* creature);

    Stats stats;
  protected:
    std::string name;
    std::string description;

	int damage;
  private:

};

#endif // ITEM_H
