#ifndef ITEM_H
#define ITEM_H
#include <Engine.h>
#include <string>
#include <Entity/Stats.h>
#include <Creation/Creatable.h>

namespace Engine {
namespace Entity {
class Creature;

/**
 * This is an item.
 */
class ENGINE_API Item : public File::Savable {
public:
  Item();
  Item(std::string name, std::string description, Stats stats);
  Item(std::string name, Stats stats);
  virtual ~Item();
  SAVABLE;
  CREATABLE_ITEM(Item)


    void showInfo() const;

  /**
   * Returns the name of the item.
   */
  std::string getName() const { return name; }
  /**
   * Returns the description of the item.
   */
  std::string getDescription() const { return description; }

  void setDescription(const std::string &description) { this->description = description; }

  int getDamage() const { return baseDamage; }
  int getHeal() const { return baseHeal; }
  void setDamage(int damage) { baseDamage = damage; }
  void setHeal(int heal) { baseHeal = heal; }

  virtual void use(const Creature &usedBy, Creature &usedOn);
  Stats stats;
  bool operator==(const Item& r);
protected:
  std::string name;
  std::string description;
  int baseDamage;
  int baseHeal;
};

}
}

#endif // ITEM_H
