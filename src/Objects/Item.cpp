#include "Item.h"
#include "Creature.h"
#include <iostream>

Item::Item():
	name("Item")
	, description("Description") {
	//TODO: Add stats
}

Item::Item(std::string name, std::string description, Stats stats):
  name(name)
  , description(description)
  , stats(stats)
{
}

Item::~Item() {
}

void Item::useOn(Creature* creature) {
  assert(creature != nullptr);
  //TODO: Implement this
	// Changes stats of creature.
  // Update the creatures stats
  // creature->stats.addStats(stats) ?
  // Do damage or healing
}

void Item::showInfo() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Description: " << description << std::endl;
  stats.showStats();
}
