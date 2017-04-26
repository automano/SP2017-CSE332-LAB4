// GameBase.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Propuse: Define public methods for base class

#include "stdafx.h"
#include "GameBase.h"

#include "common.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"

// Init the game name
string GameBase::gameName = "";

/*
 * In the source file for your game base class, initialize that static member variable with nullptr.
 */
shared_ptr<GameBase> GameBase::ptr = nullptr;

/*
 * Define prompt() method for NineAlmonds Game
 * Adapted from lab2
 * Modify your Magic Square and Nine Almonds games so that if the player chooses to quit, the game asks them whether or not they want to save the current game. If the player answers yes, the game should use an ofstream to open up a file that has the same name as the game, output a line with the name of the game as the first line of the file, then output the current state of the game (in a manner that the program can read back in to resume the game - see next), and then close the file before the program ends. How you choose to format the files is up to you, but you should please document your aproach in your ReadMe.txt file.
If the player answers no, the game should again open up a file with the same name as the game, but then output something specific that cannot be confused with a valid game state (say, a single blank line, or something like "NO DATA") to indicate that no state was saved for that game, and then close the file before the program ends.
 */
int GameBase::prompt(unsigned int &x, unsigned int &y){
	cout << "Enter coordinates <x,y> or type <quit> to quit this game." << endl;
	int output;
	string coordinates;
	LowerCase(coordinates);
	while (cin >> coordinates) {
		if (!coordinates.compare("quit"))  // user type <quit>
		{
			// save game prompt
			cout << "Would you like to save the current game ? (YyNn)" << endl;
			string in = "";
			cin >> in;
			LowerCase(in);
			while (in != "y" && in != "n") {
				cout << "Invalid input, try y or n!" << endl;
				cin >> in;
				LowerCase(in);
			}
			if (in == "y") { // user want to save the current game 
				// Adapted from http://www.cplusplus.com/reference/fstream/ofstream/is_open/
				// Whenever a game is completed it should also overwrite the game's file to indicate that the next time the game is played it should start at the beginning.
				ofstream ofs;
				ofs.open(gameName + ".txt");
				if (ofs.is_open())
				{
					// write data for Ninealmonds Game
					ofs << gameName << endl; // game name 
					ofs << game_turns_count << endl; // how many turns
					ofs << longest_piece_length << endl; // store the longest piece length
					for (int y = 0; y < vertical_dimension; y++)
					{
						for (int x = 0; x < horizontal_dimension; x++)
						{
							ofs << game_piece[y*horizontal_dimension + x] << endl;
						}
					}

					cout << "Game Saved!" << endl;
					ofs.close();
				}
				else
				{
					throw OPEN_FILE_FAILED;
				}
			}
			if (in == "n") { // user don't want to save the current game 
				// Adapted from http://www.cplusplus.com/reference/fstream/ofstream/is_open/
				// Whenever a game is completed it should also overwrite the game's file to indicate that the next time the game is played it should start at the beginning.
				ofstream ofs;
				ofs.open(gameName + ".txt");
				if (ofs.is_open())
				{
					ofs << "NO DATA" << endl; // no state was saved for that game - new game 
					ofs.close();
				}
				else
				{
					throw OPEN_FILE_FAILED;
				}
				// end 
			}

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
		// Adapted from http://www.cplusplus.com/reference/fstream/ofstream/is_open/
		// Whenever a game is completed it should also overwrite the game's file to indicate that the next time the game is played it should start at the beginning.
		ofstream ofs;
		ofs.open(gameName + ".txt");
		if (ofs.is_open())
		{
			ofs << "NO DATA" << endl; // no state was saved for that game - new game 
			ofs.close();
		}
		else
		{
			throw OPEN_FILE_FAILED;
		}
		// end 
		return SUCCESS;
	}
	else // stalemate() method returns true
	{
		cout << "Sorry! No more valid moves!" << endl;
		cout << "Total turns: " << game_turns_count << "." << endl;
		// Adapted from http://www.cplusplus.com/reference/fstream/ofstream/is_open/
		// Whenever a game is stalemate it should also overwrite the game's file to indicate that the next time the game is played it should start at the beginning.
		ofstream ofs;
		ofs.open(gameName + ".txt");
		if (ofs.is_open())
		{
			ofs << "NO DATA" << endl; // no state was saved for that game - new game 
			ofs.close();
		}
		else
		{
			throw OPEN_FILE_FAILED;
		}
		// end
		return STALEMATE;
	}
}

/*
 * Add a public static instance() method to your game base class that returns a shared smart 
 * pointer to the game base class (for example, if your game base class was of type GameBase 
 * then the method's return type would be of type shared_ptr<GameBase>). When the method is 
 * called, if the value of the static member variable that you added to the class in the previous 
 * step is not equal to nullptr the method should return it; otherwise if the value of the static 
 * member variable is equal to nullptr the method should throw an exception.
 */
shared_ptr<GameBase> GameBase::instance()
{
	if (ptr != nullptr) // not equal to nullptr
		return ptr;
	else				// member variable is equal to nullptr
		throw NULLPTR;
}


/*
 * Modify the game base class' static method that takes an integer and an array of pointers to char 
   (the same types as are given to argc and argv in your program's main function signature) so that 
   its return type is void. Change the method's implementation so that it first 
 * (1) checks whether the static shared smart pointer member variable (added above) is equal to nullptr 
       and if not throws an exception; and otherwise (if the shared smart pointer is equal to nullptr) 
 * (2) dynamically allocates the appropriate game object corresponding to the strings passed into the method and 
 * (3) stores the address of that game object in the static shared smart pointer member variable. 
 * Also, if a bad game name was given or another condition occurred that prevented the method from successfully 
   completing, a different exception should be thrown for each different failure case (note that it's fine to 
   throw the same type of exception but if so different values should be thrown).
 */
void GameBase::objectAddressPtr(int argc, char *argv[]) {
	if (ptr != nullptr)
	{//  if not throws an exception
		throw NOT_NULL_PTR;
	}
	else
	{// shared smart pointer member variable (added above) is equal to nullptr
		if (argc == ARGUMENT_0) // two arguments - default case
		{
	 		if (!strcmp(argv[GAME_NAME], "NineAlmonds"))
			{ // user want to play NineAlmondsGame
				gameName = argv[GAME_NAME];
				ptr = make_shared<NineAlmondsGame>();
			}
	 		else if (!strcmp(argv[GAME_NAME], "MagicSquare"))
	 		{ // user want to play MagicSquareGame
				gameName = argv[GAME_NAME];
				ptr = make_shared<MagicSquareGame>();
	 		}
			else
			{
				throw WRONG_GAME_NAME;
			}
		}
		// Extra Credit
		// # set game board size
		else if ((argc == ARGUMENT_1)) // three arguments 
		{
			if (!strcmp(argv[GAME_NAME], "MagicSquare"))
			{
				if (is_numeric(argv[BOARD_SIZE]))
				{
					gameName = argv[GAME_NAME]; // store the game name
					ptr = (make_shared<MagicSquareGame>(atoi(argv[BOARD_SIZE])));
				}
				else
				{
					throw INVALID_BOARD_SIZE;
				}
			}
			else
			{
				throw WRONG_GAME_NAME;
			}
		}
		//* set game board size and minimum start value of the available pieces
		 else if ((argc == ARGUMENT_2)) 
		 {
			 if (!strcmp(argv[GAME_NAME], "MagicSquare"))
			 {
				 if (is_numeric(argv[BOARD_SIZE])) 
				 {
					 if (is_numeric(argv[LOWEST_VALUE_PIECE]))
					 {
						 gameName = argv[GAME_NAME];
						 ptr = (make_shared<MagicSquareGame>(atoi(argv[BOARD_SIZE]), atoi(argv[LOWEST_VALUE_PIECE])));
					 }
					 else
					 {
						 throw INVALID_LOWEST_VALUE_PIECE;
					 }
				 }
				 else
				 {
					 throw INVALID_BOARD_SIZE;
				 }
			 }
			 else
			 {
				 throw WRONG_GAME_NAME;
			 }
		 }
		 else
		 {
			 throw WRONG_NUMBER_ARGUMENTS;
		 }
	}
}