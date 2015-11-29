#ifndef ITEM_HEALING_WAND_H
#define ITEM_HEALING_WAND_H
#include "Item.h"

class HealingWand : public Item
{
public:
  HealingWand(): Item("Healing Wand", Stats{ 0, 0, 7 }) {

    setDamage(0);
    setHeal(10);
  }
  virtual ~HealingWand() {

  }
protected:
private:
};

#endif // ITEM_HEALING_WAND_H
