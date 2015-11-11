#include "Item.h"
#include "Creature.h"
#include <iostream>

Item::Item(): damage(0)
  , heal(0)
  , isDepletedOnUse(false)
  , stackSize(1)
  , name("Item") {

}
Item::Item(int damage, int heal, bool isDepletedOnUse, int stackSize, std::string name): damage(damage)
  , heal(heal)
  , isDepletedOnUse(isDepletedOnUse)
  , name(name)
  , stackSize(stackSize) {
}

Item::~Item() {
}

// Operators
std::ostream &operator<<(std::ostream &os, const Item &item) {
  os << item.name << item.damage << " " << item.heal << " "
  << item.isDepletedOnUse << " " << " " << item.stackSize;
  return os;
}

std::istream &operator>>(std::istream &is, Item &item) {
  is >> item.name >> item.damage >> item.heal
  >> item.isDepletedOnUse >> item.stackSize;
  return is;
}

bool Item::getIsDepletedOnUse() {
  return isDepletedOnUse;
}

std::string Item::getName() {
  return name;
}

void Item::onUse(Creature* user) {
  user->onAssistDamage(damage);
  user->onHeal(heal);
}

int Item::getDamage() {
  return damage;
}

int Item::getHeal() {
  return heal;
}

int Item::getStackSize() {
  return stackSize;
}
