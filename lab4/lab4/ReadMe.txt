// Name and Student ID
Zhening Li 445612

// Lab Number
Lab 4

// Purpose: 

// Error 
// #1 
when I modity the lab4.cpp and Gamebase.cpp files, I throw enum types but I try to catch them by 

catch(int error){...}

I confused the int and enum types. Cause "Unhandled Exception" error.

Solution: catch (ProgramStatus error){...}

// #2
Duplicate elements of last call occur when call getline and stringstream.

solution: 
http://stackoverflow.com/questions/43241434/istringstream-from-getline-return-double-for-last-element-in-line

// #3
When run hasValidMove(), vector game_piece go out of range.

solution: add if(index>=0&&index<63){...}

// #4
I implement makeFlip() by change code in hasValidMove(), but this make the program can only flip in one direction, then it will return back.

solution:
After flip happened, not return success but add a flip counter. If this counter is not 0 then return success.


// Test (You can search "Test" for quick locate each test case )

// Test #1 
- Before proceeding to the next part of the assignment, please make sure your Nine Almonds and Magic Square games still perform correctly.
- In this part I only test the bad format arguments cases. Other cases are the same with lab3.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe
Error: wrong number of arguments (too many or too few)!
Usage: lab4.exe <NineAlmonds>
       lab4.exe <MagicSquare>
       lab4.exe <MagicSquare> <arbitrary_board_size>
       lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe nine
Error: Wrong game name input!
Usage: lab4.exe <NineAlmonds>
       lab4.exe <MagicSquare>
       lab4.exe <MagicSquare> <arbitrary_board_size>
       lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquar 1 2 3
Error: wrong number of arguments (too many or too few)!
Usage: lab4.exe <NineAlmonds>
       lab4.exe <MagicSquare>
       lab4.exe <MagicSquare> <arbitrary_board_size>
       lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare a b
Error: game board size should be numeric!
Usage: lab4.exe <NineAlmonds>
       lab4.exe <MagicSquare>
       lab4.exe <MagicSquare> <arbitrary_board_size>
       lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>

// Test: good format arguments - still works
D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare 1 2
0
X 0

Available pieces: 2

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Player quit game!
Total turns: 0.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Player quit game!
Total turns: 0.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Player quit game!
Total turns: 0.

// Test #2
- Before proceeding to the rest of the assignment, please make sure your Nine Almonds and Magic Square games perform correctly, including the ability to suspend and resume them mid-play.

//Test: Ninealmonds

// game file name: NineAlmonds.txt
// storage format
line 1: gamename
line 2: game turns when player quit
line 3: longest piese length
line 4-28: game piece 

// Test: Ninealmonds - run the game for the first time - create file and gameboard correctly

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// file: NineAlmonds.txt
NO DATA

// Test: Ninealmonds - quit game and save game then re-open - meet lab requirments

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.
2,2
----- Ending square -----
Enter coordinates <x,y> or type <quit> to quit this game.
2,4
4     A
3   A   A
2   A   A
1   A A A
0
X 0 1 2 3 4


2,2 to 2,4

Continue this turn(YyNn)?
n
----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game ? (YyNn)
y
Game Saved!
Player quit game!
Total turns: 1.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4     A
3   A   A
2   A   A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// file: NineAlmonds.txt
NineAlmonds
1
1
 
 
 
 
 
 
A
A
A
 
 
A
 
A
 
 
A
 
A
 
 
 
A
 
 
//end file

// Test: Ninealmonds - quit game and do not save game then re-open - meet lab requirments

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4     A
3   A   A
2   A   A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game ? (YyNn)
n
Player quit game!
Total turns: 1.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe NineAlmonds
4
3   A A A
2   A A A
1   A A A
0
X 0 1 2 3 4

----- Beginning square -----
Enter coordinates <x,y> or type <quit> to quit this game.

//Test: MagicSquare

// game file name: MagicSquare.txt
// storage format
line 1: gamename
line 2: game turns when player quit
line 3: longest piese length
line 4-12: game piece
line 12-end: avaliable piece

// Test: MagicSquare - run the game for the first time - create file and gameboard correctly

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// file: NineAlmonds.txt
NO DATA

// Test: Ninealmonds - quit game and save game then re-open - meet lab requirments

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
1,1
----- Choose piece -----
Enter available piece <x> or type <quit> to quit this game.
5

2
1   5
0
X 0 1 2

Available pieces: 1 2 3 4 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game ? (YyNn)
y
Game Saved!
Player quit game!
Total turns: 1.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1   5
0
X 0 1 2

Available pieces: 1 2 3 4 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// file: MaigcSquare.txt
MagicSquare
1
1
 
 
 
 
5
 
 
 
 
1
2
3
4
6
7
8
9
//end file

// Test: MagicSquare - quit game and do not save game then re-open - meet lab requirments
D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1   5
0
X 0 1 2

Available pieces: 1 2 3 4 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game ? (YyNn)
n
Player quit game!
Total turns: 1.

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe MagicSquare
2
1
0
X 0 1 2

Available pieces: 1 2 3 4 5 6 7 8 9

----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// file: NineAlmonds.txt
NO DATA

// Test #3 - Adding a Multi-Player Game - Reversi Game Test

// Test #3.1 - bad format argument - no player names input

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe Reversi
Error: wrong number of arguments (too many or too few)!
Usage:lab4.exe <NineAlmonds>
      lab4.exe <MagicSquare>
      lab4.exe <MagicSquare> <arbitrary_board_size>
      lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>
      lab4.exe <Reversi> <first_player_name> <second_player_name>

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe Reversi li
Error: wrong number of arguments (too many or too few)!
Usage:lab4.exe <NineAlmonds>
      lab4.exe <MagicSquare>
      lab4.exe <MagicSquare> <arbitrary_board_size>
      lab4.exe <MagicSquare> <arbitrary_board_size> <start_piece>
      lab4.exe <Reversi> <first_player_name> <second_player_name>

// Test #3.2 - good format argument - init game board successfully

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe Reversi li chen
7
6
5
4       O X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

----- Turn 0 li's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.

// Test #3.3 - user quit but not save game

D:\Project\CSE504\lab4\lab4\Debug>lab4.exe Reversi li chen
7
6
5
4       O X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

----- Turn 0 li's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game? (YyNn)
n
Player quit game!
Total turns: 1.

// Reversi.txt file
NO DATA

// Test #3.4 - user quit and want to save game
D:\Project\CSE504\lab4\lab4\Debug>lab4.exe Reversi li chen
7
6
5
4       O X
3       X O
2
1
0
X 0 1 2 3 4 5 6 7

----- Turn 0 li's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
quit
Would you like to save the current game? (YyNn)
y
Current game board saved!
Player quit game!
Total turns: 1.

// Reversi.txt file
Reversi
0
1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
X
O
 
 
 
 
 
 
O
X
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
// Reversi.txt file end

// Reversi.txt file format guide
line 1: game name
line 2: how many turns
line 3: longest piece length
line 4-67: game piece

// Test #3.5 complete game

// only show last three turns here

----- Turn 57 chen's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
7,5
7 O O O O O O O
6 X X X X X X O
5 X X X X O O O O
4 O X O O X X X O
3 X X O X X X X X
2 X X O X X X X X
1 X X X X X X X X
0 X X X X X X X X
X 0 1 2 3 4 5 6 7

----- Turn 58 li's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
7,6
7 O O O O O O O
6 X X X X X X X X
5 X X X X O O X X
4 O X O O X X X X
3 X X O X X X X X
2 X X O X X X X X
1 X X X X X X X X
0 X X X X X X X X
X 0 1 2 3 4 5 6 7

----- Turn 59 chen's turn -----
----- Choose square -----
Enter coordinates <x,y> or type <quit> to quit this game.
7,7
7 O O O O O O O O
6 X X X X X X O X
5 X X X X O O X X
4 O X O O O X X X
3 X X O O X X X X
2 X X O X X X X X
1 X X X X X X X X
0 X X X X X X X X
X 0 1 2 3 4 5 6 7

BLACK: 46
WHITE: 18
Congratulations to you! li You win!
Total turns: 60.
BLACK: 46
WHITE: 18
Congratulations to you! li You win!
Total turns: 60. // A bug here. done() method run twice due to the while loop check twice and if statement.

// Documenting Copy Control Design Decisions

- I disable copy constructor, move constructor, copy-assignment operator and move-assignment operator in both base class and derived classes by using "=delete"(c++11). 

- Because my implemention really do not need these constructors and opeators. I do not want to give access to user for allocating and messing up game states. 
This may reinforce the robustness and the independence among various games. 

- Actually, most classes do not need to copy the constructor nor need to assign an operator. In many cases, a pointer or a reference is actually enough, and there 
will be better performance. For example, you can pass a pointer, instead of passing in a value, you can also save the object pointer in the STL container, rather
than the object itself.

- But, I allow the destructor existence which allow me to release the storage space whenever the game is finished.