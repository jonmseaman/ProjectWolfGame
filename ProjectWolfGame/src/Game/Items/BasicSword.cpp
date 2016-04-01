#include <Creation/Creatable.h>
#include <Entity/Item.h>

using namespace Engine::Entity;

class BasicSword : public Item {
public:
  CREATABLE_ITEM(BasicSword)
  BasicSword() : Item("Sword", Stats{ 5,5,0 }) {}
};

CREATABLE_REGISTRATION(BasicSword);
