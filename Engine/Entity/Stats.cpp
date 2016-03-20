#include <iostream>
#include <iomanip>
#include "Entity/Stats.h"

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

Stats Stats::operator+(const Stats& r) const {
  int stam, strength, intellect;
  stam = getStamina() + r.getStamina();
  strength = getStrength() + r.getStrength();
  intellect = getIntellect() + r.getIntellect();

  return Stats{stam, strength, intellect};
}

bool Stats::operator==(const Stats& r) const {
    return getStamina() == r.getStamina()
        && getStrength() == r.getStrength()
        && getIntellect() == r.getIntellect();
}
