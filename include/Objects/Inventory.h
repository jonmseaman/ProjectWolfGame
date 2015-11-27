#ifndef INVENTORY_H
#define INVENTORY_H
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>
#include "Item.h"
#include "File.h"
class Inventory
{
  public:
    Inventory();
    Inventory(std::string name, int inventorySize);
    virtual ~Inventory();
    virtual pairType toXML();
    void fromXML(const pairType& p);

    bool addItem(Item* item);
    bool addNewItem(Item* item);
    void deleteItem(int slotIndex); // Deletes item
    bool removeItem(int slotIndex); // Removes item from slot without freeing memory
    /**
     * Allows access to the items in the inventory
     * @pre There is an item in slot slotIndex
     */
    Item *getItem(int slotIndex);
    /**
     * Checks to see if a slot is empty.
     * @param slotIndex The index of the item slot being checked
     * @pre 0 <= slotIndex < size
     * @return Returns true if there is nothing in that item slot.
     */
    bool isSlotEmpty(int slotIndex);
    std::string getName();
    int getSlots();
    bool hasOpenSlot();
    int firstEmpty();
    void showListOfItems();
  protected:
    std::string name;
    std::vector<Item*> slots;
    int size;
  private:
};

#endif // INVENTORY_H
