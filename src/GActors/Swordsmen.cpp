#include "Swordsmen.h"
#include "BasicSword.h"
Swordsmen::Swordsmen(): Actor() {
  setName("Swordsmen");
  setHealth(50);
  setMaxHealth(50);
  setStrength(15);

  inventory = Inventory{ "Backpack", 10 };
  inventory.addNewItem(new BasicSword);
  //ctor
}

Swordsmen::~Swordsmen() {
  //dtor
}
