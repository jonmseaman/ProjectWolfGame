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

void Creature::onAttack() // TODO: Update for stats class
{ // TODO: Update for weapons
  assert( targetPtr != nullptr );
  int damage = stats.getStrength();
  // damage += damage from weapon
  // TODO: Update this for items.
  // TODO: Update combat text
  // TODO: No weapon equipped --> fists
  std::cout << getName() << " swings for " << damage << ". " << std::endl;
  targetPtr->onDamage( damage );
}

/** This function handles creatures being damaged
 *
 * @param dmg The amount of damage that this creature
 */
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
  // TODO: Modify heal with abilities/ items
  health += heal;
  if (health > maxHealth) {
    health = maxHealth;
  }
}

void Creature::setHealth(int health) {
  this->health = health;
  if (health > 0 ) {
    isLiving = true;
  }
  else
  {
    isLiving = false;
  }
}

void Creature::setMaxHealth(int maxHealth) {
  this->maxHealth = maxHealth;
  setHealth(maxHealth);
}

void Creature::setTarget(Creature* creature) {
  targetPtr = creature;
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
