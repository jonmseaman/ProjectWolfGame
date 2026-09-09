import std;
#include "Entity/Stats.h"

namespace Engine {
namespace Entity {

Stats::Stats(int newStamina, int newStrength, int newIntellect)
  : stamina(newStamina)
  , strength(newStrength)
  , intellect(newIntellect) {}

void Stats::save() {
  startSave("Stats");
  SAVE(stamina);
  SAVE(strength);
  SAVE(intellect);
  endSave();
}

void Stats::load() {
  startLoad("Stats");
  LOAD(stamina);
  LOAD(strength);
  LOAD(intellect);
  endLoad();
}

void Stats::showStats() const {
  using namespace std;
  int fieldWidth = 9; // Length of "Intellect"
  cout << std::left << std::setw(fieldWidth) << "Stamina" << ": " << stamina << endl;
  cout << std::setw(fieldWidth) << "Strength" << ": " << strength << endl;
  cout << std::setw(fieldWidth) << "Intellect" << ": " << intellect << endl;
}

Stats Stats::operator+(const Stats& r) const {
  return Stats{ getStamina()   + r.getStamina(),
                getStrength()  + r.getStrength(),
                getIntellect() + r.getIntellect() };
}

bool Stats::operator==(const Stats& r) const {
  return getStamina() == r.getStamina()
    && getStrength() == r.getStrength()
    && getIntellect() == r.getIntellect();
}

}
}
