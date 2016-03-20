#include <iostream>
#include <iomanip>
#include <assert.h>
#include "Map/Create.h"
#include "Inventory.h"

Inventory::Inventory():Inventory("Inventory", 2) {}

Inventory::Inventory(std::string name, int size): name(name)
  , slots{ size, nullptr}
  , size(size) {}

Inventory::~Inventory() {
  for (int i(0); i<slots.size(); ++i) {
    delete slots.at(i);
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
  startLoad("Inventory");
  LOAD(name);
  LOAD(size);
  while (Savable::canLoad("Item"))
  {
    this->addNewItem(Create::loadNewItem());
  }
  endLoad();
}

bool Inventory::addItem(Item* item) {
  if ( hasOpenSlot() ) {
    slots.at(firstEmpty()) = item;
    return true;
  }
  else
  {
    return false;
  }
}

bool Inventory::addNewItem(Item* item) {
  bool addedItem = false;
  if ( hasOpenSlot() ) {
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
  for (int i(0); i<slots.size(); i++) {
    if (slots.at(i) == nullptr) {
      return true;
    }
  }
  return false;
}

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
  for (int i(0); i<slots.size(); i++) {
    if (slots.at(i) == nullptr ) {
      std::cout << std::setw(3) << std::right << i+1 << ": " << "Empty Slot\n";
    } else {
      std::cout << std::setw(3) << std::right << i+1 << ": " << slots.at(i)->getName() << std::endl;
    }
  }
}

Item *& Inventory::at(int slotIndex) {
    return this->slots.at(slotIndex);
}

bool Inventory::isSlotEmpty(int slotIndex) {
  assert(0 <= slotIndex && slotIndex < size);
  return slots.at(slotIndex) == nullptr;
}
