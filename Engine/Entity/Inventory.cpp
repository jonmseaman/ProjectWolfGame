#include <iostream>
#include <iomanip>
#include <assert.h>
#include <Creation/Create.h>
#include "Inventory.h"

namespace Engine {
namespace Entity {

using namespace Creation;

Inventory::Inventory() :Inventory("Inventory", 2) {}

Inventory::Inventory(std::string name, int size) : name(name)
, slots{ size, nullptr }
, size(size) {}

Inventory::~Inventory() {
  for (int i(0); i < slots.size(); ++i) {
    delete slots.at(i);
  }
}

void Inventory::clearSavable() {
  for (auto& item : slots) {
    delete item;
    item = nullptr;
  }
}

void Inventory::save() {
  startSave("Inventory");
  SAVE(name);
  SAVE(size);
  // Save items
  for (Item* i : slots) {
    if (i != nullptr) {
      i->save();
    }
  }
  endSave();
}

void Inventory::load() {
  clearSavable();
  startLoad("Inventory");
  LOAD(name);
  LOAD(size);
  while (Savable::canLoad("Item")) {
    this->addNewItem(Create::loadNewItem());
  }
  endLoad();
}

/**
* Tries to add item to the inventory.
* @return True if the item was added. False otherwise.
*/
bool Inventory::addItem(Item* item) {
  if (hasOpenSlot()) {
    slots.at(firstEmpty()) = item;
    return true;
  } else {
    return false;
  }
}

/**
* Tries to add the item to the inventory
* Deletes the item if there is not an open slot;
* @return True if the item was added. False otherwise.
*/
bool Inventory::addNewItem(Item* item) {
  bool addedItem = false;
  if (hasOpenSlot()) {
    slots.at(firstEmpty()) = item;
    addedItem = true;
  } else {
    delete item;
  }
  return addedItem;
}

Item* Inventory::removeItem(int slotIndex) {
  Item* removed = slots.at(slotIndex);
  slots.at(slotIndex) = nullptr;
  return removed;
}

std::string Inventory::getName() {
  return name;
}

int Inventory::getSlots() {
  return slots.size();
}

bool Inventory::hasOpenSlot() {
  for (int i(0); i < slots.size(); i++) {
    if (slots.at(i) == nullptr) {
      return true;
    }
  }
  return false;
}

/**
* Returns the index of the first empty slot.
* @return The index of the first empty slot or -1 if the
* an empty slot is not found.
*/
int Inventory::firstEmpty() {
  for (int i(0); i < slots.size(); i++) {
    if (slots.at(i) == nullptr) {
      return i;
    }
  }
  return -1;
}

void Inventory::showListOfItems() {
  std::cout << getName() << std::endl;
  for (int i(0); i < slots.size(); i++) {
    if (slots.at(i) == nullptr) {
      std::cout << std::setw(3) << std::right << i + 1 << ": " << "Empty Slot\n";
    } else {
      std::cout << std::setw(3) << std::right << i + 1 << ": " << slots.at(i)->getName() << std::endl;
    }
  }
}

/**
* Allows access to items in the inventory.
* @pre 0 <= slotIndex <= inventory.size
*/
Item *& Inventory::at(int slotIndex) {
  return this->slots.at(slotIndex);
}

/**
* Checks to see if a slot is empty.
* @param slotIndex The index of the item slot being checked
* @pre 0 <= slotIndex < size
* @return Returns true if there is nothing in that item slot.
*/
bool Inventory::isSlotEmpty(int slotIndex) {
  assert(0 <= slotIndex && slotIndex < size);
  return slots.at(slotIndex) == nullptr;
}

}
}
