// MagicSquareGame.cpp
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: 

#include "stdafx.h"
#include "GameBase.h"
#include "MagicSquareGame.h"
#include "common.h"

/*
 * Outside your Magic Square game class, declare and define an insertion operator (operator<<) that takes a reference to an ostream 
 * and a reference to a const Magic Square class object as parameters, and returns the ostream reference that was passed in (that 
 * allows the operator to be called repeatedly on the same ostream object as in cout << magic_square_game << endl;). Inside your Magic 
 * Square game class, declare the insertion operator to be a friend so that it can access the private member variables of the game object. 
 * The operator should print out the current state of the game board with each piece's display string for squares that have numbered 
 * pieces on them, and spaces for empty squares, with labels on the axes, and a list of the available pieces to play.
 */
// Adapted from NineAlmondsGame.cpp
ostream & operator<<(ostream &os, const MagicSquareGame &game_board) {
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
	os << endl<<endl;

	// print a list of the available pieces to play
	os << "Available pieces: ";//print out the updated available pieces list
	for (auto it = game_board.available_pieces.begin(); it != game_board.available_pieces.end(); ++it) {
		os << *it << " ";
	}
	os << endl;

	return os;
}

/*
* Initialize the game board
* - The game board should be a 3 by 3 square (for extra credit you can generalize this to an n by n square).
* - There are 9 game pieces in the game (or if you do the extra credit portion there would be n2 pieces where 
* n is the number of squares on each edge of the board), and each piece has a name that is the same as its textual 
* representation on the terminal screen when the board is printed and corresponds to a unique integer value between 1 and 9 
* (for example the first piece would have name "1" and would be printed as "1" and would have value 1 when squares of the board are summed up, etc.).
*/
MagicSquareGame::MagicSquareGame() { // Constructor 

	ifstream ifs(gameName + ".txt");
	if (ifs.is_open()) // game file exists
	{
		string firstline = "";
		getline(ifs, firstline);
		if (firstline == "NO DATA")
		{
			// new game - default constructor
			game_turns_count = 0; // set game turns to 0
			horizontal_dimension = 3;
			vertical_dimension = 3;
			longest_piece_length = 0;
			available_pieces.resize(horizontal_dimension*vertical_dimension);
			game_piece.resize(horizontal_dimension*vertical_dimension);
			// Init game board
			for (int y = 0; y < vertical_dimension; y++)
			{
				for (int x = 0; x < horizontal_dimension; x++)
				{
					game_piece[y*horizontal_dimension + x] = BLANK;
					if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
						// updated longest_piece_length if needed whenever a piece is added to the board
						longest_piece_length = game_piece[y*horizontal_dimension + x].length();
				}
			}

			// Init available pieces value vector
			for (unsigned int i = 0; i < available_pieces.size(); i++) {
				available_pieces[i] = i + 1;
			}

			int total_sum = 0;
			for (unsigned int i = 0; i < available_pieces.size(); i++)
			{
				total_sum += available_pieces[i];
			}

			//compute the magic number
			magic_number = total_sum / horizontal_dimension;
			ifs.close();
		}
		else if (firstline == "MagicSquare")
		{
			// saved game default constructor
			// default parameters
			horizontal_dimension = 3;
			vertical_dimension = 3;

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
			// get the avaliable piece from gamefile
			// Adapted from http://stackoverflow.com/questions/43241434/istringstream-from-getline-return-double-for-last-element-in-line
			string available_pieces_line;
			int each_available_pieces;
			while (getline(ifs, available_pieces_line)) {
				stringstream iss(available_pieces_line);
				while (iss>> each_available_pieces) {
					available_pieces.push_back(each_available_pieces);
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
		// new game - default constructor
		game_turns_count = 0; // set game turns to 0
		horizontal_dimension = 3;
		vertical_dimension = 3;
		longest_piece_length = 0;
		available_pieces.resize(horizontal_dimension*vertical_dimension);
		game_piece.resize(horizontal_dimension*vertical_dimension);
		// Init game board
		for (int y = 0; y < vertical_dimension; y++)
		{
			for (int x = 0; x < horizontal_dimension; x++)
			{
				game_piece[y*horizontal_dimension + x] = BLANK;
				if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
					// updated longest_piece_length if needed whenever a piece is added to the board
					longest_piece_length = game_piece[y*horizontal_dimension + x].length();
			}
		}

		// Init available pieces value vector
		for (unsigned int i = 0; i < available_pieces.size(); i++) {
			available_pieces[i] = i + 1;
		}

		int total_sum = 0;
		for (unsigned int i = 0; i < available_pieces.size(); i++)
		{
			total_sum += available_pieces[i];
		}

		//compute the magic number
		magic_number = total_sum / horizontal_dimension;
	}
}

// Extra Credit
MagicSquareGame::MagicSquareGame(int board_size) {
	// Generalize game board depends on commend line input --- an n by n square
	game_turns_count = 0; // set game turns to 0
	horizontal_dimension = board_size;
	vertical_dimension = board_size;
	longest_piece_length = 0;
	available_pieces.resize(horizontal_dimension*vertical_dimension);
	game_piece.resize(horizontal_dimension*vertical_dimension);
	// Init game board
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			game_piece[y*horizontal_dimension + x] = BLANK;
			if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
				// updated longest_piece_length if needed whenever a piece is added to the board
				longest_piece_length = game_piece[y*horizontal_dimension + x].length();
		}
	}

	// Init available pieces value vector
	for (unsigned int i = 0; i < available_pieces.size(); i++) {
		available_pieces[i] = i + 1;
	}

	int total_sum = 0;
	for (unsigned int i = 0; i < available_pieces.size(); i++)
	{
		total_sum += available_pieces[i];
	}

	//compute the magic number
	magic_number = total_sum / horizontal_dimension;
}

MagicSquareGame::MagicSquareGame(int board_size, int min_start) {
	// Generalize game board depends on commend line input --- an n by n square
	game_turns_count = 0; // set game turns to 0
	horizontal_dimension = board_size;
	vertical_dimension = board_size;
	longest_piece_length = 0;
	available_pieces.resize(horizontal_dimension*vertical_dimension);
	game_piece.resize(horizontal_dimension*vertical_dimension);

	// Init game board
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			game_piece[y*horizontal_dimension + x] = BLANK;
			if (game_piece[y*horizontal_dimension + x].length() > longest_piece_length)
				// updated longest_piece_length if needed whenever a piece is added to the board
				longest_piece_length = game_piece[y*horizontal_dimension + x].length();
		}
	}

	// Init available pieces value vector 
	int min = min_start; // minimum start value 
	for (unsigned int i = 0; i < available_pieces.size(); i++) {
		available_pieces[i] = min + i;
	}

	int total_sum = 0;
	for (unsigned int i = 0; i < available_pieces.size(); i++)
	{
		total_sum += available_pieces[i];
	}

	//compute the magic number
	magic_number = total_sum / horizontal_dimension;
}


/*
 * Method play()
 * Override the base class print() method and define it a simply inserting *this into an ostream (so that it uses the insertion
 * operator for that class, which is described above)
 */
void MagicSquareGame::print() {
	cout << *this << endl;
}

/*
 * Method done() 
 * Takes no parameters (other than the this pointer that's passed implicitly to all non-static methods andoperators) 
 * and has a bool return type. The method should return true if every square contains a piece and the sum of the integer 
 * values of the pieces along every diagonal, row, or column is the same (as illustrated at http://en.wikipedia.org/wiki/Magic_square
 * this would be 15 for the basic version of the game); otherwise the method should return false.
 */
bool MagicSquareGame::done() {
	if (this->no_more_move()) // check if every square contains a piece 
	{
		// check the sum of each row 
		for (int y = 0; y < vertical_dimension; y++)
		{
			int sum_temp = 0;
			for (int x = 0; x < horizontal_dimension; x++)
			{
				sum_temp += stoi(game_piece[y*horizontal_dimension + x]);
			}
			if (sum_temp != magic_number)
			{
				return false;
			}
		}

		// check the sum of each column
		for (int x = 0; x < horizontal_dimension; x++) 
		{
			int sum_temp = 0;
			for (int y = 0; y < vertical_dimension; y++) 
			{
				sum_temp += stoi(game_piece[y*horizontal_dimension + x]);
			}
			if (sum_temp != magic_number)
			{
				return false;
			}
		}

		// check the sum of diagonal
		int sum_temp = 0;
		for (int x = 0; x < horizontal_dimension; x++) 
		{
			
			for (int y = 0; y < vertical_dimension; y++) 
			{
				if (x == y)
				{
					sum_temp += stoi(game_piece[y*horizontal_dimension + x]);
				}
			}
		}
		if (sum_temp != magic_number)
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Method stalemate() 
 * Takes no parameters (other than the this pointer that's passed implicitly to all non-static methodsand operators) 
 * and has a bool return type. The method should return true if every square contains a piece and the sum of the integer 
 * values of the pieces along any diagonal, row, or column is different than the sum of the pieces along any other diagonal, 
 * row, or column; otherwise the method should return false.
 */
bool MagicSquareGame::stalemate() {
	if (this->no_more_move()) 
	{
		if (this->done()) // done() returns true
			return false;
		else // no more valid move
			return true;
	}
	else // still have valid move 
		return false;
}

/*
* Define prompt() method for MagicSquare Game
* Adapted from lab3
* Modify your Magic Square and Nine Almonds games so that if the player chooses to quit, the game asks them whether or not they want to save the current game. If the player answers yes, the game should use an ofstream to open up a file that has the same name as the game, output a line with the name of the game as the first line of the file, then output the current state of the game (in a manner that the program can read back in to resume the game - see next), and then close the file before the program ends. How you choose to format the files is up to you, but you should please document your aproach in your ReadMe.txt file.
If the player answers no, the game should again open up a file with the same name as the game, but then output something specific that cannot be confused with a valid game state (say, a single blank line, or something like "NO DATA") to indicate that no state was saved for that game, and then close the file before the program ends.
*/
int MagicSquareGame::prompt(unsigned int &x, unsigned int &y) {
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

					for (unsigned int x = 0; x < available_pieces.size(); x++)
					{
						ofs << available_pieces[x] << endl;
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
* Provide an overloaded public virtual (non-static) version of the prompt() method for MagicSquare Game
* Takes a single reference to an unsigned integer and has a void return type. The method
* should (repeatedly if necessary) prompt the user to type a line that is either "quit" or the
* value of one of the available (unplayed) pieces. If the user inputs "quit" the method
* should throw an exception (that the program's main function must catch if it is not
* caught before then). If the user inputs a string with the value of an available piece, the
* method should extract the value into the unsigned integer parameter and return.
*/
int MagicSquareGame::prompt(unsigned int &x) {
	cout << "Enter available piece <x> or type <quit> to quit this game." << endl;
	int output;
	string input;
	LowerCase(input);
	while (cin >> input) {
		if (!input.compare("quit"))  // user type <quit>
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
					// write data for MagicSquare Game
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

					for (unsigned int x = 0; x < available_pieces.size(); x++)
					{
						ofs << available_pieces[x] << endl;
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
		else // user type <x>
		{
			stringstream ss;
			ss << input;
			if (ss >> x)
			{
				vector<int>::iterator it = find(available_pieces.begin(), available_pieces.end(), x);
				if (it != available_pieces.end())  // if the input piece is in the list of available pieces
				{
					output = SUCCESS;
					break;
				}
				else // if the input piece is not in the list of available pieces
				{
					cout << "Your input piece is not available. Choose another one!" << endl;
					cout << "Enter coordinates <x> or type <quit> to quit this game." << endl;
					continue;
				}
			}
		}
		// other invalid user input
		cout << "Invalid user input." << endl;
		cout << "Enter coordinates <x> or type <quit> to quit this game." << endl;
	}
	return output;
}

/* 
 * Method turn()
 * Takes no parameters and has an appropriate return type. The method should (repeatedly if necessary) call the
 * overloaded prompt() method to obtain coordinates for an empty square on the board and the value of an available piece to play on that square.
 */
int MagicSquareGame::turn() {
	// square coordinates
	unsigned int x_o = 0;
	unsigned int y_o = 0;
	unsigned int piece = 0;
	cout << "----- Choose square -----" << endl;
	if ((this->prompt(x_o, y_o) == SUCCESS))
	{
		if (this->validmove(x_o, y_o))
		{
			cout << "----- Choose piece -----" << endl;
			if ((this->prompt(piece) == SUCCESS))
			{

				// delete the chosen piece from the available pieces list
				// Adapted from http://www.cplusplus.com/reference/vector/vector/erase/
				vector<int>::iterator it = find(available_pieces.begin(), available_pieces.end(), piece);
				available_pieces.erase(it);

				// Add the chosen piece into game board
				stringstream ss;
				ss << piece;
				string str = ss.str();
				game_piece[y_o*horizontal_dimension+x_o] = str;

			    // print current game board
				cout << endl;
				this->print();

				return SUCCESS;
			}
			else {
				return PLAYER_QUIT;
			}
		}
		else
		{
			cout << "Error: Invalid move!" << endl
				<< "The square you choose should be empty!" << endl;
			return INVALID_MOVE;
		}
	}
	else {
		return PLAYER_QUIT;
	}
}

/*
 * Function no_more_move()
 * check if every square contains a piece 
 */
bool MagicSquareGame::no_more_move() {
	for (int y = 0; y < vertical_dimension; y++)
	{
		for (int x = 0; x < horizontal_dimension; x++)
		{
			if (game_piece[y*horizontal_dimension + x] == BLANK)
				return false;
		}
	}
	return true;
}

bool MagicSquareGame::validmove(unsigned int x_o, unsigned int y_o)
{
	if (game_piece[y_o*horizontal_dimension + x_o]==BLANK)
		return true;
	else
		return false;
}

