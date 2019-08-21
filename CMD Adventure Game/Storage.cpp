#include <fstream>
#include <filesystem>
#include "Storage.h"
#include "Rooms.h"
#include "Items.h"

using std::ifstream; using std::ofstream;

void Storage::saveGame(Humanoid& player_data, int current_room)
{
	ofstream save;
	save.open("save.dat", ofstream::out | ofstream::trunc);
	save << current_room << " ";
	save << player_data.getHumanoidName()
		<< " !finished! "
		<< player_data.getAttribute("gold")
		<< " " << player_data.getAttribute("health")
		<< " " << player_data.getAttribute("food")
		<< " " << player_data.getAttribute("luck") << " ";
	unsigned int i = 0;
	save << player_data.getItems().size();

	while (i < player_data.getItems().size())
	{
		save << " " << player_data.getItems()[i].getBaseId() << " ";
		save << player_data.getItems()[i].getAttribute("durability") << " ";
		save << player_data.getItems()[i].getEquipped();
		++i;
	}
	save.close();
}

bool Storage::saveExists() 
{ 
	if (std::filesystem::exists("save.dat")) return true;
	else return false;
}

void Storage::loadGame(Humanoid& player_data, Room& player_room)
{
	player_data.unequipAll();
	player_data.reset();
	ifstream load;
	load.open("save.dat");
	int id;
	load >> id;
	player_room = Rooms::getRoomFromId(id);
	int i = 0;
	string player_name, temp_string;
	load >> temp_string;

	while (i < 1)
	{
		if (temp_string != "!finished!")
		{
			player_name += temp_string;
			load >> temp_string;
			if (temp_string != "!finished!") player_name += " ";
		}
		else ++i;
	}

	player_data.setHumanoidName(player_name);
	int temp_float;
	load >> temp_float;
	player_data.setAttribute("gold", temp_float);
	load >> temp_float;
	player_data.setAttribute("health", temp_float);
	load >> temp_float;
	player_data.setAttribute("food", temp_float);
	load >> temp_float;
	player_data.setAttribute("luck", temp_float);
	int items_amount;
	load >> items_amount;
	int j = 0;
	while (j < items_amount)
	{
		int item_index;
		load >> item_index;
		player_data.addItem(Items::itemFromID(item_index));
		int durability;
		load >> durability;
		player_data.getItems()[j].setAttribute("durability", durability);
		bool equipped;
		load >> equipped;
		if (equipped) player_data.equipItem(player_data.getItems()[j].getInventoryId(), false);
		++j;
	}
	load.close();
}

