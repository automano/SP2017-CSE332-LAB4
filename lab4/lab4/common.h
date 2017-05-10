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
	WRONG_GAME_NAME,
	INVALID_BOARD_SIZE,
	INVALID_LOWEST_VALUE_PIECE,
	PLAYER_QUIT,
	INVALID_USER_INPUT,
	INVALID_MOVE,
	NULLPTR,
	NOT_NULL_PTR,
	BAD_ALLOC,
	WRONG_NUMBER_ARGUMENTS,
	OPEN_FILE_FAILED,
	BAD_FORMAT_LINE,
	SKIP_CURRENT_TURN
};

int UsageMessage(char * program_name, char * promote);
void LowerCase(string &temp);
bool is_numeric(char *string);
