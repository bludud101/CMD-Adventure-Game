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

void Battle::potentialBattle(bool back, Humanoid& player, Room& current_room)
{
	int i = 0;
	int rand_option = 0;
	while (i < 1)
	{
		rand_option = Tools::getOneInThree();
		if (back) rand_option += 3;
		//cout << "Room ID:" << room_id << "Rand Option:" << rand_option << "/n";
		if (Tools::getOutOfHundred(current_room.getFightChances()[rand_option])) ++i;
	}
	cout << current_room.getMovementText()[rand_option][0] << "\n";
	// 0 and 3 are both successful moves into another room without confrontation. 
	if (rand_option == 1 || rand_option == 4) newBattle(false, player);
	else if (rand_option != 0 && rand_option != 3) newBattle(true, player);
};

void Battle::newBattle(bool player_first, Humanoid& player)
{
	Humanoid enemy = Enemies::makeEnemy(0);
	bool first_attack = false, successful_run = false;

	if (player_first)
	{
		first_attack = true;
		cout << player.getHumanoidName() << " got the jump on the " << enemy.getHumanoidName() << "!\n";
		playerAttack(player, enemy, successful_run);
	} 
	else attackOpponent(enemy, player);
	if (first_attack && enemy.getAttribute("health") > 0 && !successful_run) attackOpponent(enemy, player);

	while (enemy.getAttribute("health") > 0 && player.getAttribute("health") > 0 && !successful_run)
	{
		playerAttack(player, enemy, successful_run);
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

void Battle::playerAttack(Humanoid& player, Humanoid& enemy, bool& successful_run)
{
	int player_choice = UI::battleUI(player, enemy);
	if (player_choice == 0) attackOpponent(player, enemy);
	if (player_choice == 4)
	{
		if (luckAttempt(player, enemy, 80))
			successful_run = true;
		else 
		{
			cout << "\nThe " << enemy.getHumanoidName() << " spits on you and keeps you contained!\n";
			UI::promptUser();
		}
	}
}