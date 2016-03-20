#include <assert.h>
#include <iostream>
#include <string>
#include "Creature.h"
#include "Inventory.h"

Creature::Creature(): name("Creature")
  , inventory(Inventory{"Inv", 0})
  , isLiving(false) {
}

Creature::~Creature() {
}

void Creature::onDamage(int dmg) { // Should return damage taken
  // TODO: Update this for armor
  // modify dmg value based on armor
  if ( getIsLiving() ) {
    std::cout << getName() << " is hit for " << dmg << ". ";
    flagInCombat(true);
  }
  health -= dmg;
  if ( health <= 0 ) {
    health = 0;
    isLiving = false;
  }
  if (!getIsLiving()) {
    std::cout << getName() << " has been killed. ";
  }
  std::cout << std::endl;
}

void Creature::onHeal(int heal) {
  assert(heal >= 0);
  // TODO: Modify heal with abilities/ items
  if (getIsLiving()) {
    health += heal;
    if (health > maxHealth) {
      health = maxHealth;
    }
  }
  std::cout << getName() << " is healed for " << heal << ". " << std::endl;
}

void Creature::setHealth(int health) {
  this->health = health;
  isLiving = health > 0;
}

void Creature::setMaxHealth(int maxHealth) {
  this->maxHealth = maxHealth;
  setHealth(maxHealth);
}

void Creature::setIsLiving(bool isLiving)
{
  this->isLiving = isLiving;
}

void Creature::combatStop() {
  flagInCombat(false);
}

void Creature::flagInCombat(bool val) {
  isInCombat = val;
}

void Creature::setName(std::string name) {
  this->name = name;
}

void Creature::kill() {
  onDamage( health );
}

void Creature::useItem(Item &item, Creature &usedOn) {
  // TODO: Implement
  item.use(*this, usedOn);
}

void Creature::displayHUDLine() {
  if (!isLiving) {
    std::cout << "<Dead> ";
  }
  std::cout << name << ": " << health << "/"
    << maxHealth;
}

void Creature::save()
{
  startSave("Creature");
  // TODO: Check this
  // isLiving set from health?
  // isInCombat not important to save
  SAVE(name);
  SAVE(level);
  SAVE(experience);
  SAVE(health);
  SAVE(maxHealth);
  equipment.save();
  inventory.save();
  endSave();
}

void Creature::load()
{
  startLoad("Creature");
  LOAD(name);
  LOAD(level);
  LOAD(experience);
  LOAD(health);
  LOAD(maxHealth);
  equipment.load();
  inventory.load();
  endLoad();
}

