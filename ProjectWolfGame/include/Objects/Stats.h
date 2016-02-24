#ifndef STATS_H
#define STATS_H
#include "Savable.h"
class Creature;

class Stats : public File::Savable {
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



private:
  // Base stats
  int stamina; // Boosts max health points
  int strength; // boosts physical damage
  int intellect; // Boosts spell damage
};

Stats operator+(Stats stats1, Stats stats2);
bool operator==(const Stats& l, const Stats& r);

#endif /* end of include guard: STATS_H */
