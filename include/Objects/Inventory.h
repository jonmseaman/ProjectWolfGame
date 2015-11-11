#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <vector>
#include "Item.h"
class Inventory
{
  public:
    Inventory();
    Inventory(std::string name, int inventorySize);
    virtual ~Inventory();
    friend std::ostream &operator<<(std::ostream &os, const Inventory &inventory);
    friend std::istream &operator>>(std::istream &is, Inventory &inventory);
    bool addItem(Item* item);
    bool addNewItem(Item* item);
    void deleteItem(int slotIndex); // Deletes item
    bool removeItem(int slotIndex); // Removes item from slot without freeing memory
    Item* getItem(int slotIndex);
    std::string getName();
    int getSlots();
    bool hasOpenSlot();
    int firstEmpty();
    void show();
    bool useItem(int itemIndex, Creature* user);
  protected:
    std::string name;
    std::vector<Item*> slots;
    int inventorySize;
  private:
};

// Operators
std::ostream &operator<<(std::ostream &os, const Inventory &inventory);
std::istream &operator>>(std::istream &is, Inventory &inventory);

#endif // INVENTORY_H
