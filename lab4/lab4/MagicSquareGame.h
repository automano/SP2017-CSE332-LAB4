// MagicSquareGame.h
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: Declare derived class MagicSquareGame
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip> // std::setw
#include <fstream>
using namespace std;

const string BLANK = " ";

// Derived class MagicSquareGame from base class GameBase
class MagicSquareGame :public GameBase {
	friend ostream & operator<<(ostream &os, const MagicSquareGame &game_board); // the ostream insertion operator
private:
	vector<int> available_pieces; // store a list of the available pieces to play
	int magic_number = 0; // magic number
public:
	MagicSquareGame();
	~MagicSquareGame() {}
	MagicSquareGame(int board_size);
	MagicSquareGame(int board_size, int min_start);
	virtual void print(); // virtual print() method
	virtual bool done();  // virtual done() method
	virtual bool stalemate();  // virtual draw() method
	virtual int prompt(unsigned int &x, unsigned int &y); // overload pormpt
	virtual int prompt(unsigned int &x); // an overloaded public virtual (non-static) version of the prompt() method for MagicSquareGame
	virtual int turn();   // virtual turn() method
	bool no_more_move(); // function check if every square contains a piece 
	bool validmove(unsigned int x_o, unsigned int y_o); // function check if choen square is empty
	
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_constructor (3)
	// prevent the use of copy constructor
	MagicSquareGame (const MagicSquareGame &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (4)
	// prevent the use of copy assignment operator 
	MagicSquareGame & MagicSquareGame :: operator= (const MagicSquareGame &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/move_constructor (3)
	// prevent the use of move constructor
	MagicSquareGame (MagicSquareGame &&) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (3)
	// prevent the use of move assignment operator
	MagicSquareGame & MagicSquareGame :: operator= (MagicSquareGame &&) = delete;
};