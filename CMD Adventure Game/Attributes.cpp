#include <iostream>
#include "Attributes.h"

using std::cout;

int Attributes::getAttribute(string attribute)
{
	vector<string> atribute_name = { "gold", "durability", "food", "health", "defense", "offense", "luck"};
	for (unsigned int i = 0; i < atribute_name.size(); ++i)
	{
		if (attribute == atribute_name[i])
		{
			switch (i)
			{
				case 0:
					return gold;
				case 1:
					return durability;
				case 2:
					return food;
				case 3:
					return health;
				case 4:
					return defense;
				case 5:
					return offense;
				case 6:
					return luck;
			}
		}
	}
	cout << "Attribute not found: " << attribute;
	return -1;
}

void Attributes::setAttribute(string attribute, int value)
{
	vector<string> atribute_name = { "gold", "durability", "food", "health", "defense", "offense", "luck" };
	bool found_attribute = false;
	for (unsigned int i = 0; i < atribute_name.size(); ++i)
	{
		if (attribute == atribute_name[i])
		{
			switch(i)
			{
				case 0:
					gold = value;
					break;
				case 1:
					durability = value;
					break;
				case 2:
					food = value;
					break;
				case 3:
					health = value;
					break;
				case 4:
					defense = value;
					break;
				case 5:
					offense = value;
					break;
				case 6:
					luck = value;
					break;
			}
			found_attribute = true;
		}
	}
	if (!found_attribute) cout << "Attribute not found: " << attribute;
}