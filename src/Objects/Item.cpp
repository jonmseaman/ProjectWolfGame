#include <iostream>
#include "Creature.h"
#include "File.h"
#include "Item.h"

Item::Item():
	name("Item")
	, description("Description")
	, stats{} {
}

Item::Item(std::string name, Stats stats) : Item(name, "", stats) {

}

Item::Item(std::string name, std::string description, Stats stats) {
	this->name = name;
	this->description = description;
	this->stats = stats;
	baseDamage = 1; // TODO: Add way to set these two variables
	baseHeal = 0;
}

Item::~Item() {
}

void Item::use(const Creature &usedBy, Creature &usedOn) {
	int amountToDamage = baseDamage;
	int amountToHeal = baseHeal;

	// Derive stats from creature using item + this items stats
	Stats derivedStats = stats + usedBy.stats;
	// Add extra damage and healing from stats
	amountToDamage += 2*derivedStats.getStrength();
	amountToHeal += 2*derivedStats.getIntellect();
	// Do damage and healing
	if (amountToDamage > 0) {
		usedOn.onDamage(amountToDamage);
	}
	if (amountToHeal > 0) {
		usedOn.onHeal(amountToHeal);
	}
}

void Item::showInfo() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Description: " << description << std::endl;
  stats.showStats();
}

boost::property_tree::ptree::value_type Item::toXML() {
	using namespace boost::property_tree;
	ptree tree;

	tree.push_back(XML_VAR_SPAIR(name));
	tree.push_back(XML_VAR_SPAIR(description));
	tree.push_back(XML_VAR_PAIR(baseDamage));
	tree.push_back(XML_VAR_PAIR(baseHeal));
	tree.push_back(stats.toXML());

	return ptree::value_type("Item", tree);
}
