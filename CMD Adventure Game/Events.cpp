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

void Events::eventList(Humanoid& player, Room& current_room, Room& temp_room)
{
			if (temp_room.getName() == "Inventory")
			{
				UI::playerInventory(player, false);
				return;
			}
			if (temp_room.getName() == "My Stats")
			{
				UI::displayStats(player, true);
				return;
			}
			if (temp_room.getName() == "Save")
			{
				Storage::saveGame(player, current_room.getId());
				cout << "\nSAVED\n";
				UI::promptUser();
				return;
			}
			if (temp_room.getName() == "Load")
			{
				Storage::loadGame(player, current_room);
				cout << "\nLOADED\n";
				UI::promptUser();
				return;
			}
			if (temp_room.getName() == "Back")
			{
				Battle::potentialBattle(true, player, current_room);
				current_room = UI::getDestination(temp_room);
				return;
			}
			current_room = UI::getDestination(temp_room);
			Battle::potentialBattle(false, player, current_room);
}



