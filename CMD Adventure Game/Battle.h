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
		static void potentialBattle(bool, Humanoid&, Room&);
		static void newBattle(bool, Humanoid&);
		static void attackOpponent(Humanoid&, Humanoid&);
		static bool luckAttempt(Humanoid&, Humanoid&, int);
		static void playerAttack(Humanoid&, Humanoid&, bool&);
	private:
};

#endif