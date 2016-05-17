#ifndef STATS_H
#define STATS_H
#include "Savable.h"
#include <Engine.h>

namespace Engine {
namespace Entity {
class Creature;

class ENGINE_API Stats : public File::Savable {
public:
  Stats(int stamina = 0, int strength = 0, int intellect = 0);
  SAVABLE;

  // Get and set methods
  int getStamina() const { return stamina; }
  int getStrength() const { return strength; }
  int getIntellect() const { return intellect; }
  void setStamina(int stam) { stamina = stam; }
  void setStrength(int strength) { this->strength = strength; }
  void setIntellect(int intellect) { this->intellect = intellect; }

  /**
   * Shows a list of stats and their values
   * 3 lines, Stamina on one, strength, the intellect
   */
  void showStats() const;

  Stats operator+(const Stats& r) const;
  bool operator==(const Stats& r) const;

private:
  // Base stats
  int stamina; // Boosts max health points
  int strength; // boosts physical damage
  int intellect; // Boosts spell damage
};
}
}

#endif /* end of include guard: STATS_H */
