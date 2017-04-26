// lab4.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: 1. Interacting with a single instance of the game currently in play.
//			2. Allowing games to be saved and resumed.
//			3. Implementing a multi - player game with alternating turns.
//			4. Documenting your design decisions regarding copy control.

#include "stdafx.h"
#include "common.h"
#include "GameBase.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"


int main(int argc, char*argv[])
{
	try 
	{
		GameBase::objectAddressPtr(argc, argv); // passes argc and argv into the static method
		/*Also modify your main function so that whenever it needs to interact with the game object created by that static method, it calls the static instance() method to obtain a shared smart pointer to the object, through which to invoke methods on the object (but also catching and appropriately handling any exceptions that were thrown, as necessary). As before, the main function should invoke the object's play() method, and use the result returned by the play() method as the program's return value.*/
		return GameBase::instance()->play();
	}
	catch (bad_alloc)
	{ // adapted from http://www.cplusplus.com/reference/new/bad_alloc/
		cout << "bad_alloc caught" << endl;
		return BAD_ALLOC;
	}
	// catches an exception if one was thrown, and returns a separate non-zero value for each distinct failure case.
	catch (ProgramStatus error)
	{
		//Exceptions involving badly formed command lines also should cause a call to the usage function as in previous labs. 
		if (error == WRONG_GAME_NAME)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: Wrong game name input!");
			return error;
		}
		else if (error == INVALID_BOARD_SIZE)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: game board size should be numeric!");
			return error;
		}
		else if (error == INVALID_LOWEST_VALUE_PIECE)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: game board size should be numeric!");
			return error;
		}
		else if (error == WRONG_NUMBER_ARGUMENTS)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: wrong number of arguments (too many or too few)!");
			return error;
		}
		else if (error == NOT_NULL_PTR)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: Static GameBase pointer exists!");
			return error;
		}
		else if (error == OPEN_FILE_FAILED)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: Can not open file!");
			return error;
		}
		else if (error == BAD_FORMAT_LINE)
		{
			UsageMessage(argv[PROGRAM_NAME], "Error: first line of the file is bad format!");
			return error;
		}
	}
}