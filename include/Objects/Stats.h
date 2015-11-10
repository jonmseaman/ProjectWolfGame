#ifndef STATS_H
#define STATS_H
class Creature;
class Stats
{
  friend Creature;
public:
//  Stats();
//  virtual ~Stats();

  int getStamina() { return stamina; }
  int getStrength() { return strength; }
  int getIntellect() { return intellect; }
  int getLevel() { return level; }
  int getExperience() { return experience; }

  int getHealth() { return health; }
  int getMaxHealth() { return maxHealth; }



private:
  // Base stats
  int stamina; // Boosts max health points
  int strength; // boosts physical damage
  int intellect; // Boosts spell damage
  int level; // Creatures level
  int experience; // Experience earned this level
  int requiredExperience; // Experience required to level up

  // Calculated stats
  int health;
  int maxHealth;

};

#endif /* end of include guard: STATS_H */
