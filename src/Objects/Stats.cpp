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
