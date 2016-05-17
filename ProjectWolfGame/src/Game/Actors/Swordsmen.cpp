#include <Creation/Creatable.h>
#include <Creation/Create.h>
#include <Entity/Actor.h>

using namespace Engine::Entity;

class Swordsmen : public Actor {
public:
  CREATABLE_ACTOR(Swordsmen)
    Swordsmen() {
    setName("Swordsmen");
    setMaxHealth(50);
    stats = Stats{ 5, 3, 0 };

    inventory = Inventory{ "Backpack", 10 };
    inventory.addNewItem(Creation::Create::newItem("BasicSword"));
    auto strb = "Hello";
  }
};

CREATABLE_REGISTRATION(Swordsmen);