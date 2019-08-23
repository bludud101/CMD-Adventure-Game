
#ifndef HUMANOID_H
#define HUMANOID_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Attributes.h"
#include "Inventory.h"

class Humanoid: public Attributes
{
	public:
		Humanoid() = default;
		Humanoid(string name)
			:humanoid_name(name) {}
		Humanoid(vector<int> attributes, string name)
			:Attributes(attributes), humanoid_name(name) {}

		void eatItem(int);
		string getHumanoidName() { return humanoid_name; };
		void setHumanoidName(string new_name) { humanoid_name = new_name; };
		int returnMaxHealth() { return max_health;  };
		void setMaxHealth(int new_max) { max_health = new_max; };
		void decrimentAndCheck(int);
		void equipItem(int, bool);
		void unequipItem(int, bool);
		bool typeEquipped(int);
		Item getEquippedOfType(int);
		vector<Item> getAllEquipped();
		void equipAll();
		void unequipAll();
		vector<Item> getAllUnequipped();
		void applyStats(int);
		void unapplyStats(int);
		vector<Item> getItems() { return inventory; };
		Item& getItem(int);
		void addItem(Item item);
		void addItems(vector<Item> items);
		void removeItem(int);
		void reset() { inventory.clear(); };
		void checkItem(int id) { cout << "\n" << getItem(id).getItemText()[1] << "\n"; };
		void setRandStats(int);
		void giveRandItems(int, int, int);
		void decrimentRandEquipped();
		void decrimentEquippedWeapon();
		int getItemInteractions() const { return item_interactions; }
	private:
		vector<Item> inventory;
		string humanoid_name;
		int max_health = 50, max_hunger = 30, item_interactions = 0;
};
#endif