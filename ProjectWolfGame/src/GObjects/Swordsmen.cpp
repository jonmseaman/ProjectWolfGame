#include "GObjects\Swordsmen.h"
#include "GObjects\BasicSword.h"

Swordsmen::Swordsmen(): Actor() {
  setName("Swordsmen");
  setMaxHealth(50);
  stats = Stats{ 5, 3, 0 };

  inventory = Inventory{ "Backpack", 10 };
  inventory.addNewItem(new BasicSword);
  //ctor
}

Swordsmen::~Swordsmen() {
  //dtor
}
