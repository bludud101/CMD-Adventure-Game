#include <iostream>
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Items.h"
#include "Events.h"
#include "Rooms.h"
#include "Battle.h"
#include "Storage.h"
#include "UI.h"
#include <ctime>
#include <stdlib.h>

using std::cout; using std::cin; using std::string; using std::vector;

static bool used_box = false;

Room Events::eventList(Humanoid& player, Humanoid& enemy, Room& current_room, Room& temp_room)
{
	if (temp_room.getName() == "One-way Box")
	{
		if (used_box)
		{
			cout << "The box seems to be locked..\n";
			UI::promptUser();
			return current_room;
		}
		cout << player.getHumanoidName() << " walks into the small metal box and shuts the door behind them."
			<< "\nThere's a small amount of light coming in the box through a little pinky-sized hole.\n"
			<< "In the middle of the box is an old stool and a noose dangling over top of it.\n";
		vector<Room> death_box
		{
			Room("Bang on door", "One-way Box", "Bang on door", true),
			Room("Slump down", "One-way Box", "Slump down", true),
			Room("Sit for a while", "One-way Box", "Sit for a while", true),
			Room("Stand up", "One-way Box", "Stand up", true),
			Room("Stand on chair", "One-way Box", "stand on Chair", true),
			Room("Position noose", "One-way Box", "position Noose", true),
			Room("Kick out chair", "One-way Box", "Kick out chair", true)
		};
		for (int i = 0; i < death_box.size(); ++i)
		{
			UI::returnRoom(vector<Room> {death_box[i]});
			UI::promptUser();
			if (i == 0)
				cout << "\n" << player.getHumanoidName()
				<< " yells and bangs on the door for what seems to be days.\nNothing happens.\n";
			if (i == 1)
				cout << player.getHumanoidName() << " slumps down against the side of the box.\n";
		}
		used_box = true;
		return Events::playerDeath(player, 0);
	}
	if (temp_room.getName() == "Inventory")
	{
		if (enemy.getAttribute("health") > 0)
			UI::playerInventory(player, true);
		else UI::playerInventory(player, false);
		return current_room;
	}
	if (temp_room.getName() == "Fight" || temp_room.getName() == "Run")
		return current_room;
	if (temp_room.getName() == "My Stats")
	{
		UI::displayStats(player, true);
		return current_room;
	}
	if (temp_room.getName() == "Enemy Stats")
	{
		UI::displayStats(enemy, true);
		return current_room;
	}
	if (temp_room.getName() == "Save")
	{
		Storage::saveGame(player, current_room.getId());
		cout << "\nSAVED\n";
		UI::promptUser();
		return current_room;
	}
	if (temp_room.getName() == "Load")
	{
		Storage::loadGame(player, current_room);
		cout << "\nLOADED\n";
		UI::promptUser();
		return current_room;
	}
	return UI::getDestination(temp_room);
}

Room Events::playerDeath(Humanoid& player, int chosen_death)
{
	switch(chosen_death)
	{
		case 0:
		{
			player = Humanoid("Fred");
			player.giveRandItems(2, 10, 0);
			cout << "\n" << player.getHumanoidName() << " Awakens in a pile of mud in the Courtyard.\n";
			return Rooms::getRoomFromName("Courtyard");
		}

	}
}


