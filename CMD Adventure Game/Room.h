#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "Tools.h"

using std::cout; using std::cin; using std::string; using std::vector;


class Room
{
public:
	Room() = default;
	Room(string room_name_, string parent_room_, string destination_, bool non_battle)
		:room_name(room_name_), parent_room(parent_room_), destination(destination_), non_battle_(non_battle) {}
	Room(string room_name_, string parent_room_, string destination_, vector<int> fight_chances_, vector<vector<string>> movement_text_)
		:room_name(room_name_), parent_room(parent_room_), destination(destination_), fight_chances(fight_chances_), movement_text(movement_text_){}
	Room(string room_name_, string parent_room_, string destination_, vector<int> fight_chances_, vector<vector<string>> movement_text_, bool one_way)
		:room_name(room_name_), parent_room(parent_room_), destination(destination_), fight_chances(fight_chances_), movement_text(movement_text_), one_way_(one_way) {}
	string getName();
	string getParent();
	vector<int> getFightChances() { return fight_chances; };
	vector<vector<string>> getMovementText() { return movement_text; };
	int getId() const { return id; }
	void setParent(string);
	string getDestinationName();
	void setDestination(string);
	bool getOneWay() const { return one_way_; }
	bool nonBattleRoom() const { return non_battle_; }
	private:
		vector<int> fight_chances;
		vector<vector<string>> movement_text;
		string room_name, parent_room, destination;
		int id = Tools::getUniqueId();
		bool one_way_ = false, non_battle_ = false;
};

#endif
