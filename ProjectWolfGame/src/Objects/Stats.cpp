#include <iostream>
#include <iomanip>
#include "Objects/Stats.h"

Stats::Stats(int stamina, int strength, int intellect) {
  this->stamina = stamina;
  this->strength = strength;
  this->intellect = intellect;
}

void Stats::save()
{
  startSave("Stats");
  SAVE(stamina);
  SAVE(strength);
  SAVE(intellect);
  endSave();
}

void Stats::load()
{
  startLoad("Stats");
  LOAD(stamina);
  LOAD(strength);
  LOAD(intellect);
  endLoad();
}

void Stats::showStats() const {
  using namespace std;
  int fieldWidth = 9; // Length of "Intellect"
  cout << std::left << std::setw(fieldWidth) <<  "Stamina" << ": " << stamina << endl;
  cout << std::setw(fieldWidth) << "Strength" << ": " << strength << endl;
  cout << std::setw(fieldWidth) << "Intellect" << ": " << intellect << endl;
}

Stats operator+(Stats stats1, Stats stats2) {
  int stam, strength, intellect;
  stam = stats1.getStamina() + stats2.getStamina();
  strength = stats1.getStrength() + stats2.getStrength();
  intellect = stats1.getIntellect() + stats2.getIntellect();

  return Stats{stam, strength, intellect};
}

bool operator==(const Stats& l, const Stats& r) {
  bool areEqual = true;
  areEqual = areEqual && (l.getStamina() == r.getStamina());
  areEqual = areEqual && (l.getStrength() == r.getStrength());
  areEqual = areEqual && (l.getIntellect() == r.getIntellect());
  return areEqual;
}
