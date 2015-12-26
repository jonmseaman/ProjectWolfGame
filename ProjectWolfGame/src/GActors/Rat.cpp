#include "Rat.h"
#include <iostream>
Rat::Rat() {
  setName("Rat");
  setHealth(2);
  setMaxHealth(2);
  stats = Stats{2, 1, 1};
}

Rat::~Rat() {
}
