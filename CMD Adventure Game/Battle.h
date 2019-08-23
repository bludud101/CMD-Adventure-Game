#ifndef BATTLE_H
#define BATTLE_H

#include "Room.h"
#include "Item.h"
#include "Items.h"
#include "Humanoid.h"

using std::cout; using std::cin; using std::string; using std::vector;

class Battle
{
	public:
		static int foundBattle(Room&, Room&);
		static void newBattle(bool, Humanoid&, Humanoid&);
		static void attackOpponent(Humanoid&, Humanoid&);
		static bool luckAttempt(Humanoid&, Humanoid&, int);
		static bool playerRunAttempt(Humanoid&, Humanoid&);
	private:
};

#endif