##### Tetris
This was coded during my c++ class. We were only given the Task with no direct instructions



### Project Structure

    Tetris.cpp/.h - Game logic and main loop

    Tetrominos.cpp/.h - Tetromino shapes, movement, and rotation

    TerminalManager.h - Abstract interface for terminal drawing/input

    NcursesTerminalManager.cpp/.h - Ncurses-based implementation for real terminal

    MockTerminalManager.cpp/.h - Mock for unit testing

    TetrisTest.cpp - Unit tests for game mechanics

What I Learned

    Object-Oriented Design: How to design classes and interfaces for modular, testable code (e.g., TerminalManager abstraction)

.

Game Logic: Implementing movement, collision detection, row clearing, and scoring

.

Terminal Graphics: Drawing and refreshing a grid-based game in the terminal using ncurses and custom color logic

.

Unit Testing: Writing tests for movement, rotation, scoring, and boundary conditions

.

Input Handling: Managing real-time keyboard input and custom key bindings
