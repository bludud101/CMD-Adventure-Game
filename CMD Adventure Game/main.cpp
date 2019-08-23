#include <iostream>
#include <vector>
#include "Room.h"
#include "UI.h"
#include <ctime>
#include <stdlib.h>
#include "Humanoid.h"
#include "Rooms.h"
#include "Items.h"
#include "Events.h"
#include "Battle.h"
#include "Enemies.h"

using std::cout; using std::cin; using std::vector; using std::string;

int main()
{
	srand(1);
	Room current_room = Rooms::getRooms()[0], fight_room = Rooms::getRooms()[0];
	Humanoid player("Slong"), enemy;
	player.giveRandItems(2,10,0);
	bool in_battle = false, player_turn = false;
	vector<Room> current_children = UI::getChildren(player, current_room, in_battle);
	player.setRandStats(1);
	int i = 0, player_interactions = 0;
	Room new_room = Rooms::getRooms()[0];
	while (i < 1)
	{
		if (!in_battle)
		{
			//cout << current_children[0].getDestinationName();
			int battle_check = Battle::foundBattle(new_room, current_room);
			if (battle_check != -1)
			{
				in_battle = true;
				enemy = Enemies::makeEnemy(Tools::randNum(1, 3));
				if (battle_check != 1)
				{
					player_turn = true;
					cout << player.getHumanoidName() << " got the jump on the " << enemy.getHumanoidName() << "!\n";
				}
				else
				{
					player_turn = false;
					cout << player.getHumanoidName() << " heard a bumrush behind them.. OHSHITITSA "
						<< enemy.getHumanoidName() << "!!!\n";
				}
			}
			cout << "current room:" << current_room.getName();
			current_children = UI::getChildren(player, current_room, in_battle);
			new_room = current_children[UI::returnRoom(current_children)];
			current_room = Events::eventList(player, enemy, current_room, new_room);
		}
		if (in_battle)
		{
			if (player_turn && new_room.getName() == "Fight")
			{
				Battle::attackOpponent(player, enemy);
				player_turn = false;
			}
			if (player_interactions != player.getItemInteractions() || player_turn != true)
			{
				Battle::attackOpponent(enemy, player);
				player_turn = true;
			}

			if (player.getAttribute("health") <= 0 || enemy.getAttribute("health") <= 0)
			{
				in_battle = false;
				cout << player.getAttribute("health") << enemy.getAttribute("health");
				new_room = current_room;
			}
			if (!in_battle)
			{
				cout << "Battle over.\n";
			}
			else
			{
				player_interactions = player.getItemInteractions();
				current_children = UI::getChildren(player, fight_room, in_battle);
				new_room = current_children[UI::returnRoom(current_children)];
				fight_room = Events::eventList(player, enemy, fight_room, new_room);
			}
		}
	}

}