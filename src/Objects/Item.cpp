#include <iostream>
#include "Creature.h"
#include "File.h"
#include "Item.h"

Item::Item():
  name("Item")
  , description("Description")
  , stats{} {
    setID(0);
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

void Item::showInfo() {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Description: " << description << std::endl;
  stats.showStats();
}

pairType Item::toTree() {
  using namespace boost::property_tree;
  ptree tree;

  tree.push_back(XML_VAR_SPAIR(name));
  tree.push_back(XML_VAR_SPAIR(description));
  tree.push_back(XML_VAR_PAIR(baseDamage));
  tree.push_back(XML_VAR_PAIR(baseHeal));
  tree.push_back(stats.toTree());

  return ptree::value_type("Item", tree);
}

void Item::fromTree(const pairType& item) {
  const treeType &tree = item.second;
  auto it = tree.begin();

  while (it != tree.end()) {
    const std::string &key = it->first;
    const std::string &data = it->second.data();

    if (key == STRING(name)) {
      name = data;
    } else if (key == STRING(description)) {
      description = data;
    } else if (key == STRING(baseDamage)) {
      baseDamage = std::stoi(data);
    } else if (key == STRING(baseHeal)) {
      baseHeal = std::stoi(data);
    } else if (key == "Stats") {
      stats.fromTree(*it);
    }

    it++;
  }
}
