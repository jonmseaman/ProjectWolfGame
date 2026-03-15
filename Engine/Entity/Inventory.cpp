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
, slots( static_cast<size_t>(size) )
, size(size) {}

Inventory::~Inventory() {}

void Inventory::clearSavable() {
  for (auto& item : slots) {
    item.reset();
  }
}

void Inventory::save() {
  startSave("Inventory");
  SAVE(name);
  SAVE(size);
  // Save items
  for (const auto& i : slots) {
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
    this->addItem(Create::loadNewItem());
  }
  endLoad();
}

bool Inventory::addItem(std::unique_ptr<Item> item) {
  if (hasOpenSlot()) {
    slots.at(firstEmpty()) = std::move(item);
    return true;
  }
  return false;
}

std::unique_ptr<Item> Inventory::removeItem(int slotIndex) {
  return std::move(slots.at(slotIndex));
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

Item* Inventory::at(int slotIndex) {
  return this->slots.at(slotIndex).get();
}

bool Inventory::isSlotEmpty(int slotIndex) {
  assert(0 <= slotIndex && slotIndex < size);
  return slots.at(slotIndex) == nullptr;
}

}
}
