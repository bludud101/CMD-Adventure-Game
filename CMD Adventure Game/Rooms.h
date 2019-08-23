#ifndef ROOMS_H
#define ROOMS_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "Item.h"

using std::cout; using std::cin; using std::string; using std::vector;

//enter_success, enter_fight_surprised, enter_fight unsurprised, backout_sucess, backout_surprised, backout_unsurprised

class Rooms
{
	public:
		static vector<Room> getRooms();
		static Room getRoomFromId(int);
		static Room getRoomFromName(string);
		static vector<vector<vector<string>>> getMovementText();
		static vector<vector<int>> getRoomFightChances();	
};

#endif
