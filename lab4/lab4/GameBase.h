// GameBase.h
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Porpuse: Refactor game class from the previous lab into a base class 
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <fstream>
using namespace std;

/*
 * A base class that contains protected member variables that are common to multiple games 
 */
class GameBase {
protected:
	int horizontal_dimension; //game board dimensions
	int vertical_dimension;
	unsigned int longest_piece_length; // longest display string length of any piece currently on the board
	unsigned int game_turns_count; // store how many turns were played
	vector<string> game_piece; // the container --- C++ style string
	static string gameName; // store current game name for save game file
	static shared_ptr<GameBase> ptr; // a protected static member variable to your game base class that is a shared smart pointer to the game base class 
public:
	GameBase() {}
	~GameBase() {}
	virtual void print() = 0;      // pure virtual print() method
	virtual bool done() = 0;       // pure virtual done() method
	virtual bool stalemate() = 0;  // pure virtual stalemate() method
	virtual int turn() = 0;        // pure virtual turn() method
	virtual int prompt(unsigned int &x, unsigned int &y); // virtual prompt() method for NineAlmondsGame
	virtual int prompt(unsigned int &x); // virtual prompt() method for MagicSquareGame
	int play(); //  play() method
	static shared_ptr<GameBase> instance();  // a public static instance() method
	static void objectAddressPtr(int argc, char * argv[]); //a static method returns a pointer to an object of the base class

	// Adapted from http://en.cppreference.com/w/cpp/language/copy_constructor (3)
	// prevent the use of copy constructor
	GameBase (const GameBase &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (4)
	// prevent the use of copy assignment operator 
	GameBase & GameBase :: operator= (const GameBase &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/move_constructor (3)
	// prevent the use of move constructor
	GameBase (GameBase &&) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (3)
	// prevent the use of move assignment operator
	GameBase & GameBase :: operator= (GameBase &&) = delete;
};
