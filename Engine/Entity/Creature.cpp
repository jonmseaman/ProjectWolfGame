module;
#include "EngineMacros.h"
#include "SavableMacros.h"

module Engine;

import std;

namespace Engine {
namespace Entity {

// health, maxHealth, level, experience and isInCombat were all left
// indeterminate here; displayHUDLine() and onDamage() read them straight
// away. They carry their defaults in the header now, which also puts this
// constructor's initialiser list back in declaration order.
Creature::Creature() : inventory(Inventory{ "Inv", 0 }) {}

Creature::~Creature() {}

void Creature::onDamage(int dmg) { // Should return damage taken
  // TODO: Update this for armor
  // modify dmg value based on armor
  if (getIsLiving()) {
    std::cout << getName() << " is hit for " << dmg << ". ";
    flagInCombat(true);
  }
  health -= dmg;
  if (health <= 0) {
    health = 0;
    isLiving = false;
  }
  if (!getIsLiving()) {
    std::cout << getName() << " has been killed. ";
  }
  std::cout << std::endl;
}

void Creature::onHeal(int heal) {
  if (heal < 0) {
    throw std::invalid_argument("onHeal: heal amount cannot be negative");
  }
  if (getIsLiving()) {
    health += heal;
    if (health > maxHealth) {
      health = maxHealth;
    }
  }
  std::cout << getName() << " is healed for " << heal << ". " << std::endl;
}

void Creature::setHealth(int newHealth) {
  health = newHealth;
  isLiving = health > 0;
}

void Creature::setMaxHealth(int newMaxHealth) {
  maxHealth = newMaxHealth;
  setHealth(maxHealth);
}

void Creature::setIsLiving(bool living) {
  isLiving = living;
}

void Creature::combatStop() {
  flagInCombat(false);
}

void Creature::flagInCombat(bool val) {
  isInCombat = val;
}

void Creature::setName(const std::string& newName) {
  name = newName;
}

void Creature::kill() {
  onDamage(health);
}

void Creature::useItem(Item &item, Creature &usedOn) {
  item.use(*this, usedOn);
}

void Creature::displayHUDLine() {
  if (!isLiving) {
    std::cout << "<Dead> ";
  }
  std::cout << name << ": " << health << "/"
    << maxHealth;
}

void Creature::save() {
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

void Creature::load() {
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

}
}
