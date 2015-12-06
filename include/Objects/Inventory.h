#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <vector>
#include "File.h"
#include "Item.h"

class Inventory
{
  public:
    Inventory();
    Inventory(std::string name, int inventorySize);
    virtual ~Inventory();
    virtual pairType toTree();
    /**
     * Gets data from p.
     * @attention Deletes all items that are already in this inventory.
     * @param p The key, tree pair that data will be gathered from.
     */
    void fromTree(const pairType& p);

    /**
     * Tries to add item to the inventory.
     * @return True if the item was added. False otherwise.
     */
    bool addItem(Item* item);
    /**
     * Tries to add the item to the inventory
     * Deletes the item if there is not an open slot;
     * @return True if the item was added. False otherwise.
     */
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
    /**
     * Returns the index of the first empty slot.
     * @return The index of the first empty slot or -1 if the
     * an empty slot is not found.
     */
    int firstEmpty();
    void showListOfItems();
  protected:
    std::string name;
    std::vector<Item*> slots;
    int size;
  private:
};

#endif // INVENTORY_H
