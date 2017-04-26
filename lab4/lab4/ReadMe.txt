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

// Test #3 