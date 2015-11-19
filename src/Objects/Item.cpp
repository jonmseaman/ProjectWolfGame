#include "Item.h"
#include "Creature.h"
#include <iostream>

Item::Item():
	name("Item")
	, description("Description") {
	//TODO: Add stats
}

Item::Item(std::string name, Stats stats) {
	Item(name, "", stats);
}

Item::Item(std::string name, std::string description, Stats stats):
  name(name)
  , description(description)
  , stats(stats)
{
	baseDamage = 1;
	baseHeal = 0;
}

Item::~Item() {
}

void Item::use(const Creature &usedBy, Creature &usedOn) {
	// TODO: Implement this
}

void Item::showInfo() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Description: " << description << std::endl;
  stats.showStats();
}
