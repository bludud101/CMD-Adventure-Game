#include <iostream>
#include "Enemies.h"
#include "Item.h"
#include "Items.h"

using std::cout;

vector<string> enemy_names{ "Dancing Toilet","Freedom Fighter","Chicken","Grannie","Sax Player","Chuck E Cheese","Robocop"};
/*
vector<vector<Item>> item_sets
{
	{ Items::returnItem("Sand bag"), Items::returnItem("Cheese"), Items::returnItem("Cheese") },
	{ Items::returnItem("Cheese"), Items::returnItem("Cheese"), Items::returnItem("Cheese") },
	{ Items::returnItem("Cheese"), Items::returnItem("Cheese"), Items::returnItem("Cheese") },
	{ Items::returnItem("Cheese"), Items::returnItem("Cheese"), Items::returnItem("Cheese") },
	{ Items::returnItem("Cheese"), Items::returnItem("Cheese"), Items::returnItem("Cheese") }
};
*/
Humanoid Enemies::makeEnemy(int difficulty)
{
	int rand_enemy = Tools::randNum(0, enemy_names.size());
	Humanoid enemy(enemy_names[rand_enemy]);
	enemy.setRandStats(Tools::randNum(1,4));
	enemy.addItem(Items::returnItem("Cheese"));
	//enemy.addItems(item_sets[rand_enemy]);
	enemy.equipAll();
	return enemy;
}

