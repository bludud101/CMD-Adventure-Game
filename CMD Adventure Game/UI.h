#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Humanoid.h"

class UI
{
public:
	UI() = default;
	static int returnRoom(vector<Room>);
	static int getUserResponse();
	static void drawChildRooms(vector<Room>);
	static Room getDestination(Room);
	static vector<Room> getChildren(Humanoid&, Room&, bool);
	static bool invNeeded(Room&);
	static void drawItems(vector<Item>, bool, bool);
	static void drawInventoryMenu();
	static bool backAllowed(Room&);
	static int returnItemId(vector<Item>, string, bool);
	static bool playerInventory(Humanoid&, bool);
	static void displayStats(Humanoid&, bool);
	static string returnAsLower(string);
	static void promptUser();
private:
};
#endif
