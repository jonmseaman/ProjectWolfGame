#ifndef STATS_H
#define STATS_H
#include "File.h"
class Creature;

class Stats {
public:
  Stats(int stamina = 0, int strength = 0, int intellect = 0);
  pairType toXML();
  void fromXML(const pairType& p);

  int getStamina() { return stamina; }
  int getStrength() { return strength; }
  int getIntellect() { return intellect; }
  void setStamina(int stam) { stamina = stam; }
  void setStrength(int strength) { this->strength = strength; }
  void setIntellect(int intellect) { this->intellect = intellect; }

  /**
   * Shows a list of stats and their values
   * 3 lines, Stamina on one, strength, the intellect
   */
  void showStats();

private:
  // Base stats
  int stamina; // Boosts max health points
  int strength; // boosts physical damage
  int intellect; // Boosts spell damage
};

Stats operator+(Stats stats1, Stats stats2);

#endif /* end of include guard: STATS_H */
