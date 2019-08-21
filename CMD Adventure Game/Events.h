#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Items.h"
#include "Humanoid.h"
#include <ctime>
#include <stdlib.h>

using std::cout; using std::cin; using std::string; using std::vector;

class Events
{
	Room *current_room;
public:
	Events() = default;
	Events(Room& ui_current_room)
		:current_room{ &ui_current_room } {}
	static void eventList(Humanoid&, Room&, Room&);
};

#endif
