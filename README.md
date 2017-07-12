# SP2017-CSE332-LAB4

This lab is intended to extend your use of C++ language features from the previous labs, and to give you experience with them, including:
- interacting with a single instance of the game currently in play
- allowing games to be saved and resumed
- implementing a multi-player game with alternating turns
- documenting your design decisions regarding copy control

To implement this lab, you will extend your C++ program from the previous lab so that it in addition to playing the Nine Almonds and Magic Square games from the previous lab assignment, it also can play a multi-player Reversi game. You will also modify your game base class and your main program so that (1) a single instance of the current game is accessed through a single static method, and (2) if a player quits a game they will have the option of saving (and later resuming) the state of the game.
