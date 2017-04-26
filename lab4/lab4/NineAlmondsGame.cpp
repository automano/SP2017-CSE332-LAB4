// NineAlmondsGame.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: Declare and define a class that implements a single-player game version of the the Nine Almonds puzzle

#include "stdafx.h"
#include "GameBase.h"
#include "NineAlmondsGame.h"
#include "common.h"

const int DIS_MAX = 2;
const int DIS_MIN = 0;

/*
 * Insertion operator
 * Modify the ostream insertion operator (from the previous lab) so that it takes a reference to a const object of the derived class 
 * for your Nine Almonds game, and uses the maximum display string length stored by the base class to print the board out not just by 
 * putting a space between consecutive piece symbols on a line, but also adjusting the widths of the squares according to the maximum 
 * display string length so that columns of the board are aligned vertically with at least a space between pieces when they are displayed. 
 */
ostream & operator<<(ostream &os, const NineAlmondsGame &game_board) {
	for (int y = game_board.vertical_dimension - 1; y >= 0; y--) {
		os << y << " "; // print vertical index
		for (int x = 0; x < game_board.horizontal_dimension; x++) {
			if (x == 0) {
				// print the first column
				os << game_board.game_piece[y*game_board.horizontal_dimension + x];
			}
			else {
				// print other columns 
				os << setw(game_board.longest_piece_length - game_board.game_piece[y*game_board.horizontal_dimension + x].length() + 2) 
				   << game_board.game_piece[y*game_board.horizontal_dimension + x];
			}
		}
		os << endl;
	}
	os << "X"; // print X mark
   
	for (int i = 0; i < game_board.horizontal_dimension; i++) // print horizontal index
		os << setw(game_board.longest_piece_length + 1) << i; 
	os << endl;
	
	return os;
}


/* 
 * Initialize the game board
 * The game board is five squares wide and five squares tall. The lower left square has coordinate 0,0 (as in the previous lab) 
   and the upper right square has coordinate 4,4.
 * Each piece in this game is a brown almond, and should be represented by an 'A' character on the terminal screen when the board is printed.
 * When the game begins, the inner nine squares of the board (coordinates 1,1 through 3,3) should all have brown almonds on them, and the outer
   sixteen squares of the board (each of which has a 0 or 4 in the horizontal or vertical portion of their coordinate) should be empty.
 * Modify the constructors of your Magic Square and Nine Almonds games so that they use an ifstream to open up a file that has the same name 
 as the game, and determine whether or not the file contains valid state of a previously saved version of that particular game. If so, the 
 constructor should use that data to initialize the game object into that saved state. If not, the constructor should initialize the object 
 into the initial game state it had when it first started up, as in the previous lab assignments.
 */
NineAlmondsGame::NineAlmondsGame() { // constructor

	ifstream ifs(gameName + ".txt");
	if (ifs.is_open()) // game file exists
	{
		string firstline = "";
		getline(ifs, firstline);
		if (firstline == "NO DATA")
		{
			// new game default constructor
			game_turns_count = 0;
			horizontal_dimension = 5;
			vertical_dimension = 5;
			longest_piece_length = 0;
			game_piece.resize(horizontal_dimension*vertical_dimension);
			for (int y = 0; y < vertical_dimension; y++)
			{
				for (int x = 0; x < horizontal_dimension; x++)
				{
					if (x == 0 || x == horizontal_dimension - 1 || y == 0 || y == vertical_dimension - 1)
						// the inner nine squares of the board should all have brown almonds on them
						game_piece[y*horizontal_dimension + x] = EMPTY;
					else
						// the outer sixteen squares of the board should be empty.
						game_piece[y*horizontal_dimension + x] = ALMOND;

					if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
						// updated longest_piece_length if needed whenever a piece is added to the board
						longest_piece_length = game_piece[y*horizontal_dimension + x].length();
				}
			}
			ifs.close();
		}
		else if (firstline == "NineAlmonds")
		{
			// saved game default constructor
			// default parameters
			horizontal_dimension = 5;
			vertical_dimension = 5;

			// get game turns from game file
			string secondline = "";
			getline(ifs, secondline);
			stringstream ss1;
			ss1 << secondline;
			ss1 >> game_turns_count;

			// get longest length game piece
			string thirdline = "";
			getline(ifs, thirdline);
			stringstream ss2;
			ss2 << thirdline;
			ss2 >> longest_piece_length;

			// get game pieces from game file
			game_piece.resize(horizontal_dimension*vertical_dimension);
			for (int y = 0; y < vertical_dimension; y++)
			{
				for (int x = 0; x < horizontal_dimension; x++)
				{
					getline(ifs, game_piece[y*horizontal_dimension + x]);
				}
			}
			ifs.close();
		}
		else
		{
			throw BAD_FORMAT_LINE;
		}	
	}
	else // game file not exits - Run the game for the first time
	{
		// create the game file
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
		// new game default constructor
		game_turns_count = 0;
		horizontal_dimension = 5;
		vertical_dimension = 5;
		longest_piece_length = 0;
		game_piece.resize(horizontal_dimension*vertical_dimension);
		for (int y = 0; y < vertical_dimension; y++)
		{
			for (int x = 0; x < horizontal_dimension; x++)
			{
				if (x == 0 || x == horizontal_dimension - 1 || y == 0 || y == vertical_dimension - 1)
					// the inner nine squares of the board should all have brown almonds on them
					game_piece[y*horizontal_dimension + x] = EMPTY;
				else
					// the outer sixteen squares of the board should be empty.
					game_piece[y*horizontal_dimension + x] = ALMOND;

				if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
					// updated longest_piece_length if needed whenever a piece is added to the board
					longest_piece_length = game_piece[y*horizontal_dimension + x].length();
			}
		}
	}
}

// Method: print
void NineAlmondsGame::print() {
	cout << *this << endl;
}

/*
 * Method: done()
 * Takes no parameters (other than the this pointer that's passed implicitly to all non-static methods and operators) and has a bool return type. 
 * This method should return true if there is exactly one almond positioned at the center of the board (the square with coordinate 2,2), and all 
 * other squares are empty; otherwise the method should return false.
 */
bool NineAlmondsGame::done() {
	unsigned int empty_count = 0; // Counter of empty pieces
	const int CENTER_INDEX = 12; // Index of coordinate 2,2 is 12 
	const int DEFAULT_EMPTY_COUNT = 24;  // Should have 24 empty pieces 
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			if (game_piece[y*horizontal_dimension + x] == EMPTY)
			{
				empty_count++; // count empty game pieces number
			}
		}
	}
	if (empty_count == DEFAULT_EMPTY_COUNT && game_piece[CENTER_INDEX] == ALMOND)
		// exactly one almond positioned at the center of the board (the square with coordinate 2,2), and all other squares are empty
		return true;
	else
		return false;
} 

/*
 * Method: stalemate()
 * Takes no parameters (other than the this pointer that's passed implicitly to all non-static methods and operators) and has a bool return type. 
 * This method should return false if there are any valid moves remaining in the game (as defined below) or if the done() method returns true; 
 * otherwise (if there are no valid moves remaining and the game has not been completed successfully) the stalemate() method should return true.
 */
bool NineAlmondsGame::stalemate() {
	if (this->done()) //if the done() method returns true
		return false;
	else
	{// traverse the game board to check valid moves
	 // Brute Force
		for (int y = 0; y < vertical_dimension; y++)
		{
			for (int x = 0; x < horizontal_dimension; x++)
			{
				// neighbor index
				int x_left_n = x - 1;
				int x_right_n = x + 1;
				int y_down_n = y - 1;
				int y_up_n = y + 1;
				// destination index
				int x_left_d = x - 2;
				int x_right_d = x + 2;
				int y_down_d = y - 2;
				int y_up_d = y + 2;

				// find a almonds first
				if (game_piece[y*horizontal_dimension + x] == ALMOND)
				{ // check #1 move (left down)
					if (x_left_n >= 0 && x_left_n < horizontal_dimension &&
						y_down_n >= 0 && y_down_n < vertical_dimension && // check if neighbor on the game board
						game_piece[y_down_n*horizontal_dimension + x_left_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_left_d >= 0 && x_left_d < horizontal_dimension &&
						y_down_d >= 0 && y_down_d < vertical_dimension && // check if destination on the game board
						game_piece[y_down_d*horizontal_dimension + x_left_d] == EMPTY) // ends with an empty square that is two positions away
						return false;

					//check #2 move (down)
					else if (
						x >= 0 && x < horizontal_dimension &&
						y_down_n >= 0 && y_down_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_down_n*horizontal_dimension + x] == ALMOND && //check there is an almond on the square that is in between the two squares
						x >= 0 && x < horizontal_dimension &&
						y_down_d >= 0 && y_down_d < vertical_dimension && // check if destination on the game board
						game_piece[y_down_d*horizontal_dimension + x] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #3 move (right down)
					else if (
						x_right_n >= 0 && x_right_n < horizontal_dimension &&
						y_down_n >= 0 && y_down_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_down_n*horizontal_dimension + x_right_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_right_d >= 0 && x_right_d < horizontal_dimension &&
						y_down_d >= 0 && y_down_d < vertical_dimension && // check if destination on the game board
						game_piece[y_down_d*horizontal_dimension + x_right_d] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #4 move (left)
					else if (
						x_left_n >= 0 && x_left_n < horizontal_dimension &&
						y_up_n >= 0 && y_up_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_up_n*horizontal_dimension + x_left_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_left_d >= 0 && x_left_d < horizontal_dimension &&
						y >= 0 && y < vertical_dimension && // check if destination on the game board
						game_piece[y*horizontal_dimension + x_left_d] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #5 move (right)
					else if (
						x_right_n >= 0 && x_right_n < horizontal_dimension &&
						y >= 0 && y < vertical_dimension &&// check if neighbor on the game board
						game_piece[y*horizontal_dimension + x_right_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_right_d >= 0 && x_right_d < horizontal_dimension &&
						y >= 0 && y < vertical_dimension && // check if destination on the game board
						game_piece[y*horizontal_dimension + x_right_d] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #6 move (left up)
					else if (
						x_left_n >= 0 && x_left_n < horizontal_dimension &&
						y_up_n >= 0 && y_up_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_up_n*horizontal_dimension + x_left_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_left_d >= 0 && x_left_d < horizontal_dimension &&
						y_up_d >= 0 && y_up_d < vertical_dimension && // check if destination on the game board
						game_piece[y_up_d*horizontal_dimension + x_left_d] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #7 move (up)
					else if (
						x >= 0 && x < horizontal_dimension &&
						y_up_n >= 0 && y_up_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_up_n*horizontal_dimension + x] == ALMOND && //check there is an almond on the square that is in between the two squares
						x >= 0 && x < horizontal_dimension &&
						y_up_d >= 0 && y_up_d < vertical_dimension && // check if destination on the game board
						game_piece[y_up_d*horizontal_dimension + x] == EMPTY) // ends with an empty square that is two positions away
						return false;

					// check #8 move (right up)
					else if (
						x_right_n >= 0 && x_right_n < horizontal_dimension &&
						y_up_n >= 0 && y_up_n < vertical_dimension &&// check if neighbor on the game board
						game_piece[y_up_n*horizontal_dimension + x_right_n] == ALMOND && //check there is an almond on the square that is in between the two squares
						x_right_d >= 0 && x_right_d < horizontal_dimension &&
						y_up_d >= 0 && y_up_d < vertical_dimension && // check if destination on the game board
						game_piece[y_up_d*horizontal_dimension + x_right_d] == EMPTY) // ends with an empty square that is two positions away
						return false;
				}
			}
		}
		return true;
	}
}

/*
 * Method: turn()
 * Takes no parameters. 
 * The method should (repeatedly if necessary) call the prompt() method twice to obtain coordinates for the beginning and ending squares (respectively) 
 * for a valid move in the game, or to determine that the user has quit the game (if the user quits, the turn() method should immediately 
 * return an appropriate failure value, instead of doing any further processing).
 */
int NineAlmondsGame::turn() {

	string move_info = "";
	string in = "";
	// beginning square coordinates
	unsigned int x_o = 0;
	unsigned int y_o = 0;
	// ending square coordinates
	unsigned int x_d = 0;
	unsigned int y_d = 0;

	cout << "----- Beginning square -----" << endl;
	if ((this->prompt(x_o, y_o) == SUCCESS)) {
		cout << "----- Ending square -----" << endl;
		if ((this->prompt(x_d, y_d) == SUCCESS)) {
			// index of almond on the square that is in between the beginning ande ending squares
			unsigned int x_m = x_o + int((x_d - x_o)) / 2;
			unsigned int y_m = y_o + int((y_d - y_o)) / 2;

			if (this->validmove(x_o, y_o, x_d, y_d)) {
				// set squares
				(*this).game_piece[y_o*horizontal_dimension + x_o] = EMPTY;
				(*this).game_piece[y_m*horizontal_dimension + x_m] = EMPTY;
				(*this).game_piece[y_d*horizontal_dimension + x_d] = ALMOND;

				// print current game board
				this->print();
				cout << endl;

				// print out move info
				move_info = to_string(x_o) + "," + to_string(y_o) + " to " + to_string(x_d) + "," + to_string(y_d);
				cout << move_info << endl << endl;

				// ask if user want to continue
				cout << "Continue this turn(YyNn)?" << endl;
				cin >> in;
				LowerCase(in);
				while (in != "y" && in != "n") {
					cout << "Invalid input, try y or n!" << endl;
					cin >> in;
					LowerCase(in);
				}
				while (in == "y") {
					// set beginning square coordinates to previous move
					x_o = x_d;
					y_o = y_d;
					// get ending square coordinates
					cout << "----- Next move -----" << endl;
					if (this->prompt(x_d, y_d) == SUCCESS) {
						// index of almond on the square that is in between the beginning ande ending squares
						x_m = x_o + int((x_d - x_o)) / 2;
						y_m = y_o + int((y_d - y_o)) / 2;
						if (this->validmove(x_o, y_o, x_d, y_d)) {
							// set squares
							(*this).game_piece[y_o*horizontal_dimension + x_o] = EMPTY;
							(*this).game_piece[y_m*horizontal_dimension + x_m] = EMPTY;
							(*this).game_piece[y_d*horizontal_dimension + x_d] = ALMOND;
							// print current game board
							this->print();
							cout << endl;

							// print out move info
							move_info = move_info + " to " + to_string(x_d) + "," + to_string(y_d);
							cout << move_info << endl << endl;

							// ask if user want to continue
							cout << endl << "Continue this turn (YyNn)?" << endl;
							cin >> in;
							LowerCase(in);
							while (in != "y" && in != "n") {
								cout << "Invalid input, try y or n!" << endl;
								cin >> in;
								LowerCase(in);
							}
						}
						else {
							cout << "Invalid Move! Continue this turn(YyNn)?" << endl;
							cin >> in;
							LowerCase(in);
							while (in != "y" && in != "n") {
								cout << "Invalid input, try y or n!" << endl;
								cin >> in;
								LowerCase(in);
							}
						}
					}
					else {
						return PLAYER_QUIT;
					}
				}
				return SUCCESS;
			}
			else
			{
				cout << "Error: Invalid move!" << endl
					<< "A valid move:" << endl
					<< "(1) Starts with a square on the board that contains an almond;" << endl
					<< "(2) Ends with an empty square that is two positions away from the original square either diagonally, vertically, or horizontally;" << endl
					<< "(3) There is an almond on the square that is in between the two squares." << endl;
				return INVALID_MOVE;
			}
		}
		else {
			return PLAYER_QUIT;
		}
	}
	else {
		return PLAYER_QUIT;
	}
}

/*
 * Funtion validmove()
 * A move is valid if and only if it moves an almond to an empty square by jumping over another almond. 
 * Specifically, a valid move: 
 * (1) starts with a square on the board that contains an almond; 
 * (2) ends with an empty square that is two positions away from the original square either diagonally, vertically, or horizontally (for example 0,0 or 0,2 or 0,4 or 2,0 or 2,4 or 4,0 or 4,2 or or 4,4 would be two positions away from the center square 2,2)
 * (3) there is an almond on the square that is in between the two squares.
 */ 
bool NineAlmondsGame::validmove(unsigned int x_o, unsigned int y_o, unsigned int x_d, unsigned int y_d) {
	// index of almond on the square that is in between the beginning ande ending squares
	unsigned int x_m = x_o + int((x_d - x_o)) / 2;
	unsigned int y_m = y_o + int((y_d - y_o)) / 2;
	// distance between beginning square and ending square
	unsigned int x_dis = abs(int(x_d - x_o));
	unsigned int y_dis = abs(int(y_d - y_o));

	if ((x_dis == DIS_MAX || x_dis == DIS_MIN) && (y_dis == DIS_MAX || y_dis == DIS_MIN)
		&& game_piece[y_o*horizontal_dimension + x_o] == ALMOND
		&& game_piece[y_d*horizontal_dimension + x_d] == EMPTY
		&& game_piece[y_m*horizontal_dimension + x_m] == ALMOND)
		return true;
	else
		return false;
}