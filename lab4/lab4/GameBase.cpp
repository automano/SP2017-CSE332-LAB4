// GameBase.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Propuse: Define public methods for base class

#include "stdafx.h"
#include "GameBase.h"

#include "common.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"

/*
 * Define prompt() method for NineAlmonds Game
 # Adapted from lab2
 */
int GameBase::prompt(unsigned int &x, unsigned int &y){
	cout << "Enter coordinates <x,y> or type <quit> to quit this game." << endl;
	int output;
	string coordinates;
	LowerCase(coordinates);
	while (cin >> coordinates) {
		if (!coordinates.compare("quit"))  // user type <quit>
		{
			output = PLAYER_QUIT;
			break;
		}
		else // user type <x,y>
		{
			for (unsigned int i = 0; i <= coordinates.size(); i++)
			{
				if (coordinates[i] == ',')
				{
					coordinates[i] = ' ';
				}
			}
			stringstream ss;
			ss << coordinates;
			if (ss >> x >> y) 
			{
				if ((0 <= int(x) && int(x) < horizontal_dimension) && (0 <= int(y) && int(y) < vertical_dimension))  //check the input move is on the inner nine squares of the board
				{
					output = SUCCESS;
					break;
				}
			}
		}
		// other invalid user input
		cout << "Invalid user input." << endl;
		cout << "Enter coordinates <x,y> or type <quit> to quit this game." << endl;
	}
	return output;
}

/*
 * Define prompt() method for MagicSquare Game
 * oveload in Class MagicSquareGame
 */
int GameBase::prompt(unsigned int &x) {
	return SUCCESS;
}

/*
 * Define play() method for Base class
 * Takes no parameters, prints the game board (using the ostream operator described above) and then repeatedly calls the turn() method and then the done() and stalemate() methods until either: 
 * (1) the done() method returns true in which case the program should print out a message indicating how many turns it took to complete the game successfully and then return a success code (with value 0) 
 * (2) the stalemate() method returns true in which case the program should print out a message indicating how many turns were played and saying that no valid moves remain and then return a unique non-zero failure code
 * (3) the user quits, in which case the program should print out a message indicating how many turns were played and saying that the user quit and then return a different unique non-zero failure code.
 */
int GameBase::play() {
	game_turns_count = 0; // set game turns to 0
	int method_turn_return;
	this->print(); // print the init game board
	while (!this->done() && !this->stalemate()) {// repeatedly calls the turn() method and then the done() and stalemate() methods
		method_turn_return = this->turn();
		if (method_turn_return == PLAYER_QUIT) { // user quits
			cout << "Player quit game!" << endl;
			cout << "Total turns: " << game_turns_count << "." << endl;
			return PLAYER_QUIT;
		}
		else if (method_turn_return == SUCCESS) {
			game_turns_count++;
		}
	}
	if (this->done()) // done() method returns true
	{
		cout << "Congratulations! You win!" << endl;
		cout << "Total turns: " << game_turns_count << "." << endl;
		return SUCCESS;
	}
	else // stalemate() method returns true
	{
		cout << "Sorry! No more valid moves!" << endl;
		cout << "Total turns: " << game_turns_count << "." << endl;
		return STALEMATE;
	}
}

/*
 * Add a static method to the base class that takes an integer and an array of pointers to char 
 * (the same types as are given to argc and argv in your program's main function signature) and 
 * returns a pointer to an object of your base class. The method should check that exactly one 
 * argument has been passed to the program (in addition to the program's name), and if so that 
 * the string in argv[1] is "NineAlmonds". If so, the method should use the new operator to 
 * dynamically default construct an object of your derived Nine Almonds game class, and return 
 * the address of that object; otherwise, the method should return a singlular pointer (i.e., 
 * a pointer whose value is 0), indicating that no object was constructed.
 */
GameBase* GameBase::objectAddressPtr(int argc, char *argv[]) {
	GameBase *objectAddressPtr;
	if (argc == ARGUMENT_0) //two arguments - default case
	{
		if (!strcmp(argv[GAME_NAME], "NineAlmonds"))
		{ // user want to play NineAlmondsGame
			objectAddressPtr = new NineAlmondsGame;
			return objectAddressPtr;
		}
		/*
		 * Update the static method of the base class that parses argc and argv so that if the string in argv[1] is "MagicSquare" 
		 * it should dynamically default construct an object of your derived Magic Square game class, and return the address of that object.
		 */
		else if (!strcmp(argv[GAME_NAME], "MagicSquare"))
		{ // user want to play MagicSquareGame
			objectAddressPtr = new MagicSquareGame;
			return objectAddressPtr;
		}
		else
		{
			objectAddressPtr = nullptr;
			return objectAddressPtr;
		}
	}

	// Extra Credit
	// # set game board size
	else if ((argc == ARGUMENT_1) && !strcmp(argv[GAME_NAME], "MagicSquare")) {
		if (is_numeric(argv[BOARD_SIZE]))
		{ 
			objectAddressPtr = new MagicSquareGame(atoi(argv[BOARD_SIZE]));
			return objectAddressPtr;
		}
		else
		{
			objectAddressPtr = nullptr;
			return objectAddressPtr;
		}
		
	}
	//* set game board size and minimum start value of the available pieces
	else if ((argc == ARGUMENT_2) && !strcmp(argv[GAME_NAME], "MagicSquare")) {
		if (is_numeric(argv[BOARD_SIZE]) && is_numeric(argv[LOWEST_VALUE_PIECE]))
		{
			objectAddressPtr = new MagicSquareGame(atoi(argv[BOARD_SIZE]), atoi(argv[LOWEST_VALUE_PIECE]));
			return objectAddressPtr;
		}
		else
		{
			objectAddressPtr = nullptr;
			return objectAddressPtr;
		}
		
	}
	else {
		objectAddressPtr = nullptr;
		return objectAddressPtr;
	}
}