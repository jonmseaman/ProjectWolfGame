#include <assert.h>
#include <iostream>
#include <string>
#include "Creature.h"
#include "dLog.h"
#include "File.h"
#include "Inventory.h"
#include "utils.h"

Creature::Creature(): name("Creature")
  , inventory(Inventory{"Inv", 0})
  , isLiving(false) {
  dLog << "Creature ctor called" << std::endl;
}

Creature::~Creature() {
  dLog << "Creature dtor called" << std::endl;
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

pairType Creature::toXML() {
  using namespace boost::property_tree;
  ptree tree;

  tree.push_back(XML_VAR_SPAIR(name));
  tree.push_back(XML_VAR_PAIR(isLiving));
  tree.push_back(XML_VAR_PAIR(isInCombat));

  tree.push_back(XML_VAR_PAIR(level));
  tree.push_back(XML_VAR_PAIR(experience));

  tree.push_back(XML_VAR_PAIR(health));
  tree.push_back(XML_VAR_PAIR(maxHealth));

  tree.push_back(equipment.toXML());
  tree.push_back(inventory.toXML());

  tree.push_back(stats.toXML());

  return pairType("Creature", tree);
}

void Creature::fromXML(const pairType& p) {
  const treeType &tree = p.second;
  auto it = tree.begin();

  while (it != tree.end()) {
    const std::string &key = it->first;
    const std::string &data = it->second.data();

    if (key == "name") {
      name = data;
    } else if (key == "isLiving") {
      isLiving = (bool)std::stoi(data);
    } else if (key == "isInCombat") {
      isInCombat = (bool)std::stoi(data);
    } else if (key == "level") {
      level = std::stoi(data);
    } else if (key == "experience") {
      experience = std::stoi(data);
    } else if (key == "health") {
      health = std::stoi(data);
    } else if (key == "maxHealth") {
      maxHealth = std::stoi(data);
    } else if (key == "Equipment") {
      equipment.fromXML(*it);
    } else if (key == "Inventory") {
      inventory.fromXML(*it);
    } else if (key == "Stats") {
      stats.fromXML(*it);
    }
    it++;
  }


}
