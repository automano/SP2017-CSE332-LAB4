// ReversiGame.h
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

const string BLACK = "X"; // black game piece - who moves first
const string WHITE = "O"; // white game piece - who moves second

// Derived class ReversiGame from base class GameBase
class ReversiGame :public GameBase {
	friend ostream & operator<<(ostream &os, const ReversiGame &game_board); // the ostream insertion operator
private:
	string player_1; // play who moves first (at the even turn start at turn 0) - black - X
	string player_2; // player who moves second (at the odd turn) - white - O
public:
	ReversiGame(string player_black, string player_white);
	~ReversiGame() {} // 
	virtual void print(); // virtual print() method
	virtual bool done();  // virtual done() method
	virtual bool stalemate();  // virtual draw() method
	virtual int turn();   // virtual turn() method
	bool hasValidmove(string currentPlayer); // check if here valid move on the game board
	bool makeFlip(string currentPlayer, int x_d, int y_d); // make move and filpe

	// Adapted from http://en.cppreference.com/w/cpp/language/copy_constructor (3)
	// prevent the use of copy constructor
	ReversiGame(const ReversiGame &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (4)
	// prevent the use of copy assignment operator 
	ReversiGame & ReversiGame :: operator= (const ReversiGame &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/move_constructor (3)
	// prevent the use of move constructor
	ReversiGame(ReversiGame &&) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (3)
	// prevent the use of move assignment operator
	ReversiGame & ReversiGame :: operator= (ReversiGame &&) = delete;
};