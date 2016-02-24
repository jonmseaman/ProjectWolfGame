#include <iostream>
#include "Creature.h"
#include "Item.h"
#include "Savable.h"

Item::Item() :Item("Item", Stats()) {
}

Item::Item(std::string name, Stats stats) : Item(name, "", stats) {
  setID(0);
}

Item::Item(std::string name, std::string description, Stats stats) {
  setID(0);
  this->name = name;
  this->description = description;
  this->stats = stats;
  baseDamage = 1; // TODO: Add way to set these two variables
  baseHeal = 0;
}

Item::~Item() {
}

void Item::save()
{
  startSave("Item");
  SAVE(name);
  SAVE(description);
  SAVE(baseDamage);
  SAVE(baseHeal);
  stats.save();
  endSave();
}

void Item::load() {
  startLoad("Item");
  LOAD(name);
  LOAD(description);
  LOAD(baseDamage);
  LOAD(baseHeal);
  stats.load();
  endLoad();
}

void Item::use(const Creature &usedBy, Creature &usedOn) {
  // Derive stats from creature using item + this items stats
  Stats derivedStats = stats + usedBy.stats;
  // Do damage and healing
  if (baseDamage > 0) {
    int amountToDamage = baseDamage;
    amountToDamage += 2*derivedStats.getStrength();
    usedOn.onDamage(amountToDamage);
  }
  if (baseHeal > 0) {
    int amountToHeal = baseHeal;
    amountToHeal += 2*derivedStats.getIntellect();
    usedOn.onHeal(amountToHeal);
  }
}

void Item::showInfo() const {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Description: " << description << std::endl;
  stats.showStats();
}

bool operator==(const Item & l, const Item & r)
{
  return l.getName() == r.getName()
    && l.getDescription() == r.getDescription()
    && l.getDamage() == r.getDamage()
    && l.getHeal() == r.getHeal()
    && l.stats == r.stats;
}
