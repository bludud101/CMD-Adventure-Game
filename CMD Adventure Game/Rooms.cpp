#include <iostream>
#include <vector>
#include "Room.h"
#include "Rooms.h"

using std::cout; using std::cin; using std::string; using std::vector;

vector<vector<int>> room_fight_chances
{
	{0, 50, 50, 80, 30, 30},
	{ 75,40,40,80,20,20 },
	{ 90,10,10,90,10,10 },
	{ 60,57,20,50,58,20 },
	{ 80,10,10,100,10,10 }
};

vector<vector<vector<string>>> movement_text
{
	{
		{"enter_successfull", "enter_successfull"},
		{"enter_fight_surprised","enter_fight_surprised"},
		{"enter_fight_unsurprised","enter_fight_unsurprised"},
		{"Attempting to become a safety consciousness individual,\nyou wait for Deadlift Donnie and his crew to walk out,\nbefore successfully following them outside.\n", "Having had previous misfortune attempting to leave the bar,\nthis time you run out with flailing arms."},
		{"Unsurpringly, as you walk out of the shady bar, you get blindsighted by a ", "BACKOUT_FIGHT_SURPRISED"},
		{"Backout_fight_unsurprised","Backout_fight_unsurprised"}
	},
	{
		{"enter_successfull", "enter_successfull"},
		{"enter_fight_surprised","enter_fight_surprised"},
		{"enter_fight_unsurprised","enter_fight_unsurprised"},
		{"You almost slip on a banana as you're walking out.", "You hold the door for a grandma before walking out. Nice!"},
		{"BACKOUT_FIGHT_SURPRISED","BACKOUT_FIGHT_SURPRISED"},
		{"Backout_fight_unsurprised","Backout_fight_unsurprised"}
	},
	{
		{"enter_successfull", "enter_successfull"},
		{"enter_fight_surprised","enter_fight_surprised"},
		{"enter_fight_unsurprised","enter_fight_unsurprised"},
		{"You peek out of the stall and notice some scary people.\nAfter waiting for what seemed to be three hours, they leave, and you come out.", "Attempting to open the stall door is unsucessful, but you ram it a few times and it pops open."},
		{"BACKOUT_FIGHT_SURPRISED","BACKOUT_FIGHT_SURPRISED"},
		{"backout_fight_unsurprised","backout_fight_unsurprised"}
	},
	{
		{"enter_successfull", "enter_successfull"},
		{"enter_fight_surprised","enter_fight_surprised"},
		{"enter_fight_unsurprised","enter_fight_unsurprised"},
		{"backout_successful","backout_successful"},
		{"BACKOUT_FIGHT_SURPRISED","BACKOUT_FIGHT_SURPRISED"},
		{"Backout_fight_unsurprised","Backout_fight_unsurprised"}
	},
	{
		{"enter_successfull", "enter_successfull"},
		{"enter_fight_surprised","enter_fight_surprised"},
		{"enter_fight_unsurprised","enter_fight_unsurprised"},
		{"backout_successful","backout_successful"},
		{"BACKOUT_FIGHT_SURPRISED", "BACKOUT_FIGHT_SURPRISED"},
		{"Backout_fight_unsurprised","Backout_fight_unsurprised"}
	},
};

vector<Room> rooms_list
{
	Room("Main", "none", "Main", room_fight_chances[0], movement_text[0]),
	Room("Shady Bar", "Main", "Shady Bar", room_fight_chances[0], movement_text[0]),
	Room("Unisex Bathroom", "Shady Bar", "Unisex Bathroom", room_fight_chances[1], movement_text[1]),
	Room("Dangerous Stall", "Men's Bathroom", "Dangerous Stall", room_fight_chances[2], movement_text[2]),
	Room("Wonky Stall", "Men's Bathroom", "Wonky Stall", room_fight_chances[3], movement_text[3]),
	Room("Ol' Stall", "Men's Bathroom", "Ol' Stall", room_fight_chances[4], movement_text[4])
};

vector<Room> Rooms::getRooms() { return rooms_list; };
vector<vector<vector<string>>> Rooms::getMovementText() { return movement_text; };
vector<vector<int>> Rooms::getRoomFightChances() { return room_fight_chances; };

Room Rooms::getRoomFromId(int id)
{
	unsigned int i = 0;

	while (i < rooms_list.size())
	{
		if (rooms_list[i].getId() == id) return rooms_list[i];
		++i;
	}

	cout << "COULD NOT FIND ROOM!";
	return rooms_list[-1];
}