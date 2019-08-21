#include <iostream>
#include <vector>
#include "Room.h"

using std::cout; using std::cin; using std::string; using std::vector;

string Room::getName()
{
	return room_name;
}

string Room::getParent()
{
	return parent_room;
}

void Room::setParent(string new_parent)
{
	parent_room = new_parent;
}


string Room::getDestinationName()
{
	return destination;
}

void Room::setDestination(string new_destination)
{
	destination = new_destination;
}
