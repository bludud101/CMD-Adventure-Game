#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Tools.h"
#include <string>
#include <vector>

using std::string; using std::vector;

class Attributes
{
public:
	Attributes()
		:gold(0), durability(0), food(0), health(0), defense(0), offense(0), luck(0) {}
	Attributes(vector<int> attributes)
		:gold(attributes[0]), durability(attributes[1]), food(attributes[2]), health(attributes[3]), defense(attributes[4]), offense(attributes[5]), luck(attributes[6]) {}

	//Attributes getAttributes() { return attributes; };
	int getAttribute(string);
	void setAttribute(string, int);
	int getBaseId() { return base_id; };
	// gold_value, durability, food_value, health_amount, defense_amount, offense_amount, luck_amount = 0;
protected:
	int gold, durability, food, health, defense, offense, luck;
	int base_id = Tools::getUniqueId();
};
#endif