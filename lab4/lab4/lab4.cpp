// lab4.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: refactoring common data structures and behaviors into a base class, and
//          specializing how the common parts are used in different derived classes.

#include "stdafx.h"
#include "common.h"
#include "GameBase.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"


int main(int argc, char*argv[])
{
	GameBase *myGame = 0;
	myGame = myGame->objectAddressPtr(argc, argv);

	if (myGame != nullptr)
	{
		return myGame->play();
	}
	else
	{
		char * program_name = argv[PROGRAM_NAME];
		char * second_argument = "<game_name>";
		return UsageMessage(program_name, second_argument);// call usage message 
	}
}