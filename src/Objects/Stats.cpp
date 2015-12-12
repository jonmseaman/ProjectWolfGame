#include <iostream>
#include "File.h"
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

pairType Stats::toTree() {
	treeType tree;

	tree.push_back(XML_VAR_PAIR(stamina));
	tree.push_back(XML_VAR_PAIR(strength));
	tree.push_back(XML_VAR_PAIR(intellect));

	return pairType("stats", tree);
}

void Stats::fromTree(const pairType& p) {
	const treeType& tree = p.second;
	auto it = p.second.begin();
	while (it != p.second.end()) {
		const std::string &key = it->first;
		const std::string &data = it->second.data();

		if (key == STRING(stamina)) {
			stamina = std::stoi(data);
		} else if (key == STRING(strength)) {
			strength = std::stoi(data);
		} else if (key == STRING(intellect)) {
			intellect = std::stoi(data);
		}
		it++;
	}

}
