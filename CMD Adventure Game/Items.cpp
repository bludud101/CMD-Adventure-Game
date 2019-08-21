#include "Items.h"

vector<vector<vector<string>>> item_text
{
	{
		{	
			"Sand Bag", 
			"A well worn cloth bag that is full of sand. Might have been stolen.",
			"You eat some of the cloth, but the sand spills out onto your face.",
			"You balance the sand bag on your head in hopes it provides protection. Your neck hurts.",
			"You look down to grab a gold piece and the sand bag falls off your head.", "You leave the sand bag on the curb.",
			"broke"
		},
		{
			"Cheesy Pop", "A semi-frozen, phallic cheese glob on a stick. May have a hair on the top.",
			"The cheesy pop and hair does not go down very well, but it does fill you up some.",
			"You now wield the cheesy pop as though it is an actual weapon.",
			"You put away the mighty cheesy pop.",
			"You give the cheesy pop to a street dog. The street dog walks about 5 feet and spits it out.",
			"broke"
		},
		{	"Cheese",
			"A hunk of undisclosed cheese product. Smells like brie.",
			"You find out it was definitely not brie. Or cheese.",
			"The cheese does not at first appear to be a worthwhile piece of appeal,\nuntil you realize it can be molded around your feet. Stylish.",
			"Each foot is jiggled until that shit flies off.",
			"You take the cheese and toss it to the ground. That'll show it.", "broke"
		},
		{
			"Hockey Stick",
			"A duct-tape mended stick of wood.\nShaped to hit pucks, but may work well for braining some fool.",
			"You nibble on the end and get some splinters in your mouth.\nAn appetite was worked up.",
			"The hockey stick is grasped tightly.", "All good things much come to an end; such as using sports equipment as a weapon.",
			"You toss the old friend into a nearby well. Goodbye, sweet prince.",
			"broke"
		},
		{
			"Karate Belt", "A yellow karate belt. Smells like salmon. Tastes similar.",
			"You suck on the end of it a little, it leaves a fishy taste in your mouth.",
			"The yellow belt fits nicely around your waist. A bystander points and laughs.",
			"You take off the belt and notice it stained your pants an unsightly yellow hue.",
			"You toss the belt to a child. He looks pleased to have it.", "broke"
		},
		{
			"Calico Cat",
			"A male calico cat. Seems to have respiratory issues.",
			"That didn't go very well.",
			"The calico makes great shoes.",
			"You peel the calico off.",
			"You grab the calico cat to let it go, but end up needing three stiches and a shovel."
		}
	}
};

vector<vector<int>> item_attributes
{
	//gold_value, durability, food_value, health_amount, defense_amount, offense_amount, luck_amount
	{2, 1, -2, -2, 1, 0, 2},
	{3, 1, 20, 20, 0, 1, 0},
	{5, 3, 2, 2, 2, 0, 3},
	{12, 37, -1, -2, 2, 9, 1},
	{3, 30, 0, 0, 3, 4, -1},
	{2, 9, 3, -4, 7, -1, 2}
};

vector<vector<Item>> item_list
{
	//helmet 0, chest 1, gloves 2, weapon 3, ring 4, belt 5, pants 6, shoes 7, unspecific 8.
	{
		Item(item_attributes[0], item_text[0][0], 0),
		Item(item_attributes[1], item_text[0][1], 3),
		Item(item_attributes[2], item_text[0][2], 7),
		Item(item_attributes[3], item_text[0][3], 3),
		Item(item_attributes[4], item_text[0][4], 5),
		Item(item_attributes[5], item_text[0][5], 7)
	}
};

Item Items::returnItem(string item_name)
{
	unsigned int i = 0;
	while (i < item_list.size())
	{
		unsigned int j = 0;
		while (j < item_list[i].size())
		{
			if (item_list[i][j].getItemText()[0] == item_name) 
				return item_list[i][j];
			++j;
		}
		++i;
	}
}

vector<vector<Item>> Items::returnItems()
{
	return item_list;
}

Item Items::itemFromID(int id)
{
	unsigned int i = 0;
	while (i < item_list.size())
	{
		unsigned int j = 0;
		while (j < item_list[i].size())
		{
			if (item_list[i][j].getBaseId() == id) return item_list[i][j];
			++j;
		}
		++i;
	}
}

Item Items::returnRandomItem(int item_level)
{
	return item_list[item_level][Tools::randNum(0, item_list[item_level].size())];
}




