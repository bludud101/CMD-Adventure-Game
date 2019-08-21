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
	void UILoop(Humanoid&, Room&);
	static int returnRoom(vector<Room>);
	static int getUserResponse();
	static void drawChildRooms(vector<Room>);
	static Room getDestination(Room);
	void getChildren(Humanoid&, Room&);
	bool invNeeded(Room&);
	static void drawItems(vector<Item>, bool, bool);
	static void drawInventoryMenu();
	bool backAllowed(Room&);
	static int returnItemId(vector<Item>, string, bool);
	static bool playerInventory(Humanoid&, bool);
	static void displayStats(Humanoid&, bool);
	string returnAsLower(string);
	static int battleUI(Humanoid&, Humanoid&);
	static void promptUser();
private:
};
#endif
