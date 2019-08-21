#ifndef STORAGE_H
#define STORAGE_H

#include "Humanoid.h"

class Storage
{
public:
	static void saveGame(Humanoid&, int);
	static bool saveExists();
	static void loadGame(Humanoid&, Room&);
};

#endif