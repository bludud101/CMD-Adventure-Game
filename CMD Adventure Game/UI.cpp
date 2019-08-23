#include <iostream>
#include <stdlib.h> 
#include <string>
#include <vector>
#include <limits>
#include "Room.h"
#include "Rooms.h"
#include "UI.h"
#include "Item.h"
#include "Humanoid.h"
#include "Items.h"
#include "Events.h"
#include "Storage.h"
#include "Attributes.h"
#include "Enemies.h"
#include "Battle.h"

using std::cout; using std::cin; 

vector<Room> UI::getChildren(Humanoid& player, Room& current_room, bool in_battle)
{
	vector<Room> child_rooms;
	unsigned int i = 0;
	while (i < Rooms::getRooms().size())
	{
		if ((current_room.getName() == Rooms::getRooms()[i].getParent() 
			 || Rooms::getRooms()[i].getParent() == "NONBATTLE") && !in_battle 
			 || Rooms::getRooms()[i].getParent() == "ALL" 
			 || (in_battle && Rooms::getRooms()[i].getParent() == "BATTLE"))
		{
			//cout << "Added " << rooms_list[i].room_name << " to " << room_name << std::endl;
			child_rooms.push_back(Rooms::getRooms()[i]);
		}
		++i;
	}
	if (UI::backAllowed(current_room) && !in_battle)
		child_rooms.push_back(Rooms::getRoomFromName(current_room.getParent()));
	return child_rooms;
}

bool UI::backAllowed(Room& current_room)
{
	if (!(current_room.getParent() == "NONE") && !current_room.getOneWay()) return true;
	return false;
}

int UI::returnRoom(vector<Room> child_rooms)
{
	unsigned int user_response = 0;
	do
	{
		drawChildRooms(child_rooms);
		user_response = getUserResponse() - 1;
	} while (user_response < 0 || user_response > child_rooms.size() - 1);
	//cout << "Returning:" << user_response;
	return user_response;
}

void UI::drawChildRooms(vector<Room> child_rooms)
{
	unsigned int i = 0;
	bool beginning_space = false;
	while (i < child_rooms.size())
	{
		if (!beginning_space)
		{
			cout << "\n";
			beginning_space = true;
		}
		cout << (i + 1) << ". " << child_rooms[i].getName() << "\n";
		++i;
	}
	//if (backAllowed()) cout << ++i << ". Back\n";
}

int UI::getUserResponse()
{
	int temp;
	cout << "\n:";
	if (!(cin >> temp))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return temp;
}

Room UI::getDestination(Room room)
{
	for (unsigned int i = 0; i < Rooms::getRooms().size(); ++i)
	{
		//cout << room.getDestinationName();
		if (room.getDestinationName() == Rooms::getRooms()[i].getName()) return Rooms::getRooms()[i];
	}
	cout << "COULD NOT FIND DESTINATION:" << room.getDestinationName();

	return room;
}

bool UI::invNeeded(Room& current_room)
{
	if (current_room.getName() == "Inventory") return true;
	return false;
}

bool UI::playerInventory(Humanoid& player, bool in_battle)
{	
	int i = 0;
	unsigned int id = 0;
	if (player.getItems().size() == 0)
	{
		cout << "My my, " << player.getHumanoidName() << ". You ain't got shit!\n";
		UI::getUserResponse();
		return false;
	}
	while (i < 1)
	{
		bool display_prompt = true;
		drawItems(player.getItems(), false, false);
		drawInventoryMenu();
		const vector<string> prompts = {"Check:", "Eat:"};
		switch(getUserResponse())
		{
			case 1:
			{
				id = returnItemId(player.getItems(), "Check:", true);
				if (id != -1) 
					player.checkItem(id);
				break;
			}
			case 2:
			{
				id = returnItemId(player.getItems(), "Eat:", true);
				if (id != -1)
				{
					player.eatItem(id);
					if (in_battle)
						i = 2;
				}
				break;
			}
			case 3:
			{
				id = returnItemId(player.getAllUnequipped(), "Equip:", true);
				if (id != -1)
				{
					player.equipItem(id, true);
					if (in_battle)
						i = 2;
				}
				break;
			}
			case 4:
			{
				id = returnItemId(player.getAllEquipped(), "Unequip:", true);
				if (id != -1)
				{
					player.unequipItem(id, true);
					if (in_battle)
						i = 2;
				}
				break;
			}
			case 5:
			{
				id = returnItemId(player.getItems(), "Delete:", true);
					if (id != -1) player.removeItem(id);
					{
						if (in_battle)
							i = 2;
					}
				break;
			}
			case 6:
			{
				displayStats(player, false);
				break;
			}
			case 7:
			{
				++i;
				break;
			}
		
		}
		if (id == -1) display_prompt = false;
		if (player.getItems().size() == 0)
		{
			cout << "That was the last item you had. Enter any number to go back.\n";
			++i;
			getUserResponse();
		}
		else if ((i == 0 || i == 2) && display_prompt)
			promptUser();
	}
	if (i == 2) return true;
	return false;
}

void UI::drawItems(vector<Item> player_items, bool numbered, bool include_back)
{
	unsigned int i = 0;
	bool beginning_space = false;
	while (i < player_items.size())
	{
		if (!beginning_space)
		{
			if (!numbered) cout << "\nItems:\n\n";
			else cout << "\n\n";
			beginning_space = true;
		}
		if (numbered) cout << (i + 1) << ". ";
		cout << player_items[i].getItemText()[0] << "\n";
		++i;
	}
	if (include_back) cout << ++i << ". Back\n";
}

void UI::drawInventoryMenu()
{
	cout << "\nOptions:\n\n1. Check Item\n2. Eat Item\n3. Equip Item\n4. Unequip Item\n5. Delete Item\n6. My Stats\n7. Back\n";
}

int UI::returnItemId(vector<Item> items, string prompt, bool include_back)
{
	int max_input = items.size() - 1;
	if (include_back) max_input = items.size();
	int user_response = 0;
	do
	{
		cout << "\n" << prompt;
		drawItems(items, true, include_back);
		user_response = getUserResponse() - 1;
	} while (user_response < 0 || user_response > max_input);
	//cout << "Returning:" << user_response;
	if (user_response == items.size())
		return -1;
	return items[user_response].getInventoryId();
}

void UI::displayStats(Humanoid& player, bool prompt)
{
	cout << 
		"Current Stats:\n\nGold: " << player.getAttribute("gold") << 
		"\nHealth: " << player.getAttribute("health") << 
		"\nSatiety: " << player.getAttribute("food") <<
		"\nDefense: " << player.getAttribute("defense") <<
		"\nOffense: " << player.getAttribute("offense") <<
		"\nLuck: " << player.getAttribute("luck") << "\n";
	if(prompt)
		promptUser();
}

string UI::returnAsLower(string s)
{
	for (char &c: s)
	{
		c = tolower(c);
	}
	return s;
}

void UI::promptUser()
{
	cout << "\n(Enter any number)";
	getUserResponse();
}