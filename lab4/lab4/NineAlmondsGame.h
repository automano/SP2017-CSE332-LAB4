// NineAlmondsGame.h
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: Declare derived class NineAlmondsGame
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip> // std::setw
#include <fstream>
using namespace std;

const string ALMOND = "A"; // Almond game piece

// Derived class NineAlmondsGame from base class GameBase
class NineAlmondsGame :public GameBase {
	
	friend ostream & operator<<(ostream &os, const NineAlmondsGame &game_board); // the ostream insertion operator
public:
	NineAlmondsGame();
	~NineAlmondsGame() {}
	virtual void print(); // virtual print() method
	virtual bool done();  // virtual done() method
	virtual bool stalemate();  // virtual draw() method
	virtual int turn();   // virtual turn() method
	bool validmove(unsigned int x_o, unsigned int y_o, unsigned int x_d, unsigned int y_d);

	// Adapted from http://en.cppreference.com/w/cpp/language/copy_constructor (3)
	// prevent the use of copy constructor
	NineAlmondsGame (const GameBase &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (4)
	// prevent the use of copy assignment operator 
	NineAlmondsGame & NineAlmondsGame :: operator= (const NineAlmondsGame &) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/move_constructor (3)
	// prevent the use of move constructor
	NineAlmondsGame (NineAlmondsGame &&) = delete;
	// Adapted from http://en.cppreference.com/w/cpp/language/copy_assignment (3)
	// prevent the use of move assignment operator
	NineAlmondsGame & NineAlmondsGame :: operator= (NineAlmondsGame &&) = delete;
};
