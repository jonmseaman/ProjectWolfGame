#include <Entity/Item.h>
#include <Creation/Creatable.h>

using namespace Engine::Entity;

class HealingWand : public Item {
public:
  CREATABLE_ITEM(HealingWand)
    HealingWand() : Item("Healing Wand", Stats{ 0, 0, 7 }) {
    setDamage(0);
    setHeal(10);
  }
  virtual ~HealingWand() {
  }
protected:
private:
};

CREATABLE_REGISTRATION(HealingWand);