#include <iostream>
#include <iomanip>
#include <assert.h>
#include "dLog.h"
#include "File.h"
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

Item *Inventory::getItem(int slotIndex) {
  assert(slots.at(slotIndex) != nullptr);
  assert(0 <= slotIndex && slotIndex < slots.size());
  return slots.at(slotIndex);
}

bool Inventory::isSlotEmpty(int slotIndex) {
  assert(0 <= slotIndex && slotIndex < size);
  return !(slots.at(slotIndex) == nullptr);
}

pairType Inventory::toXML() {
  treeType tree{};

	tree.push_back(XML_VAR_SPAIR(name));
  tree.push_back(XML_VAR_PAIR(size));
  for (Item* item : slots) {
    if (item != nullptr) {
      tree.push_back(item->toXML());
    }
  }

	return pairType("Inventory", tree);
}

void Inventory::fromXML(const pairType& p) {
  // TODO: Loading
}
