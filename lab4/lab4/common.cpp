// common.cpp
// Author: Zhening Li E-mail: zhening.li@wustl.edu
// Purpose: 
//          Define an enumeration for the different array indices that are relevant to my program
//          Define an enumeration for the different success and failure values my program
//          Define functions (Usage Message, Lowercase)

#include "stdafx.h"
#include "common.h"

const int A_to_a = 32; // 'A'-'a'=32

/**
* Usage Message function
*/
int UsageMessage(char * program_name, char * promote)
{
	cout << promote << endl; // Error Message
	// Usage Message
	cout << "Usage: " << program_name << " " << "<NineAlmonds>" << endl
		 << "       " << program_name << " " << "<MagicSquare>" << endl
		 << "       " << program_name << " " << "<MagicSquare>" << " " << "<arbitrary_board_size>" << endl
		 << "       " << program_name << " " << "<MagicSquare>" << " " << "<arbitrary_board_size>" << " " << "<start_piece>" << endl;
	return SUCCESS;
}

/**
* Function that takes a reference to a C++ style string
* and modifies that string so that all of the alphabetic characters in it become lowercase
*/
void LowerCase(string &temp)
{
	for (unsigned int i = 0;i < temp.length();i++)
	{
		if (temp[i] >= 'A'&&temp[i] <= 'Z')
		{
			temp[i] = temp[i] + A_to_a;
		}
	}
}

/*
 * Function check if input is numberic or not
 * Adapted from http://stackoverflow.com/questions/18154630/c-see-if-argument-is-numeric
 */
bool is_numeric(char *s)
{
	int sizeOfString = strlen(s);
	int iteration = 0;
	bool isNumeric = true;

	while (iteration < sizeOfString)
	{
		if (!isdigit(s[iteration]))
		{
			isNumeric = false;
			break;
		}

		iteration++;

	}

	return isNumeric;;
}