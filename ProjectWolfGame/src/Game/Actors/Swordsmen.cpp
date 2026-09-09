#include <Creation/Creatable.h>

import std;
import Engine;

using namespace Engine::Entity;

class Swordsmen : public Actor {
public:
  CREATABLE_ACTOR(Swordsmen)
  Swordsmen() {
    setName("Swordsmen");
    setMaxHealth(50);
    stats = Stats{ 5, 3, 0 };

    inventory = Inventory{ "Backpack", 10 };
    inventory.addItem(Creation::Create::newItem("BasicSword"));
  }
};

CREATABLE_REGISTRATION(Swordsmen);
