// NineAlmondsGame.h
// Author: Zhening Li  Email: zhening.li@wustl.edu
// Purpose: Declare derived class NineAlmondsGame
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip> // std::setw
using namespace std;

const string ALMOND = "A";
const string EMPTY = " ";

// Derived class NineAlmondsGame from base class GameBase
class NineAlmondsGame :public GameBase {
	
	friend ostream & operator<<(ostream &os, const NineAlmondsGame &game_board); // the ostream insertion operator
public:
	NineAlmondsGame();
	virtual void print(); // virtual print() method
	virtual bool done();  // virtual done() method
	virtual bool stalemate();  // virtual draw() method
	virtual int turn();   // virtual turn() method
	bool validmove(unsigned int x_o, unsigned int y_o, unsigned int x_d, unsigned int y_d);
};
