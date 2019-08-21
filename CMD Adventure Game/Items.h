#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include "Attributes.h"

using std::cout; using std::cin; using std::string; using std::vector;

class Items
{
public:
	static Item returnItem(string);
	static vector<vector<Item>> returnItems();
	static Item itemFromID(int);
	static Item returnRandomItem(int);
};
#endif

