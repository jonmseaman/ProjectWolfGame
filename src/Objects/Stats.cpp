#include <iostream>
#include "Stats.h"

Stats::Stats(int stamina, int strength, int intellect) {
	this->stamina = stamina;
	this->strength = strength;
	this->intellect = intellect;
}

void Stats::showStats() {
	using namespace std;
	cout << "Stamina: " << stamina << endl;
	cout << "Strength: " << strength << endl;
	cout << "Intellect: " << intellect << endl;
}

Stats operator+(Stats stats1, Stats stats2) {
	int stam, strength, intellect;
	stam = stats1.getStamina() + stats2.getStamina();
	strength = stats1.getStrength() + stats2.getStrength();
	intellect = stats1.getIntellect() + stats2.getIntellect();

	return Stats{stam, strength, intellect};
}
