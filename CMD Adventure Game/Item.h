#ifndef ITEM_H
#define ITEM_H

#include "Attributes.h"

class Item: public Attributes
{
	public:
		Item() = default;
		Item(vector<string> item_text_) :item_text(item_text_) {}
		Item(vector<int> attributes, vector<string> item_text_, int equip_type_)
			:Attributes(attributes), item_text(item_text_), equip_type(equip_type_){}
		vector<string> getItemText() const { return item_text; }
		void setItemText(string new_text, int text_index) { item_text[text_index] = new_text; };
		int getEquipType() const { return equip_type; }
		bool getEquipped() const { return equipped; }
		void setEquipped(bool new_equip) { equipped = new_equip; };
		void setInventoryId(int id) { inventory_id = id; };
		int getInventoryId() { return inventory_id; };
	private:
		vector<string> item_text;
		int equip_type = 0, inventory_id = 0;
		bool equipped = false;
};

#endif

