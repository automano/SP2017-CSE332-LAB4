// common.h
// Author: Zhening Li E-mail: zhening.li@wustl.edu
// Purpose: 
//          Declare an enumeration for the different array indices that are relevant to my program
//          Declare an enumeration for the different success and failure values my program
//          Declare common functions 
#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ARGUMENT_0 2
#define ARGUMENT_1 3
#define ARGUMENT_2 4

enum ArrayIndices
{
	PROGRAM_NAME,
	GAME_NAME,
	BOARD_SIZE,
	LOWEST_VALUE_PIECE,
	CDM_ARGUMENTS_NUMBER
};


enum ProgramStatus
{
	SUCCESS,
	STALEMATE,
	BAD_ARGUMENT_FORMAT,
	PLAYER_QUIT,
	INVALID_USER_INPUT,
	INVALID_MOVE
};

int UsageMessage(char * program_name, char * promote);
void LowerCase(string &temp);
bool is_numeric(char *string);
