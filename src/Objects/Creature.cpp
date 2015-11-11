#include <iostream>
#include <string>
#include <assert.h>
#include "Inventory.h"
#include "Creature.h"
#include "utils.h"
#include "dLog.h"

Creature::Creature(): name("Creature")
  , targetPtr(nullptr)
  , inventory(Inventory{"Inv", 0})
  , isLiving(false)
  , isInCombat(false) {
  dLog << "Creature ctor called" << std::endl;
}

Creature::~Creature() {
  dLog << "Creature dtor called" << std::endl;
}

int Creature::onAttack() // TODO: Update for stats class
{ // TODO: Update for weapons
  assert( targetPtr != nullptr );
  int damage = stats.getStrength();
  // damage += damage from weapon
  // TODO: Update this for items.
  // TODO: Update combat text
  // TODO: No weapon equipped --> fists
  std::cout << getName() << " swings for " << damage << ". " << std::endl;
  return targetPtr->onDamage( damage );
}

/** This function handles creatures being damaged
 *
 * @param dmg The amount of damage that this creature
 */
int Creature::onDamage(int dmg) { // Should return damage taken
  // TODO: Update this for armor
  // modify dmg value based on armor
  if ( getIsLiving() ) {
    std::cout << getName() << " is hit for " << dmg << ". ";
    flagInCombat(true);
  }
  stats.health -= dmg;
  if ( stats.health <= 0 ) {
    stats.health = 0;
    isLiving = 0;
  }
  if (!getIsLiving()) { std::cout << getName() << " is dead. "; }
  std::cout << std::endl;
  return dmg;
}

int Creature::onHeal(int heal) {
  // TODO: Modify heal with abilities/ items
  stats.health += heal;
  if (stats.health > stats.maxHealth) stats.health = stats.maxHealth;
  return heal; // FIXME: make this return the amount healed
}

void Creature::setHealth(int health) {
  stats.health = health;
  if (health > 0 ) {
    isLiving = true;
  }
  else
  {
    isLiving = false;
  }
}

void Creature::setMaxHealth(int maxHealth) {
  stats.maxHealth = maxHealth;
  setHealth(maxHealth);
}

void Creature::setTarget(Creature* creature) {
  targetPtr = creature;
}

void Creature::setStrength(int strength) {
  stats.strength = strength;
}

void Creature::combatStop() { // Takes creature out of combat and removes targets
  flagInCombat(false);
  setTarget(nullptr);
}

void Creature::flagInCombat(bool val) {
  isInCombat = val;
}

void Creature::setName(std::string name) {
  this->name = name;
}

void Creature::kill() {
  onDamage( stats.getHealth() );
}

void Creature::onAssistDamage(int dmg) {
  assert( targetPtr != nullptr );
  targetPtr->onDamage(dmg);
}

void Creature::onAssistHeal(int heal) {
  if ( targetPtr != nullptr ) {
    targetPtr->onHeal(heal);
  }
}

//void Creature::setInventory(const Inventory &inventory)
//{
//  this->inventory = inventory;
//}

void Creature::useItemFromInventory(int itemNumber) {
  inventory.useItem(itemNumber, this);
}

void Creature::displayHUDLine() {
  if (!isLiving) {
    std::cout << "<Dead> ";
  }
  std::cout << name << ": " << stats.getHealth() << "/"
    << stats.getMaxHealth();
}
