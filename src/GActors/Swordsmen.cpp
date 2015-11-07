#include "Swordsmen.h"
#include "Item_BasicSword.h"
Swordsmen::Swordsmen(): Actor()
{
  setName("Swordsmen");
  setHealth(50);
  setMaxHealth(50);
  setStrength(15);

  inventory = Inventory{ "Backpack", 10 };
  inventory.addNewItem(new Item_BasicSword);
  //ctor
}

Swordsmen::~Swordsmen()
{
  //dtor
}
