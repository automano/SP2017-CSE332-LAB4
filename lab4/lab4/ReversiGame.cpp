// ReversiGame.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: 

#include "stdafx.h"
#include "GameBase.h"
#include "ReversiGame.h"
#include "common.h"

// Index used for init game board
const int init_X_index_1 = 3 * 8 + 3; //(3,3) - X
const int init_X_index_2 = 4 * 8 + 4; //(4,4) - X
const int init_O_index_1 = 4 * 8 + 3; //(3,4) - O
const int init_O_index_2 = 3 * 8 + 4; //(4,3) - O
/*
 * Inside your Reversi game class, declare the insertion operator to be a friend so that it can 
   access the private member variables of the game object. The operator should print out the current 
   state of the game board with coordinate labels on the axes, each piece's display symbol for squares 
   that have pieces on them, and spaces for empty squares. 
 */
 // Adapted from NineAlmondsGame.cpp
ostream & operator<<(ostream &os, const ReversiGame &game_board) {
	for (int y = game_board.vertical_dimension - 1; y >= 0; y--) 
	{
		os << y << " "; // print vertical index
		for (int x = 0; x < game_board.horizontal_dimension; x++) 
		{
			if (x == 0) 
			{
				// print the first column
				os << game_board.game_piece[y*game_board.horizontal_dimension + x];
			}
			else
			{
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
 * The Reversi game is played by two players, one playing the black pieces (who moves first) and one 
 playing the white pieces (who moves second). The game's constructor should take strings for the name 
 of the person playing the black pieces and then the name of the person playing the white pieces, and 
 store those names in member variables for use when prompting a player for their turn. The Reversi game 
 board should be 8 by 8, with squares numbered from 0,0 (lower left corner) to 7,7 (upper right corner).

 * The game pieces for Reversi are either black (denoted on the board by "X"), or white (denoted on the 
 board by "O"). In the actual board game, each piece is a two-sided "coin", with the two colors on opposite 
 sides - if you'd like to add a new kind of game piece to your inheritance hierarchy to model this you can, 
 though it may be simpler to just represent them as game pieces of one color or the other, which are replaced 
 by a piece of the other color (or which change their color and display symbol) when needed.

 * As in your Magic Square and Nine Almonds games your constructor for the Reversi game class should use 
 an ifstream to open up a file that has the same name as the game (e.g., ReversiGame), and determine whether 
 or not the file contains the valid state of a previously saved version of that particular game. If so, the 
 constructor should use that data to initialize the game object into that saved state. If not, the constructor 
 should initialize the object into an initial game state with black pieces on squares 3,3 and 4,4, white pieces 
 on squares 3,4 and 4,3, and all other squares of the board should be empty.
 */
ReversiGame::ReversiGame(string player_black, string player_white) { // constructor

	ifstream ifs(gameName + ".txt");
	if (ifs.is_open()) // game file exists
	{
		string firstline = "";
		getline(ifs, firstline);
		if (firstline == "NO DATA")
		{
			// Default constructor
			game_turns_count = 0;
			horizontal_dimension = 8;
			vertical_dimension = 8;
			longest_piece_length = 0;
			player_1 = player_black;
			player_2 = player_white;
			game_piece.resize(horizontal_dimension*vertical_dimension);
			for (int y = 0; y < vertical_dimension; y++)
			{
				for (int x = 0; x < horizontal_dimension; x++)
				{
					if (y*horizontal_dimension + x == init_X_index_1 || y*horizontal_dimension + x == init_X_index_2)
						// init X at (3,3) and (4,4)
						game_piece[y*horizontal_dimension + x] = BLACK;
					else if (y*horizontal_dimension + x == init_O_index_1 || y*horizontal_dimension + x == init_O_index_2)
						// init O at (3,4) and (4,3)
						game_piece[y*horizontal_dimension + x] = WHITE;
					else
						// other game pieces should be empty
						game_piece[y*horizontal_dimension + x] = EMPTY;

					if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
						// updated longest_piece_length if needed whenever a piece is added to the board
						longest_piece_length = game_piece[y*horizontal_dimension + x].length();
				}
			}
			ifs.close();
		}
		else if (firstline == "Reversi")
		{
			// saved game default constructor
			// default parameters
			horizontal_dimension = 8;
			vertical_dimension = 8;
			player_1 = player_black;
			player_2 = player_white;

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
		// Default constructor
		game_turns_count = 0;
		horizontal_dimension = 8;
		vertical_dimension = 8;
		longest_piece_length = 0;
		player_1 = player_black;
		player_2 = player_white;
		game_piece.resize(horizontal_dimension*vertical_dimension);
		for (int y = 0; y < vertical_dimension; y++)
		{
			for (int x = 0; x < horizontal_dimension; x++)
			{
				if (y*horizontal_dimension + x == init_X_index_1 || y*horizontal_dimension + x == init_X_index_2)
					// init X at (3,3) and (4,4)
					game_piece[y*horizontal_dimension + x] = BLACK;
				else if (y*horizontal_dimension + x == init_O_index_1 || y*horizontal_dimension + x == init_O_index_2)
					// init O at (3,4) and (4,3)
					game_piece[y*horizontal_dimension + x] = WHITE;
				else
					// other game pieces should be empty
					game_piece[y*horizontal_dimension + x] = EMPTY;

				if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
					// updated longest_piece_length if needed whenever a piece is added to the board
					longest_piece_length = game_piece[y*horizontal_dimension + x].length();
			}
		}
	}
}

// Method: print()
void ReversiGame::print() {
	cout << *this << endl;
}

/*
 * Method: done()
 * Declare and define a public virtual (non-static) done() method that takes no parameters (other than the this
 pointer that's passed implicitly to all non-static methods and operators) and has a bool return type. The method 
 should return true if either (1) all pieces on the board are of the same color, or (2) there are more pieces of 
 one color than another color on the board and either of the following is true: (a) all squares are filled; or 
 (b) there are no remaining legal moves for either player (Note that this requires your game to identify explicitly 
 which moves are valid plays for either player); otherwise the method should return false.
 */
bool ReversiGame::done() {
	int black_count = 0; // how many black pieces on the current game board
	int white_count = 0; // how many white pieces on the current game board
	int empty_count = 0; // how many empty piece on the current game board
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			if (game_piece[y*horizontal_dimension + x] == BLACK)
				// black piece 
				black_count++;
			if (game_piece[y*horizontal_dimension + x] == WHITE)
				// white piece 
				white_count++;
			if (game_piece[y*horizontal_dimension + x] == EMPTY)
				// empty piece 
				empty_count++;
		}
	}

	// (1) all pieces on the board are of the same color - return true
	if ((black_count == 0 && white_count != 0) || (white_count == 0 && black_count != 0))
	{
		if (black_count > white_count) // player_1 win
		{
			cout << "BLACK: " << black_count << endl;
			cout << "WHITE: " << white_count << endl;
			cout << "Congratulations to you! " << player_1 << " You win!" << endl;
			cout << "Total turns: " << game_turns_count << "." << endl;
		}
		if (white_count > black_count) // player_2 win
		{
			cout << "BLACK: " << black_count << endl;
			cout << "WHITE: " << white_count << endl;
			cout << "Congratulations to you! " << player_2 << " You win!" << endl;
			cout << "Total turns: " << game_turns_count << "." << endl;
		}
		return true;
	}

	// (2) there are more pieces of one color than another color on the board 
	if ((black_count > white_count) || (black_count < white_count))
	{
		// (a) all squares are filled - return true
		if (empty_count == 0)
		{
			if (black_count > white_count) // player_1 win
			{
				cout << "BLACK: " << black_count << endl; 
				cout << "WHITE: " << white_count << endl;
				cout << "Congratulations to you! " << player_1 << " You win!" << endl;
				cout << "Total turns: " << game_turns_count << "." << endl;
			}
			if (white_count > black_count) // player_2 win
			{
				cout << "BLACK: " << black_count << endl;
				cout << "WHITE: " << white_count << endl;
				cout << "Congratulations to you! " << player_2 << " You win!" << endl;
				cout << "Total turns: " << game_turns_count << "." << endl;
			}
			return true;	
		}
		// (b) no remaining legal moves for either player - return true
		if (!hasValidmove(player_1) && !hasValidmove(player_2))
		{
			if (black_count > white_count) // player_1 win
			{
				cout << "BLACK: " << black_count << endl;
				cout << "WHITE: " << white_count << endl;
				cout << "Congratulations to you! " << player_1 << " You win!" << endl;
				cout << "Total turns: " << game_turns_count << "." << endl;
			}
			if (white_count > black_count) // player_2 win
			{
				cout << "BLACK: " << black_count << endl;
				cout << "WHITE: " << white_count << endl;
				cout << "Congratulations to you! " << player_2 << " You win!" << endl;
				cout << "Total turns: " << game_turns_count << "." << endl;
			}
			return true;	
		}
	}
	// otherwise the method should return false
	return false;
}

/* Method: stalemate()
 * Declare and define a public virtual (non-static) stalemate() method that takes no parameters (other than the this 
 pointer that's passed implicitly to all non-static methods and operators) and has a bool return type. The method should 
 return true if both (1) there are the same number of black pieces and white pieces on the board and (2) either of the 
 following is true: (a) all squares are filled; or (b) there are no remaining legal moves for either player; otherwise 
 the method should return false.
 */
bool ReversiGame::stalemate() {
	int black_count = 0; // how many black pieces on the current game board
	int white_count = 0; // how many white pieces on the current game board
	int empty_count = 0; // how many empty piece on the current game board
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			if (game_piece[y*horizontal_dimension + x] == BLACK)
				// black piece 
				black_count++;
			if (game_piece[y*horizontal_dimension + x] == WHITE)
				// white piece 
				white_count++;
			if (game_piece[y*horizontal_dimension + x] == EMPTY)
				// empty piece 
				empty_count++;
		}
	}
	// (1) there are the same number of black pieces and white pieces on the board - return true
	if (black_count == white_count)
	{
		//(a) all squares are filled - return true
		if (empty_count == 0)
		{
			return true;
		}
		// (b) there are no remaining legal moves for either player - return true
		if (!hasValidmove(player_1) && !hasValidmove(player_2))
		{
			return true;
		}
	}
	// otherwise the method should return false
	return false;
}

/* Method: turn()
 * Declare and define a virtual public (non-static) turn() method that takes no parameters and has an appropriate return 
 type. The game should remember which player's turn it is, the method should print out a message to that effect (using 
 the player names that were passed into the Reversi game's constructor), and the method should alternate whose turn it 
 is each time it is called.
 */
int ReversiGame::turn() {
	//  print out a message to that effect (using the player names that were passed into the Reversi game's constructor)
	if (game_turns_count % 2 == 0) // even turn - black player
	{
		cout << "----- " <<"Turn "<<game_turns_count<< " " << this->player_1 << "'s turn" << " -----" << endl;
		// For the player whose turn it is, the turn() method should first determine whether or not there are any valid empty squares on which the current player can play a piece.
		if (!hasValidmove(this->player_1))
		{
			cout << "No valid move for yout turn! " << this->player_1 << endl;
			return SKIP_CURRENT_TURN;
		}
		// piece coordinates
		unsigned int x_d = 0;
		unsigned int y_d = 0;
		cout << "----- Choose square -----" << endl;
		if ((this->prompt(x_d, y_d) == SUCCESS))
		{
			if (makeFlip(this->player_1, x_d, y_d))
			{
				this->print();
				return SUCCESS;
			}
			else
			{
				cout << "Your move is invalid, Please try an another move." << endl;
				return INVALID_MOVE;
			}
		}
		else 
		{
			return PLAYER_QUIT;
		}
	}
	else // odd even - white player
	{
		cout << "----- " << "Turn " << game_turns_count << " " << player_2 << "'s turn" << " -----" << endl;
		// For the player whose turn it is, the turn() method should first determine whether or not there are any valid empty squares on which the current player can play a piece.
		if (!hasValidmove(player_2))
		{
			cout << "No valid move for yout turn! " << player_2 << endl;
			return SKIP_CURRENT_TURN;
		}
		// piece coordinates
		unsigned int x_d = 0;
		unsigned int y_d = 0;
		cout << "----- Choose square -----" << endl;
		if ((this->prompt(x_d, y_d) == SUCCESS))
		{
			if (makeFlip(player_2, x_d, y_d))
			{
				cout << endl;
				this->print();
				return SUCCESS;
			}
			else
			{
				cout << "Invalid Move! Try another!" << endl;
				return INVALID_MOVE;
			}
		}
		else
		{
			return PLAYER_QUIT;
		}
	}
}

/* Method: validmove()
 * An empty square is valid if contiguously from that empty square in any vertical, horizontal, or diagonal direction (with 
 no other intervening empty squares) there is (are) one or more pieces of the other player's color followed immediately (again 
 with no intervening empty squares) by a piece of the color played by the player whose turn it is.
 */
bool ReversiGame::hasValidmove(string currentPlayer) {

	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			// neighbor index
			int x_left_n = x - 1;
			int x_right_n = x + 1;
			int y_down_n = y - 1;
			int y_up_n = y + 1;

			if (y*horizontal_dimension + x >= 0 && y*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
			{
				// check eight different directions
				if (game_piece[y*horizontal_dimension + x] == EMPTY) // target piece are empty
				{
					// check for player_1
					if (currentPlayer == player_1) // BLACK - current
					{
						if (y_down_n*horizontal_dimension + x >= 0 && y_down_n*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #1 down
							if (game_piece[y_down_n*horizontal_dimension + x] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; y - i >= 0; i++)
								{
									if ((y - i)*horizontal_dimension + x >= 0 && (y - i)*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + x] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + x] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}
						
						if (y_up_n*horizontal_dimension + x >= 0 && y_up_n*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #2 up
							if (game_piece[y_up_n*horizontal_dimension + x] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; y + i <= vertical_dimension; i++)
								{
									if ((y + i)*horizontal_dimension + x >= 0 && (y + i)*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + x] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + x] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}
			
						if (y*horizontal_dimension + x_left_n >= 0 && y*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #3 left
							if (game_piece[y*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; x - i >= 0; i++)
								{
									if (y*horizontal_dimension + (x - i) >= 0 && y*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[y*horizontal_dimension + (x - i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[y*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y*horizontal_dimension + x_right_n >= 0 && y*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #4 right
							if (game_piece[y*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; x + i <= horizontal_dimension; i++)
								{
									if (y*horizontal_dimension + (x + i) >= 0 && y*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[y*horizontal_dimension + (x + i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[y*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}
						
						if (y_down_n*horizontal_dimension + x_left_n >= 0 && y_down_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #5 left down
							if (game_piece[y_down_n*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; (y - i >= 0) && (x - i >= 0); i++)
								{
									if ((y - i)*horizontal_dimension + (x - i) >= 0 && (y - i)*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + (x - i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}

						}

						if (y_down_n*horizontal_dimension + x_right_n >= 0 && y_down_n*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #6 right dwon
							if (game_piece[y_down_n*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; (y - i >= 0) && (x + i <= horizontal_dimension); i++)
								{
									if ((y - i)*horizontal_dimension + (x + i) >= 0 && (y - i)*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + (x + i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_up_n*horizontal_dimension + x_left_n >= 0 && y_up_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #7 left up
							if (game_piece[y_up_n*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; (y + i <= vertical_dimension) && (x - i >= 0); i++)
								{
									if ((y + i)*horizontal_dimension + (x - i) >= 0 && (y + i)*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + (x - i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_up_n*horizontal_dimension + x_right_n>=0&& y_up_n*horizontal_dimension + x_right_n<horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #8 right up
							if (game_piece[y_up_n*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
							{
								for (int i = 2; (y + i <= vertical_dimension) && (x + i <= horizontal_dimension); i++)
								{
									if ((y + i)*horizontal_dimension + (x + i) >= 0 && (y + i)*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + (x + i)] == BLACK) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}
					}

					if (currentPlayer == player_2) // WHITE - current
					{
						if (y_down_n*horizontal_dimension + x >= 0 && y_down_n*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #1 down
							if (game_piece[y_down_n*horizontal_dimension + x] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; y - i >= 0; i++)
								{
									if ((y - i)*horizontal_dimension + x >= 0 && (y - i)*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + x] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + x] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_up_n*horizontal_dimension + x >= 0 && y_up_n*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #2 up
							if (game_piece[y_up_n*horizontal_dimension + x] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; y + i <= vertical_dimension; i++)
								{
									if ((y + i)*horizontal_dimension + x >= 0 && (y + i)*horizontal_dimension + x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + x] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + x] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y*horizontal_dimension + x_left_n >= 0 && y*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #3 left
							if (game_piece[y*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; x - i >= 0; i++)
								{
									if (y*horizontal_dimension + (x - i) >= 0 && y*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[y*horizontal_dimension + (x - i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[y*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y*horizontal_dimension + x_right_n >= 0 && y*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #4 right
							if (game_piece[y*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; x + i <= horizontal_dimension; i++)
								{
									if (y*horizontal_dimension + (x + i) >= 0 && y*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[y*horizontal_dimension + (x + i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[y*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_down_n*horizontal_dimension + x_left_n >= 0 && y_down_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #5 left down
							if (game_piece[y_down_n*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; (y - i >= 0) && (x - i >= 0); i++)
								{
									if ((y - i)*horizontal_dimension + (x - i) >= 0 && (y - i)*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + (x - i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}

						}

						if (y_down_n*horizontal_dimension + x_right_n >= 0 && y_down_n*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #6 right dwon
							if (game_piece[y_down_n*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; (y - i >= 0) && (x + i <= horizontal_dimension); i++)
								{
									if ((y - i)*horizontal_dimension + (x + i) >= 0 && (y - i)*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y - i)*horizontal_dimension + (x + i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y - i)*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_up_n*horizontal_dimension + x_left_n >= 0 && y_up_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #7 left up
							if (game_piece[y_up_n*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; (y + i <= vertical_dimension) && (x - i >= 0); i++)
								{
									if ((y + i)*horizontal_dimension + (x - i) >= 0 && (y + i)*horizontal_dimension + (x - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + (x - i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + (x - i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}

						if (y_up_n*horizontal_dimension + x_right_n >= 0 && y_up_n*horizontal_dimension + x_right_n<horizontal_dimension*vertical_dimension) // prevent vector run out of range
						{
							// #8 right up
							if (game_piece[y_up_n*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is white
							{
								for (int i = 2; (y + i <= vertical_dimension) && (x + i <= horizontal_dimension); i++)
								{
									if ((y + i)*horizontal_dimension + (x + i) >= 0 && (y + i)*horizontal_dimension + (x + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
									{
										if (game_piece[(y + i)*horizontal_dimension + (x + i)] == WHITE) // have black piece on this direction
										{
											return true;
										}
										else if (game_piece[(y + i)*horizontal_dimension + (x + i)] == EMPTY) // not contiguous in this direction
										{
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}


/*
 * When a valid square is given by the player, then (a) a piece of the color being played by the player whose turn it is should be 
 placed on that square (each player is assumed to have as many pieces to play as they would need during the game) and then (b) the 
 color of every contiguous sequence of the other player's pieces that's immediately followed by one of the current player's piece, 
 in any direction leading away from the square that was just played, should be flipped to the current player's color.
 */
bool ReversiGame::makeFlip(string currentPlayer, int x_d, int y_d)
{
	// 
	int flip_check = 0;
	// neighbor index
	int x_left_n = x_d - 1;
	int x_right_n = x_d + 1;
	int y_down_n = y_d - 1;
	int y_up_n = y_d + 1;

	if (y_d*horizontal_dimension + x_d >= 0 && y_d*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
	{
		// check eight different directions
		if (game_piece[y_d*horizontal_dimension + x_d] == EMPTY) // target piece are empty
		{
			// check for player_1
			if (currentPlayer == player_1) // BLACK - current
			{
				if (y_down_n*horizontal_dimension + x_d >= 0 && y_down_n*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #1 down
					if (game_piece[y_down_n*horizontal_dimension + x_d] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; y_d - i >= 0; i++)
						{
							if ((y_d - i)*horizontal_dimension + x_d >= 0 && (y_d - i)*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + x_d] == BLACK) // have black piece on this direction
								{	
									// do flip
									for (int flip_index_y = y_d - i; flip_index_y <= y_d; flip_index_y++)
									{
										if (flip_index_y*horizontal_dimension + x_d >= 0 && flip_index_y*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + x_d] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + x_d] = BLACK;
										}	
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + x_d] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_d >= 0 && y_up_n*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #2 up
					if (game_piece[y_up_n*horizontal_dimension + x_d] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; y_d + i <= vertical_dimension; i++)
						{
							if ((y_d + i)*horizontal_dimension + x_d >= 0 && (y_d + i)*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + x_d] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i; flip_index_y >= y_d; flip_index_y--)
									{
										if (flip_index_y*horizontal_dimension + x_d >= 0 && flip_index_y*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + x_d] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + x_d] = BLACK;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + x_d] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_d*horizontal_dimension + x_left_n >= 0 && y_d*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #3 left
					if (game_piece[y_d*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; x_d - i >= 0; i++)
						{
							if (y_d*horizontal_dimension + (x_d - i) >= 0 && y_d*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[y_d*horizontal_dimension + (x_d - i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_x = x_d - i; flip_index_x <= x_d; flip_index_x++)
									{
										if (y_d*horizontal_dimension + flip_index_x >= 0 && y_d*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[y_d*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[y_d*horizontal_dimension + flip_index_x] = BLACK;
										}										
									}
									flip_check++;
								}
								else if (game_piece[y_d*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_d*horizontal_dimension + x_right_n >= 0 && y_d*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #4 right
					if (game_piece[y_d*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; x_d + i <= horizontal_dimension; i++)
						{
							if (y_d*horizontal_dimension + (x_d + i) >= 0 && y_d*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[y_d*horizontal_dimension + (x_d + i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_x = x_d + i; flip_index_x >= x_d; flip_index_x--)
									{
										if (y_d*horizontal_dimension + flip_index_x >= 0 && y_d*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[y_d*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[y_d*horizontal_dimension + flip_index_x] = BLACK;
										}									
									}
									flip_check++;
								}
								else if (game_piece[y_d*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_down_n*horizontal_dimension + x_left_n >= 0 && y_down_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #5 left down
					if (game_piece[y_down_n*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; (y_d - i >= 0) && (x_d - i >= 0); i++)
						{
							if ((y_d - i)*horizontal_dimension + (x_d - i) >= 0 && (y_d - i)*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + (x_d - i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d - i, flip_index_x = x_d - i; flip_index_y <= y_d&&flip_index_x <= x_d; flip_index_y++, flip_index_x++)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = BLACK;
										}	
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}

				}

				if (y_down_n*horizontal_dimension + x_right_n >= 0 && y_down_n*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #6 right dwon
					if (game_piece[y_down_n*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; (y_d - i >= 0) && (x_d + i <= horizontal_dimension); i++)
						{
							if ((y_d - i)*horizontal_dimension + (x_d + i) >= 0 && (y_d - i)*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + (x_d + i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d - i, flip_index_x = x_d + i; flip_index_y <= y_d&&flip_index_x >= x_d; flip_index_y++,flip_index_x--)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = BLACK;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_left_n >= 0 && y_up_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #7 left up
					if (game_piece[y_up_n*horizontal_dimension + x_left_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; (y_d + i <= vertical_dimension) && (x_d - i >= 0); i++)
						{
							if ((y_d + i)*horizontal_dimension + (x_d - i) >= 0 && (y_d + i)*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + (x_d - i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i, flip_index_x = x_d - i; flip_index_y >= y_d&&flip_index_x <= x_d; flip_index_y--, flip_index_x++)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = BLACK;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_right_n >= 0 && y_up_n*horizontal_dimension + x_right_n<horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #8 right up
					if (game_piece[y_up_n*horizontal_dimension + x_right_n] == WHITE) // nearest neighbor is white
					{
						for (int i = 2; (y_d + i <= vertical_dimension) && (x_d + i <= horizontal_dimension); i++)
						{
							if ((y_d + i)*horizontal_dimension + (x_d + i) >= 0 && (y_d + i)*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + (x_d + i)] == BLACK) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i, flip_index_x = x_d + i; flip_index_y >= y_d&&flip_index_x >= x_d; flip_index_y--, flip_index_x--)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != BLACK)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = BLACK;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}
			}

			// check for player_2
			if (currentPlayer == player_2) // WHITE - current
			{
				if (y_down_n*horizontal_dimension + x_d >= 0 && y_down_n*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #1 down
					if (game_piece[y_down_n*horizontal_dimension + x_d] == BLACK) // nearest neighbor is black
					{
						for (int i = 2; y_d - i >= 0; i++)
						{
							if ((y_d - i)*horizontal_dimension + x_d >= 0 && (y_d - i)*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + x_d] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d - i; flip_index_y <= y_d; flip_index_y++)
									{
										if (flip_index_y*horizontal_dimension + x_d >= 0 && flip_index_y*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + x_d] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + x_d] = WHITE;
										};
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + x_d] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_d >= 0 && y_up_n*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #2 up
					if (game_piece[y_up_n*horizontal_dimension + x_d] == BLACK) // nearest neighbor is black
					{
						for (int i = 2; y_d + i <= vertical_dimension; i++)
						{
							if ((y_d + i)*horizontal_dimension + x_d >= 0 && (y_d + i)*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + x_d] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i; flip_index_y >= y_d; flip_index_y--)
									{
										if (flip_index_y*horizontal_dimension + x_d >= 0 && flip_index_y*horizontal_dimension + x_d < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + x_d] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + x_d] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + x_d] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_d*horizontal_dimension + x_left_n >= 0 && y_d*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #3 left
					if (game_piece[y_d*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is black
					{
						for (int i = 2; x_d - i >= 0; i++)
						{
							if (y_d*horizontal_dimension + (x_d - i) >= 0 && y_d*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[y_d*horizontal_dimension + (x_d - i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_x = x_d - i; flip_index_x <= x_d; flip_index_x++)
									{
										if (y_d*horizontal_dimension + flip_index_x >= 0 && y_d*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[y_d*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[y_d*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[y_d*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_d*horizontal_dimension + x_right_n >= 0 && y_d*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #4 right
					if (game_piece[y_d*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is black
					{
						for (int i = 2; x_d + i <= horizontal_dimension; i++)
						{
							if (y_d*horizontal_dimension + (x_d + i) >= 0 && y_d*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[y_d*horizontal_dimension + (x_d + i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_x = x_d + i; flip_index_x >= x_d; flip_index_x--)
									{
										if (y_d*horizontal_dimension + flip_index_x >= 0 && y_d*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[y_d*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[y_d*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[y_d*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_down_n*horizontal_dimension + x_left_n >= 0 && y_down_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #5 left down
					if (game_piece[y_down_n*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is white
					{
						for (int i = 2; (y_d - i >= 0) && (x_d - i >= 0); i++)
						{
							if ((y_d - i)*horizontal_dimension + (x_d - i) >= 0 && (y_d - i)*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + (x_d - i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d - i, flip_index_x = x_d - i; flip_index_y <= y_d&&flip_index_x <= x_d; flip_index_y++, flip_index_x++)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}

				}

				if (y_down_n*horizontal_dimension + x_right_n >= 0 && y_down_n*horizontal_dimension + x_right_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #6 right dwon
					if (game_piece[y_down_n*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is white
					{
						for (int i = 2; (y_d - i >= 0) && (x_d + i <= horizontal_dimension); i++)
						{
							if ((y_d - i)*horizontal_dimension + (x_d + i) >= 0 && (y_d - i)*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d - i)*horizontal_dimension + (x_d + i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d - i, flip_index_x = x_d + i; flip_index_y <= y_d&&flip_index_x >= x_d; flip_index_y++, flip_index_x--)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d - i)*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_left_n >= 0 && y_up_n*horizontal_dimension + x_left_n < horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #7 left up
					if (game_piece[y_up_n*horizontal_dimension + x_left_n] == BLACK) // nearest neighbor is white
					{
						for (int i = 2; (y_d + i <= vertical_dimension) && (x_d - i >= 0); i++)
						{
							if ((y_d + i)*horizontal_dimension + (x_d - i) >= 0 && (y_d + i)*horizontal_dimension + (x_d - i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + (x_d - i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i, flip_index_x = x_d - i; flip_index_y >= y_d&&flip_index_x <= x_d; flip_index_y--, flip_index_x++)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + (x_d - i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}

				if (y_up_n*horizontal_dimension + x_right_n >= 0 && y_up_n*horizontal_dimension + x_right_n<horizontal_dimension*vertical_dimension) // prevent vector run out of range
				{
					// #8 right up
					if (game_piece[y_up_n*horizontal_dimension + x_right_n] == BLACK) // nearest neighbor is white
					{
						for (int i = 2; (y_d + i <= vertical_dimension) && (x_d + i <= horizontal_dimension); i++)
						{
							if ((y_d + i)*horizontal_dimension + (x_d + i) >= 0 && (y_d + i)*horizontal_dimension + (x_d + i) < horizontal_dimension*vertical_dimension) // prevent vector run out of range
							{
								if (game_piece[(y_d + i)*horizontal_dimension + (x_d + i)] == WHITE) // have black piece on this direction
								{
									// do flip
									for (int flip_index_y = y_d + i, flip_index_x = x_d + i; flip_index_y >= y_d&&flip_index_x >= x_d; flip_index_y--, flip_index_x--)
									{
										if (flip_index_y*horizontal_dimension + flip_index_x >= 0 && flip_index_y*horizontal_dimension + flip_index_x < horizontal_dimension*vertical_dimension) // prevent vector run out of range
										{
											if (game_piece[flip_index_y*horizontal_dimension + flip_index_x] != WHITE)
												game_piece[flip_index_y*horizontal_dimension + flip_index_x] = WHITE;
										}
									}
									flip_check++;
								}
								else if (game_piece[(y_d + i)*horizontal_dimension + (x_d + i)] == EMPTY) // not contiguous in this direction
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	if (flip_check == 0)
		return false;
	else
		return true;
}