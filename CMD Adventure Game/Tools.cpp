#include "Tools.h"
#include <stdlib.h>

static int currentId = 0;

int Tools::getUniqueId()
{
	return ++currentId;
}

int Tools::randNum(int min_num, int max_num)
{
	int i = 0, temp_rand = 0;
	while (i < 1)
	{
		temp_rand = rand() % (max_num + 1);
		if (temp_rand <= max_num && temp_rand >= min_num) ++i;
	}
	return temp_rand;
}

int Tools::getOneInThree()
{
	return rand() % 3;
}

bool Tools::getOutOfHundred(int chance)
{
	if ((rand() % 100 + 1) > chance) return false;
	else return true;
}