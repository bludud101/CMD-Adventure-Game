#include <iostream>
#include "Humanoid.h"
#include "Items.h"
#include <string>

using std::string; using std::cout;

void Humanoid::eatItem(int id)
{
	cout << "\n" << getItem(id).getItemText()[2] << "\n";
	food += getItem(id).getAttribute("food");
	if (food >= max_hunger)
	{
		food = max_hunger;
		cout << "\nYou're now fully satiated!\n";
	}
	else cout << "\nSatiety is now " << food << ".\n";

	health += getItem(id).getAttribute("health");
	if (health >= max_health)
	{
		health = max_health;
		cout << "You're now fully healed!\n";
	}
	else cout << "Health is now " << health << ".\n";

	if (getItem(id).getAttribute("durability") == 1)
	{
		cout << "\nItem was fully eaten!\n";
		if (getItem(id).getEquipped()) unequipItem(id, false);
		removeItem(id);
	}
	else
	{
		decrimentAndCheck(id);
		cout << getItem(id).getAttribute("durability") << " uses remaining.";
	}
}

void Humanoid::decrimentAndCheck(int id)
{
	getItem(id).setAttribute("durability", (getItem(id).getAttribute("durability") - 1));
	if (getItem(id).getAttribute("durability") == 0)
	{
		cout << getItem(id).getItemText()[6];
		unapplyStats(id);
		if (getItem(id).getEquipped()) unequipItem(id, false);
		removeItem(id);
	}
}

Item& Humanoid::getItem(int id)
{
	unsigned int i = 0;

	while (i < inventory.size())
	{
		if (inventory[i].getInventoryId() == id) 
			return inventory[i];
		++i;
	}
	Item item({ "none" });
	return item;
}

void Humanoid::addItem(Item item)
{
	inventory.push_back(item);
	inventory.back().setInventoryId(Tools::getUniqueId());
}

void Humanoid::addItems(vector<Item> items) 
{ 
	unsigned int i = 0;

	while (i < items.size())
	{
		addItem(items[i]);
		++i;
	}
}

void Humanoid::removeItem(int id)
{
	unsigned int i = 0;

	while (i < inventory.size())
	{
		if (inventory[i].getInventoryId() == id)
			inventory.erase(inventory.begin() + i);
		++i;
	}
}

void Humanoid::equipItem(int id, bool display_message)
{
	if (getItem(id).getEquipped())
	{
		if (display_message) cout << "Sorry, this item is already equipped!\n";
	}
	else
	{
		unsigned int i = 0;
		while (i < inventory.size())
		{
			if (inventory[i].getEquipType() == getItem(id).getEquipType() && inventory[i].getEquipped())
			{
				unequipItem(inventory[i].getInventoryId(), display_message);
				break;
			}
			++i;
		}
		applyStats(id);
		getItem(id).setEquipped(true);
		if (display_message) cout << getItem(id).getItemText()[3] << "\n";
	}
}
void Humanoid::unequipItem(int id, bool display_message)
{
	if (getItem(id).getEquipped())
	{
		unapplyStats(id);
		getItem(id).setEquipped(false);
		if (display_message) cout << getItem(id).getItemText()[4] << "\n";
	}
	else cout << "This item was not equipped!";
}

Item Humanoid::getEquippedOfType(int equip_type)
{
	unsigned int i = 0;
	while (i < getAllEquipped().size())
	{
		if (getAllEquipped()[i].getEquipType() == equip_type) return getAllEquipped()[i];
		++i;
	}
	Item item({ "none" });
	return item;
}

bool Humanoid::typeEquipped(int equip_type)
{
	if (getEquippedOfType(equip_type).getItemText()[0] != "none") return true;
	return false;
}

void Humanoid::equipAll()
{
	unsigned int i = 0;
	while (i < inventory.size())
	{
		if (!inventory[i].getEquipped())
		{
			equipItem(inventory[i].getInventoryId(), false);
		}
		++i;
	}
}

vector<Item> Humanoid::getAllEquipped()
{
	unsigned int i = 0;
	vector<Item> equipped_items;

	while (i < inventory.size())
	{
		if (inventory[i].getEquipped())
			equipped_items.push_back(inventory[i]);
		++i;
	}
	return equipped_items;
}

void Humanoid::unequipAll()
{
	unsigned int i = 0;
	while (i < inventory.size())
	{
		if (inventory[i].getEquipped())
		{
			unequipItem(inventory[i].getInventoryId(), false);
		}
		++i;
	}
}

vector<Item> Humanoid::getAllUnequipped()
{
	unsigned int i = 0;
	vector<Item> unequipped_items;

	while (i < inventory.size())
	{
		if (!inventory[i].getEquipped())
			unequipped_items.push_back(inventory[i]);
		++i;
	}
	return unequipped_items;
}

void Humanoid::applyStats(int id)
{
	if (!getItem(id).getEquipped())
	{
		defense += getItem(id).getAttribute("defense");
		offense += getItem(id).getAttribute("offense");
		luck += getItem(id).getAttribute("luck");
	}
	else cout << "Cannot apply stats to equipped item!\n";
}

void Humanoid::unapplyStats(int id)
{
	if (getItem(id).getEquipped())
	{
		defense -= getItem(id).getAttribute("defense");
		offense -= getItem(id).getAttribute("offense");
		luck -= getItem(id).getAttribute("luck");
	}
	else cout << "Cannot unapply stats from uneqipped item!\n";
}

void Humanoid::setRandStats(int level)
{
	setAttribute("health", Tools::randNum(10 * level, 10 * (level + 1)));
	setAttribute("food", Tools::randNum(10 * level, 10 * (level + 1)));
	setAttribute("luck", Tools::randNum(3 * level, 5 * (level + 1)));
	setAttribute("offense", Tools::randNum(4 * level, 9 * (level + 1)));
	setAttribute("defense", Tools::randNum(3 * level, 7 * (level + 1)));
}

void Humanoid::giveRandItems(int min_items, int max_items, int item_level)
{
	for (int i = 0; i < Tools::randNum(min_items, max_items); ++i)
	{
		(inventory.push_back(Items::returnRandomItem(item_level)));
	}
}

void Humanoid::decrimentRandEquipped()
{
	unsigned int i = 0;
	while (i < 1)
	{
		if (inventory.size() > 0)
		{
			if (inventory.size() == 1 && inventory[0].getEquipType() == 3) break;
			if (Tools::randNum(0, 100) < 20 && inventory[i].getEquipped() && inventory[i].getEquipType() != 3) 
				decrimentAndCheck(inventory[i].getInventoryId());
		}
		++i;
	}
}

void Humanoid::decrimentEquippedWeapon()
{
	unsigned int i = 0;
	while (i < inventory.size())
	{
		if (inventory[i].getEquipped() && inventory[i].getEquipType() == 3)
		{
			decrimentAndCheck(inventory[i].getInventoryId());
			cout << "\nDecrimented Weapon\n";
			break;
		}
		++i;
	}
}
