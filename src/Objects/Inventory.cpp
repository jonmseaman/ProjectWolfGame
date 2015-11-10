#include <iostream>
#include <iomanip>
#include <assert.h>
#include "dLog.h"
#include "Inventory.h"

Inventory::Inventory():Inventory("Inventory", 2) {}

Inventory::Inventory(std::string name, int inventorySize): name(name)
  , slots{inventorySize, nullptr}
  , inventorySize(inventorySize) {}

Inventory::~Inventory() {
  for (int i(0); i<slots.size(); ++i) {
    delete slots.at(i);
  }
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
  if ( hasOpenSlot() ) {
    slots.at(firstEmpty()) = item;
    return true;
  }
  else
  {
    delete item;
    return false;
  }
}

bool Inventory::removeItem(int slotIndex) {
  slots.at(slotIndex) = nullptr;
  return true;
}

void Inventory::deleteItem(int slotIndex) {
  assert ( slotIndex>=0 && slotIndex<slots.size() );
  delete slots.at(slotIndex);
  slots.at(slotIndex) = nullptr;
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
  for (int i(0); i<slots.size(); i++) {
    if (slots.at(i) == nullptr) {
      return i;
    }
  }
  return 0;
}

void Inventory::show() {
  std::cout << getName() << std::endl;
  for (int i(0); i<slots.size(); i++) {
    if (slots.at(i) == nullptr ) {
      std::cout << std::setw(3) << std::right << i+1 << ": " << "Empty Slot\n";
    }
    else
    {
      std::cout << std::setw(3) << std::right << i+1 << ": " << slots.at(i)->getName() << std::endl;
    }
  }
}

bool Inventory::useItem(int itemIndex, Creature_Interface* user) {
  assert ( (slots.size() > itemIndex) && (itemIndex >= 0));
  if ( slots.at(itemIndex) != nullptr ) {
    slots.at(itemIndex)->onUse(user);
    return true;
  }
  else
  {
    return false;
  }
}

Item* Inventory::getItem(int slotIndex) {
  if (slotIndex>=0 && slotIndex<slots.size()) {
    return slots.at(slotIndex);
  }
  return nullptr;
}
