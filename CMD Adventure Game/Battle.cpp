#include <iostream>
#include "Battle.h"
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Items.h"
#include "Events.h"
#include "UI.h"
#include "Enemies.h"
#include "Player.h"

using std::cout; using std::cin; using std::string; using std::vector;
// If old_room is a child of new_room, player went back, use backward battle odds. 
// Otherwise assume player entered a child room and use forward battle odds. 
// Return -1 for no battle, 1 for player surprised, 2 for player unsurprised.
int Battle::foundBattle(Room& new_room, Room& old_room) 
{
	int i = 0;
	int rand_option = 0;
	if (new_room.nonBattleRoom() || old_room.nonBattleRoom())
		return -1;
	while (i < 1)
	{
		rand_option = Tools::getOneInThree();
		//Get random of three options (No battle, surprised battle, and unsurprised battle).
		//If true, use back battle odds by adding 3 to get proper elements. 
		if (old_room.getParent() == new_room.getName())
			rand_option += 3;
		//Takes selected option, which has odds (out of a hundred) and compares them to a random number from 0 to 100.
		//If selected option is the bigger number, continues. Otherwise tries again with a potentially different option. 
		if (Tools::getOutOfHundred(new_room.getFightChances()[rand_option])) ++i;
	}
	cout << new_room.getMovementText()[rand_option][0] << "\n";
	// 0 and 3 are both successful moves into another room without confrontation. 
	if (rand_option == 0 || rand_option == 3) 
		return -1;
	//if surprised. (1 or 4)
	else if (rand_option == 1 || rand_option == 4)
		return 1;
	//finally, assume unsurprised (2 or 5).
	return 2;
};

void Battle::newBattle(bool player_first, Humanoid& player, Humanoid& enemy)
{
	bool first_attack = false, successful_run = false;

	if (player_first)
	{
		first_attack = true;
		cout << player.getHumanoidName() << " got the jump on the " << enemy.getHumanoidName() << "!\n";
		//playerAttack(player, enemy, successful_run);
	} 
	else attackOpponent(enemy, player);
	if (first_attack && enemy.getAttribute("health") > 0 && !successful_run) attackOpponent(enemy, player);

	while (enemy.getAttribute("health") > 0 && player.getAttribute("health") > 0 && !successful_run)
	{
		//playerAttack(player, enemy, successful_run);
		if (enemy.getAttribute("health") > 0 && !successful_run) attackOpponent(enemy, player);
	}

	if (enemy.getAttribute("health") < 1)
	{
		cout << "\nThe " << enemy.getHumanoidName() << " has died!\n";
		if (Tools::randNum(0, 1) > 0)
		{
			Item dropped_item = enemy.getItems()[Tools::randNum(0, enemy.getItems().size() - 1)];
			player.addItem(dropped_item);
			cout << "It seems the " << enemy.getHumanoidName() << " has dropped their " << dropped_item.getItemText()[0] <<"! Finders keepers.\n";
		}
	}
	else if (player.getAttribute("health") < 1)
		cout << "\n" << player.getHumanoidName() << " has fallen!\n";
	else 
		cout << "\n" << player.getHumanoidName() << " high tailed it outta there!\n";
	UI::promptUser();
}

void Battle::attackOpponent(Humanoid& attacker, Humanoid& receiver)
{
	const int successful_hit = 59;
	if (luckAttempt(attacker, receiver, successful_hit))
	{
		int hit_power = attacker.getAttribute("offense") - receiver.getAttribute("defense");
		if (hit_power < 0) hit_power = Tools::randNum(1,3);
		receiver.setAttribute("health", receiver.getAttribute("health") - hit_power);
		if (attacker.typeEquipped(3))
			cout << "\nWHAM!\n" << attacker.getHumanoidName() << " hit " << receiver.getHumanoidName() << " with a " << attacker.getEquippedOfType(3).getItemText()[0] << "\n";
		else
			cout << "\nSMACK!\n" << attacker.getHumanoidName() << " bitch slapped " << receiver.getHumanoidName() << "!\n";
		receiver.decrimentRandEquipped();
		attacker.decrimentEquippedWeapon();
		if (hit_power > 0) cout << "\nAttack did " << hit_power << " damage!\n";
		else cout << "\nAttack did no damage!\n";
	}
	else 
	{
		cout << attacker.getHumanoidName() << " Missed " << receiver.getHumanoidName() << " by a mile!\n";
		cout << "\n" << receiver.getHumanoidName() << " stands tall!\n";
	}
	cout << "\nHealth for " << receiver.getHumanoidName() << " is " << receiver.getAttribute("health") << "!\n";
	UI::promptUser();
}

bool Battle::luckAttempt(Humanoid& attemper, Humanoid& defender, int required_num)
{
	int luck_pool = attemper.getAttribute("luck") - defender.getAttribute("luck");
	int rand_num = Tools::randNum(0, 100 + luck_pool);
	if (rand_num > required_num) return true;
	return false;

}

bool Battle::playerRunAttempt(Humanoid& player, Humanoid& enemy)
{
	if (luckAttempt(player, enemy, 80))
		return true;

	cout << "\nThe " << enemy.getHumanoidName() << " spits on you and keeps you contained!\n";
	UI::promptUser();
	return false;
}