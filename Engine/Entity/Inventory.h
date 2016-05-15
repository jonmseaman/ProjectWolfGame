#ifndef INVENTORY_H
#define INVENTORY_H
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
  SAVABLE_CLEAR;

  bool addItem(Item* item);
  bool addNewItem(Item* item);
  Item* removeItem(int slotIndex); // Removes item from slot without freeing memory

  Item*& at(int slotIndex);

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

}
}

#endif // INVENTORY_H
