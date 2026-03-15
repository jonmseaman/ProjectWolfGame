#ifndef INVENTORY_H
#define INVENTORY_H
#include <memory>
#include <string>
#include <vector>
#include <Engine.h>
#include "Item.h"
#include "Savable.h"

namespace Engine {
namespace Entity {

class ENGINE_API Inventory : public File::Savable {
public:
  Inventory();
  Inventory(std::string name, int inventorySize);
  virtual ~Inventory();
  Inventory(Inventory&&) = default;
  Inventory& operator=(Inventory&&) = default;
  SAVABLE_CLEAR;
  

  /**
   * Tries to add item to the inventory.
   * Takes ownership. Destroys the item if there is no open slot.
   * @return True if the item was added. False otherwise.
   */
  bool addItem(std::unique_ptr<Item> item);
  /**
   * Removes item from slot, transferring ownership to the caller.
   */
  std::unique_ptr<Item> removeItem(int slotIndex);

  /**
   * Allows non-owning access to items in the inventory.
   * @pre 0 <= slotIndex <= inventory.size
   */
  Item* at(int slotIndex);
  /**
   * Checks to see if a slot is empty.
   * @param slotIndex The index of the item slot being checked
   * @pre 0 <= slotIndex < size
   * @return Returns true if there is nothing in that item slot.
   */
  bool isSlotEmpty(int slotIndex);
  std::string getName() const;
  int getSlots() const;
  bool hasOpenSlot() const;
  /**
   * Returns the index of the first empty slot.
   * @return The index of the first empty slot or -1 if the
   * an empty slot is not found.
   */
  int firstEmpty();
  void showListOfItems();
protected:
  std::string name;
  std::vector<std::unique_ptr<Item>> slots;
  int size;
private:
};

}
}

#endif // INVENTORY_H
