// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>
#pragma once

#include "./TerminalManager.h"
#include "./Tetrominos.h"
#include <chrono>
#include <gtest/gtest.h>

class Tetris {
public:
  // Constrctor of Tetris
  explicit Tetris(TerminalManager *terminalManager = nullptr, int level = 0,
                  char leftKey = 'a', char rightKey = 's');

  // run game under current logic
  void run();

private:
  // setter for level
  void setLevel(const int arg) { level_ = arg; };

  // setter for Rotation Keys
  void setKeys(char left, char right);

  // sets the fall speed of Tetromino
  void speedAndLevel(bool verbose = false);

  bool updateGame(std::chrono::steady_clock::time_point &lastFallTime,
                  std::chrono::steady_clock::time_point currentTime);

  // Initializes Game
  void initTerminal();

  // Handle Key inputt from player
  bool processUserInput(UserInput userinput);

  // adds Tetromio to Grid with given colors,
  void insertTetro(const IntPairVector &tetroVecs, int color);

  // checks for full rows, (up to 4) and removes them and adjustes the grid
  void CheckHandleFullRows();

  // Switches current and Next Tetromino pointer, so that one can be randomly
  // selected.
  void switchTetromino();

  // calculate Points for given ammount of filled rows
  void calcGamePoints(int rows);

  //_____________________MOVEMENT_____________________

  // validate movement
  // checks: if tetro Cooridnates are out of Bounds (left right, bottom)
  // checks: if Co. match with previously dropped Tetros,
  // reverses movement if it is invalid
  void validateMove(bool spawn = false);

  //_____________________Draw_____________________

  // draws given row on Terminal with int of grid representing the color
  void drawRow(int row) const;

  // print level and rows filled
  void drawLevelAndFilledRows() const;

  // draw border of game, iwann mit parameter?
  void drawBorder() const;

  // draws Tetromino on screen
  void drawTetromino(const IntPairVector &points, int color) const;

  // erase Tetromino on screen (color = 0)
  void eraseTetromino(const IntPairVector &points) const;

  // draws end card when you quit game or loose
  void drawPattern();

  // saves highscore in file
  void saveHighScore();

  // loads highscore from file
  int loadHighScore();

  //___________MEMBERVARIABLES______________________________________________
  // enum to choose movement direction
  TerminalManager *terminalManager_ = nullptr;

  // Member variables for key bindings // default assignments
  char keyRightRotation_ = 's';
  char keyLeftRotation_ = 'a';

  // scrren dimensions
  int numRows_;
  int numCols_;

  //____GAME__FIELD_______________

  // object1 and pointer Tetromino
  Tetrominos Tetro1_;
  Tetrominos *currentTetro = &Tetro1_;

  // object2 falling Tetromino, pointer2 of object2
  Tetrominos Tetro2_;
  Tetrominos *nextTetro = &Tetro2_;

  // next Tetromino Points
  int xnPoint_ = 17;
  int ynPoint_ = 6;

  // border limits
  int x_max_game_ = 12;
  int x_min_game_ = 1;
  int y_max_game_ = 24;
  int y_min_game_ = 4;

  // shift arrays
  int Xshift = x_min_game_ + 1;
  int Yshift = y_min_game_;

  // spawn points
  int xSpawn = x_max_game_ / 2;
  int ySpawn = y_min_game_;

  // Tetromino array limits of game grid
  static const int maxRows_ = 20;
  static const int maxCols_ = 10;

  // Grid of Tetris
  // 0 = Black (empty)
  // 1-7 represent the Tetrominos
  int grid[maxRows_][maxCols_] = {{0}};

  // current level of game
  int level_ = 0;
  // filled rows
  int rowsFilled_ = 0;
  // fall speed
  int fallSpeed = 48;
  // points in game
  int gamePoints_ = 0;

  // GAME INPUTT
  bool quit = false;

  // add more points when full row and arrow down key is pressed
  int times_pressed = 0;
  bool pushedDown_ = false;

  // Highscore
  const std::string highScoreFile = "TetrisHighScore.txt";
  int highScore = 0;

  // Tests
  FRIEND_TEST(Tetris, TetroInsertion);
  FRIEND_TEST(Tetris, FullRows);
  FRIEND_TEST(Tetris, CalculateGamePoints);
  FRIEND_TEST(Tetris, CalculateGamePoints);
  FRIEND_TEST(Tetris, processUserInputQuit);
  FRIEND_TEST(Tetris, processUserInputKEYDOWN);
  FRIEND_TEST(Tetris, processUserInputMoveRight);
  FRIEND_TEST(Tetris, processUserInputMoveLeft);
  FRIEND_TEST(Tetris, processUserInputEdge);
  FRIEND_TEST(Tetris, switchTetromino);
  FRIEND_TEST(Tetris, drawTetromino);
  FRIEND_TEST(Tetris, drawBorder);
  FRIEND_TEST(Tetris, eraseTetromino);
  FRIEND_TEST(Tetris, CheckHandleFullRowsTerminal);
  FRIEND_TEST(Tetris, validateMove);
  FRIEND_TEST(Tetris, timeInterval);
  FRIEND_TEST(Tetris, moveWHILEdrop);
};
