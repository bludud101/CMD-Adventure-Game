#include <iostream>
#include <vector>
#include "Room.h"
#include "UI.h"
#include <ctime>
#include <stdlib.h>
#include "Humanoid.h"
#include "Rooms.h"
#include "Items.h"

using std::cout; using std::cin; using std::vector; using std::string;

int main()
{
	srand(time(nullptr));
	Room current_room = Rooms::getRooms()[0];
	Humanoid player("Slong");
	player.addItem(Items::returnItem("Cheese"));
	player.addItem(Items::returnItem("Karate Belt"));
	player.addItem(Items::returnItem("Cheese"));
	player.addItem(Items::returnItem("Hockey Stick"));
	player.addItem(Items::returnItem("Cheesy Pop"));
	player.addItem(Items::returnItem("Calico Cat"));
	player.addItem(Items::returnItem("Sand Bag"));
	player.setRandStats(1);
	UI game;
	game.UILoop(player, current_room);
}