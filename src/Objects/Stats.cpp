#include <iostream>
#include "Stats.h"

Stats::Stats() {
	stamina = 0;
	strength = 0;
	intellect = 0;
}

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
