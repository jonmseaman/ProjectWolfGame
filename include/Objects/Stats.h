#ifndef STATS_H
#define STATS_H
class Creature;
class Stats
{
  friend Creature;
public:
  Stats();
  Stats(int stamina = 0, int strength = 0, int intellect = 0);
//  virtual ~Stats();

  int getStamina() { return stamina; }
  int getStrength() { return strength; }
  int getIntellect() { return intellect; }

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

#endif /* end of include guard: STATS_H */
