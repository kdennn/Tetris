// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#include "./Tetris.h"
#include "./Tetrominos.h"
#include "MockTerminalManager.h"
#include <chrono>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>

using IntPair = std::pair<int, int>;
using IntPairVector = std::vector<IntPair>;

// Define some colors
Color red(1.0, 0.0, 0.0);
Color green(0.0, 1.0, 0.0);
Color blue(0.0, 0.0, 1.0);
Color black(0.0, 0.0, 0.0);
Color white(1.0, 1.0, 1.0);
Color yellow(1.0, 1.0, 0.0);
Color cyan(0.0, 1.0, 1.0);
Color magenta(1.0, 0.0, 1.0);
Color gray(0.5, 0.5, 0.5);
Color orange(1.0, 0.5, 0.0);
Color pink(1.0, 0.75, 0.8);
Color brown(0.65, 0.16, 0.16);

// Initialize vector with 12 color pairs
std::vector<std::pair<Color, Color>> colors = {
    {black, white},   // Black foreground, white background
    {red, black},     // Red foreground, black background
    {green, black},   // Green foreground, black background
    {blue, white},    // Blue foreground, white background
    {yellow, black},  // Yellow foreground, black background
    {cyan, black},    // Cyan foreground, black background
    {magenta, black}, // Magenta foreground, black background
    {gray, black},    // Gray foreground, black background
    {orange, black},  // Orange foreground, black background
    {pink, black},    // Pink foreground, black background
    {brown, black},   // Brown foreground, black background
    {white, black}    // White foreground, black background
};

TEST(Tetromino, RotateT) {

  Tetrominos TetroT;
  TetroT.setPivot(5, 5);
  TetroT.setShape(Tetrominos::T);

  IntPairVector original = TetroT.getPoints();

  TetroT.rotate(false);

  IntPairVector expected = {{5, 5}, {5, 4}, {6, 5}, {5, 6}};

  // sort to compare easily
  std::sort(TetroT.getPoints().begin(), TetroT.getPoints().end());
  std::sort(expected.begin(), expected.end());
  std::sort(original.begin(), original.end());

  // test Size
  ASSERT_EQ(TetroT.getPoints().size(), expected.size());

  // test if they are same(meaing a counter clock wise rotation)
  EXPECT_EQ(TetroT.getPoints(), expected);

  // rotate back to see if it reverses correctly
  TetroT.rotate(true);

  // sort to compare easily
  std::sort(TetroT.getPoints().begin(), TetroT.getPoints().end());
  std::sort(original.begin(), original.end());

  EXPECT_EQ(TetroT.getPoints(), original);
}
TEST(Tetromino, RotateI) {
  Tetrominos TetroI;
  TetroI.setPivot(3, 2);
  TetroI.setShape(Tetrominos::I);
  IntPairVector original = TetroI.getPoints();

  TetroI.rotate(true);

  // Assert one turn to the left
  IntPairVector expected = {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
  std::sort(TetroI.getPoints().begin(), TetroI.getPoints().end());
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(TetroI.getPoints(), expected);

  // if right Rotation is called again it should rotate left to Original layout
  TetroI.rotate(true);

  // sort to compare
  std::sort(original.begin(), original.end());
  std::sort(TetroI.getPoints().begin(), TetroI.getPoints().end());
  EXPECT_EQ(TetroI.getPoints(), original);

  // if  in original position and rotateLeft() is called it should rotate right
  TetroI.rotate(true);
  std::sort(TetroI.getPoints().begin(), TetroI.getPoints().end());
  EXPECT_EQ(TetroI.getPoints(), expected);

  // calling left again should Rotate left
  TetroI.rotate(true);
  std::sort(TetroI.getPoints().begin(), TetroI.getPoints().end());
  EXPECT_EQ(TetroI.getPoints(), original);
}
TEST(Tetromino, RotateO) {
  Tetrominos TetroO;
  TetroO.setPivot(2, 1);
  TetroO.setShape(Tetrominos::O);
  IntPairVector original = TetroO.getPoints();

  // after rotation of Square Tetromino there should be no change
  TetroO.rotate(true);

  IntPairVector expected = {{2, 1}, {1, 1}, {1, 2}, {2, 2}};
  std::sort(TetroO.getPoints().begin(), TetroO.getPoints().end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(TetroO.getPoints(), expected);

  TetroO.rotate(false);
  std::sort(TetroO.getPoints().begin(), TetroO.getPoints().end());

  EXPECT_EQ(TetroO.getPoints(), expected);
}

TEST(Tetromino, moveDown) {
  Tetrominos TetroT;
  TetroT.setPivot(5, 5);
  TetroT.setShape(Tetrominos::T);

  TetroT.moveDown();

  IntPairVector expected = {{5, 6}, {4, 6}, {6, 6}, {5, 7}};

  // sort to compare
  std::sort(TetroT.getPoints().begin(), TetroT.getPoints().end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(TetroT.getPoints(), expected);
}
TEST(Tetromino, moveRight) {
  Tetrominos TetroT;
  TetroT.setPivot(5, 5);
  TetroT.setShape(Tetrominos::T);

  TetroT.moveRight();

  IntPairVector expected = {{5, 5}, {6, 5}, {7, 5}, {6, 6}};

  // sort to compare
  std::sort(TetroT.getPoints().begin(), TetroT.getPoints().end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(TetroT.getPoints(), expected);
}
TEST(Tetromino, moveLeft) {
  Tetrominos TetroT;
  TetroT.setPivot(5, 5);
  TetroT.setShape(Tetrominos::T);

  TetroT.moveLeft();

  IntPairVector expected = {{3, 5}, {4, 5}, {5, 5}, {4, 6}};

  // sort to compare
  std::sort(TetroT.getPoints().begin(), TetroT.getPoints().end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(TetroT.getPoints(), expected);
}
TEST(Tetromino, computeShape) {
  Tetrominos Tetro;
  Tetro.setPivot(5, 5);

  // Test for Tetromino I
  Tetro.setShape(Tetrominos::I);
  Tetro.computeShape();
  IntPairVector expectedI = {{3, 5}, {4, 5}, {6, 5}, {5, 5}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedI.begin(), expectedI.end());
  EXPECT_EQ(Tetro.getPoints(), expectedI);

  // Test for Tetromino O
  Tetro.setShape(Tetrominos::O);
  Tetro.computeShape();
  IntPairVector expectedO = {{4, 6}, {4, 5}, {5, 5}, {5, 6}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedO.begin(), expectedO.end());
  EXPECT_EQ(Tetro.getPoints(), expectedO);

  // Test for Tetromino T
  Tetro.setShape(Tetrominos::T);
  Tetro.computeShape();
  IntPairVector expectedT = {{5, 5}, {4, 5}, {6, 5}, {5, 6}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedT.begin(), expectedT.end());
  EXPECT_EQ(Tetro.getPoints(), expectedT);

  // Test for Tetromino S
  Tetro.setShape(Tetrominos::S);
  Tetro.computeShape();
  IntPairVector expectedS = {{6, 5}, {5, 6}, {4, 6}, {5, 5}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedS.begin(), expectedS.end());
  EXPECT_EQ(Tetro.getPoints(), expectedS);

  // Test for Tetromino Z
  Tetro.setShape(Tetrominos::Z);
  Tetro.computeShape();
  IntPairVector expectedZ = {{5, 5}, {4, 5}, {5, 6}, {6, 6}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedZ.begin(), expectedZ.end());
  EXPECT_EQ(Tetro.getPoints(), expectedZ);

  // Test for Tetromino J
  Tetro.setShape(Tetrominos::J);
  Tetro.computeShape();
  IntPairVector expectedJ = {{4, 5}, {6, 6}, {6, 5}, {5, 5}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedJ.begin(), expectedJ.end());
  EXPECT_EQ(Tetro.getPoints(), expectedJ);

  // Test for Tetromino L
  Tetro.setShape(Tetrominos::L);
  Tetro.computeShape();
  IntPairVector expectedL = {{5, 5}, {4, 5}, {6, 5}, {4, 6}};
  std::sort(Tetro.getPoints().begin(), Tetro.getPoints().end());
  std::sort(expectedL.begin(), expectedL.end());
  EXPECT_EQ(Tetro.getPoints(), expectedL);
}
TEST(Tetromino, setRandShape) {
  // test to see that two following Randshapes have about a probability of 1/49
  const int iterations = 10000;
  int sameCount = 0;

  Tetrominos tetromino;
  tetromino.setRandShape();
  int previousColor = tetromino.getColor();

  for (int i = 0; i < iterations; ++i) {
    tetromino.setRandShape();
    int currentColor = tetromino.getColor();

    if (currentColor == previousColor) {
      sameCount++;
    }

    previousColor = currentColor;
  }

  double observedProbability = static_cast<double>(sameCount) / iterations;
  double expectedProbability = 1.0 / 49;

  // 10% margin of error allowed
  ASSERT_NEAR(observedProbability, expectedProbability,
              expectedProbability * 0.10);
}
TEST(Tetromino, revert) {
  Tetrominos Tetromino;
  Tetromino.setPivot(4, 5);
  Tetromino.moveLeft();
  Tetromino.revert();

  IntPairVector original = Tetromino.getPoints();
  std::sort(Tetromino.getPoints().begin(), Tetromino.getPoints().end());
  std::sort(original.begin(), original.end());

  ASSERT_EQ(original, Tetromino.getPoints());
}

//_________________________________________________________________________________________________

TEST(Tetris, TetroInsertion) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Tetrominos TetroT;
  TetroT.setPivot(7, 22);
  TetroT.setShape(Tetrominos::T);

  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  int countLASTROW = 0;
  for (bool val : Game.grid[19]) {
    if (val != 0) {
      countLASTROW += 1;
    }
  }
  int countSECONDLAST = 0;
  for (bool val : Game.grid[18]) {
    if (val != 0) {
      countSECONDLAST += 1;
    }
  }

  ASSERT_EQ(1, countLASTROW);
  ASSERT_EQ(3, countSECONDLAST);
  ASSERT_EQ(3, Game.grid[19][5]);
}
TEST(Tetris, FullRows) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Tetrominos TetroT;
  TetroT.setPivot(4, 23);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(8, 23);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(3, 21);
  TetroT.setShape(Tetrominos::O);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(6, 22);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(11, 22);
  TetroT.setShape(Tetrominos::I);
  TetroT.rotate(true);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  // check that
  // row is deleted
  // multipule rows are delted
  // rows are moved down
  // the right colors are moved down

  // check that no rows have been filled
  ASSERT_EQ(0, Game.rowsFilled_);

  int array16[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int array17[] = {2, 2, 0, 0, 0, 0, 0, 0, 0, 1};
  int array18[] = {2, 2, 1, 1, 1, 1, 0, 0, 0, 1};
  int array19[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1};

  // check that all rows have been added correctly
  bool row16 = std::equal(std::begin(array16), std::end(array16),
                          std::begin(Game.grid[16]));
  bool row17 = std::equal(std::begin(array17), std::end(array17),
                          std::begin(Game.grid[17]));
  bool row18 = std::equal(std::begin(array18), std::end(array18),
                          std::begin(Game.grid[18]));
  bool row19 = std::equal(std::begin(array19), std::end(array19),
                          std::begin(Game.grid[19]));

  ASSERT_EQ(row16, true);
  ASSERT_EQ(row17, true);
  ASSERT_EQ(row18, true);
  ASSERT_EQ(row19, true);

  // add last Tetromino to fill bottom two rows
  TetroT.setPivot(9, 22);
  TetroT.setShape(Tetrominos::J);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  // check that two rows have been filled
  ASSERT_EQ(2, Game.rowsFilled_);
  const int expected1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  const int expected2[] = {2, 2, 0, 0, 0, 0, 0, 0, 0, 1};

  bool expectedRow18 = std::equal(std::begin(expected1), std::end(expected1),
                                  std::begin(Game.grid[18]));
  bool expectedRow19 = std::equal(std::begin(expected2), std::end(expected2),
                                  std::begin(Game.grid[19]));

  ASSERT_EQ(expectedRow18, true);
  ASSERT_EQ(expectedRow19, true);
}
TEST(Tetris, CalculateGamePoints) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);
  Tetrominos TetroI;

  // Vectors to fill Rows
  std::vector<std::pair<int, int>> vec16, vec17, vec18, vec19;

  //  y-values for each vector (shift already added) () shift = 4
  int y_values[] = {20, 21, 22, 23};

  // Fill each vector with x values from 2 to 10 () shift = 2
  for (int x = 2; x <= 10; ++x) {
    vec16.emplace_back(x, y_values[0]);
    vec17.emplace_back(x, y_values[1]);
    vec18.emplace_back(x, y_values[2]);
    vec19.emplace_back(x, y_values[3]);
  }

  //___________LEVEL = 0______________________________
  // calculate 1 row

  // Check there are no current points
  ASSERT_EQ(0, Game.gamePoints_);

  // fill last row except one
  Game.insertTetro(vec19, 3);

  // fill row
  IntPairVector fillRow = {std::make_pair(11, 23)};
  Game.insertTetro(fillRow, 4);

  // 40 * (Level +1) für k = 1
  ASSERT_EQ(40, Game.gamePoints_);

  //_________LEVEL = 6 ========
  // calculate 2 row
  Game.setLevel(6);

  // fill two rows
  Game.insertTetro(vec19, 3);
  Game.insertTetro(vec18, 1);

  // add vec to fill two rows
  fillRow.emplace_back(11, 22);
  Game.insertTetro(fillRow, 6);

  // 100 * (i+1) für k = 2
  ASSERT_EQ(740, Game.gamePoints_);

  //_________LEVEL = 14 ========
  // calculate 3 row
  Game.setLevel(14);

  // fill two rows
  Game.insertTetro(vec19, 3);
  Game.insertTetro(vec18, 1);
  Game.insertTetro(vec17, 1);

  fillRow.emplace_back(11, 21);
  Game.insertTetro(fillRow, 6);

  // 300 * (i+1) für k = 3
  ASSERT_EQ(5240, Game.gamePoints_);

  //_________LEVEL = 39 ========
  // calculate 4 row
  Game.setLevel(39);

  // fill two rows
  Game.insertTetro(vec19, 3);
  Game.insertTetro(vec18, 1);
  Game.insertTetro(vec17, 1);
  Game.insertTetro(vec16, 9);

  fillRow.emplace_back(11, 20);
  Game.insertTetro(fillRow, 6);

  // 1200* (i+1) für k = 4.
  ASSERT_EQ(53240, Game.gamePoints_);

  // Test added points when pressing down buttom
  UserInput u;
  u.keycode_ = 258;
  Game.gamePoints_ = 0;

  Game.currentTetro->setPivot(Game.xSpawn, Game.ySpawn);
  Game.currentTetro->setShape(Tetrominos::T);
  for (int i = 0; i < 20; i++) {
    Game.processUserInput(u);
  }
  ASSERT_EQ(19, Game.gamePoints_);
}
TEST(Tetris, processUserInputQuit) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  UserInput u;
  u.keycode_ = 'q';
  ASSERT_FALSE(Game.processUserInput(u));
}
TEST(Tetris, processUserInputKEYDOWN) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);
  UserInput u;

  Game.currentTetro->setPivot(4, 1);
  Game.currentTetro->setShape(Tetrominos::T);
  u.keycode_ = 258;

  ASSERT_TRUE(Game.processUserInput(u));
  ASSERT_EQ(1, Game.times_pressed);

  IntPairVector current = Game.currentTetro->getPoints();
  IntPairVector expected = {{3, 2}, {4, 2}, {5, 2}, {4, 3}};

  std::sort(current.begin(), current.end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(current, expected);
}
TEST(Tetris, processUserInputMoveRight)

{
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);
  UserInput u;

  Game.currentTetro->setPivot(4, 1);
  Game.currentTetro->setShape(Tetrominos::T);
  // move right
  u.keycode_ = 261;

  ASSERT_TRUE(Game.processUserInput(u));

  IntPairVector current = Game.currentTetro->getPoints();
  IntPairVector expected = {{4, 1}, {5, 1}, {6, 1}, {5, 2}};

  std::sort(current.begin(), current.end());
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(current, expected);
}
TEST(Tetris, processUserInputMoveLeft) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);
  UserInput u;

  Game.currentTetro->setPivot(4, 1);
  Game.currentTetro->setShape(Tetrominos::T);
  // move left
  u.keycode_ = 260;

  ASSERT_TRUE(Game.processUserInput(u));

  IntPairVector current = Game.currentTetro->getPoints();
  IntPairVector expected = {{2, 1}, {3, 1}, {4, 1}, {3, 2}};

  std::sort(current.begin(), current.end());
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(current, expected);
}
TEST(Tetris, processUserInputEdge) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);
  UserInput u;

  Game.currentTetro->setPivot(4, 1);
  Game.currentTetro->setShape(Tetrominos::T);
  // move left
  u.keycode_ = 270;
  ASSERT_TRUE(Game.processUserInput(u));
  u.keycode_ = 100;
  ASSERT_TRUE(Game.processUserInput(u));
  u.keycode_ = 278;
  ASSERT_TRUE(Game.processUserInput(u));
}
TEST(Tetris, switchTetromino) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Tetrominos *originalCurrent = Game.currentTetro;
  Tetrominos *originalNext = Game.nextTetro;

  Game.switchTetromino();

  // Check if the pointers have been swapped
  EXPECT_EQ(Game.currentTetro, originalNext);
  EXPECT_EQ(Game.nextTetro, originalCurrent);
}
TEST(Tetris, validateMove) {

  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Game.currentTetro->setPivot(3, 22);
  Game.currentTetro->setShape(Tetrominos::I);

  // IntPairVector expected = {{2, 23}, {3, 23}, {4, 23}, {5, 23}};
  IntPairVector original = Game.currentTetro->getPoints();
  std::sort(original.begin(), original.end());

  // moving tetro left against border should stay equal
  Game.currentTetro->moveLeft();
  Game.validateMove(false);
  std::sort(Game.currentTetro->getPoints().begin(),
            Game.currentTetro->getPoints().end());

  // check that Tetromino cant move further down then the border
  Game.currentTetro->moveDown();
  IntPairVector lastRow = Game.currentTetro->getPoints();
  std::sort(lastRow.begin(), lastRow.end());

  // move over border
  Game.currentTetro->moveDown();
  Game.validateMove(false);

  // coordinates should stay equal
  EXPECT_EQ(Game.currentTetro->getPoints(), lastRow);

  Game.nextTetro->setShape(Tetrominos::I);
  Game.switchTetromino();
  Game.currentTetro->setPivot(2, 20);
  Game.currentTetro->computeShape();

  // move down so it collides with droppped tetromino
  Game.currentTetro->moveDown();
  Game.validateMove(false);
  Game.currentTetro->moveDown();
  Game.validateMove(false);

  IntPairVector expectedT = Game.currentTetro->getPoints();
  Game.currentTetro->moveDown();
  Game.validateMove(false);

  std::sort(expectedT.begin(), expectedT.end());
  std::sort(Game.currentTetro->getPoints().begin(),
            Game.currentTetro->getPoints().end());

  // should detect collion and stay at previous spot
  EXPECT_EQ(Game.currentTetro->getPoints(), expectedT);

  // quit game when tetros are filled to top
  IntPairVector full = {{6, 5},  {6, 6},  {6, 7},  {6, 8},  {6, 9},
                        {6, 10}, {6, 11}, {6, 12}, {6, 13}, {6, 14},
                        {6, 15}, {6, 16}, {6, 17}, {6, 18}, {6, 19},
                        {6, 20}, {6, 21}, {6, 22}, {6, 23}};

  Game.nextTetro->setShape(Tetrominos::I);
  Game.switchTetromino();
  Game.insertTetro(full, 5);

  Game.currentTetro->moveDown();
  Game.validateMove(false);

  // game should quit once Tetrominos fill the grid to the top
  ASSERT_TRUE(Game.quit);
}
TEST(Tetris, timeInterval) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  const int testDurationSeconds = 10;
  const auto frameDuration = std::chrono::milliseconds(1000 / 60);
  int expectedFallSpeed = Game.fallSpeed;

  auto start = std::chrono::steady_clock::now();
  auto lastFallTime = start;
  int fallCount = 0;

  while (std::chrono::steady_clock::now() - start <
         std::chrono::seconds(testDurationSeconds)) {
    auto now = std::chrono::steady_clock::now();
    if (Game.updateGame(lastFallTime, now)) {
      fallCount++;
    }
  }

  auto actualDuration = std::chrono::steady_clock::now() - start;
  auto expectedInterval = frameDuration * expectedFallSpeed;
  int expectedFallCount = actualDuration / expectedInterval;

  // 5% margin of error
  EXPECT_NEAR(fallCount, expectedFallCount, expectedFallCount * 0.1);

  Game.setLevel(10);
  Game.speedAndLevel(false);
  expectedFallSpeed = Game.fallSpeed;

  auto start2 = std::chrono::steady_clock::now();
  lastFallTime = start2;
  fallCount = 0;

  while (std::chrono::steady_clock::now() - start2 <
         std::chrono::seconds(testDurationSeconds)) {
    auto now = std::chrono::steady_clock::now();
    if (Game.updateGame(lastFallTime, now)) {
      fallCount++;
    }
  }

  actualDuration = std::chrono::steady_clock::now() - start2;
  expectedInterval = frameDuration * expectedFallSpeed;
  expectedFallCount = actualDuration / expectedInterval;

  // Level 10 test
  EXPECT_NEAR(fallCount, expectedFallCount, expectedFallCount * 0.1);
}

// MockTerminal________________________________________________________________
TEST(Tetris, drawTetromino) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Game.currentTetro->setPivot(Game.xSpawn, Game.ySpawn);
  Game.currentTetro->setShape(Tetrominos::I);
  Game.drawTetromino(Game.currentTetro->getPoints(),
                     Game.currentTetro->getColor());

  Game.nextTetro->setPivot(Game.xnPoint_, Game.ynPoint_);
  Game.nextTetro->setShape(Tetrominos::T);
  Game.drawTetromino(Game.nextTetro->getPoints(), Game.nextTetro->getColor());

  IntPairVector CurrentSpawn = Game.currentTetro->getPoints();
  IntPairVector NextSpawn = Game.nextTetro->getPoints();

  // drawn correctly at spawn
  for (auto const &vec : CurrentSpawn) {
    ASSERT_TRUE(tm.isPixelDrawn(vec.second, vec.first));
    ASSERT_EQ(Game.currentTetro->getColor(),
              tm.getColor(vec.second, vec.first));
  }

  // drawn correcly at spawn of next
  for (auto const &vec : NextSpawn) {
    ASSERT_TRUE(tm.isPixelDrawn(vec.second, vec.first));
    ASSERT_EQ(Game.nextTetro->getColor(), tm.getColor(vec.second, vec.first));
  }

  Game.eraseTetromino(Game.currentTetro->getPoints());
  // Game.currentTetro->setShape(Tetrominos::I);
  Game.switchTetromino();
  // draw in last row to check that it does not draw on border
  Game.currentTetro->setPivot(6, 23);
  IntPairVector lastRow = Game.currentTetro->getPoints();
  Game.currentTetro->moveDown();
  Game.validateMove(false);
  Game.drawTetromino(Game.currentTetro->getPoints(),
                     Game.currentTetro->getColor());

  for (auto const &vec : lastRow) {
    ASSERT_TRUE(tm.isPixelDrawn(vec.second, vec.first));
    ASSERT_EQ(Game.currentTetro->getColor(),
              tm.getColor(vec.second, vec.first));
  }
}
TEST(Tetris, drawBorder) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Game.drawBorder();
  // draw left and right
  for (int i = Game.y_min_game_; i < Game.y_max_game_; i++) {
    // draw left and right border
    ASSERT_TRUE(tm.isPixelDrawn(i, Game.x_min_game_));
    ASSERT_TRUE(tm.isPixelDrawn(i, Game.x_max_game_));
  }
  for (int i = Game.x_min_game_; i <= (Game.x_max_game_); i++) {
    // draw bottom border
    ASSERT_TRUE(tm.isPixelDrawn(Game.y_max_game_, i));
  }
}
TEST(Tetris, eraseTetromino) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Game.currentTetro->setPivot(Game.xSpawn, Game.ySpawn);
  Game.currentTetro->setShape(Tetrominos::I);
  Game.drawTetromino(Game.currentTetro->getPoints(),
                     Game.currentTetro->getColor());

  Game.nextTetro->setPivot(Game.xnPoint_, Game.ynPoint_);
  Game.nextTetro->setShape(Tetrominos::T);
  Game.drawTetromino(Game.nextTetro->getPoints(), Game.nextTetro->getColor());

  // now erase Tetrominos
  Game.eraseTetromino(Game.currentTetro->getPoints());
  Game.eraseTetromino(Game.nextTetro->getPoints());

  IntPairVector CurrentSpawn = Game.currentTetro->getPoints();
  IntPairVector NextSpawn = Game.nextTetro->getPoints();

  // drawn correctly at spawn
  for (auto const &vec : CurrentSpawn) {
    ASSERT_FALSE(tm.isPixelDrawn(vec.second, vec.first));
    ASSERT_EQ(0, tm.getColor(vec.second, vec.first));
  }
  // drawn correcly at spawn of next
  for (auto const &vec : NextSpawn) {
    ASSERT_FALSE(tm.isPixelDrawn(vec.second, vec.first));
    ASSERT_EQ(0, tm.getColor(vec.second, vec.first));
  }
}
TEST(Tetris, CheckHandleFullRowsTerminal) {
  MockTerminalManager tm(30, 60);
  Tetris Game(&tm);

  Tetrominos TetroT;
  TetroT.setPivot(4, 23);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());
  Game.drawTetromino(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(8, 23);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());
  Game.drawTetromino(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(3, 21);
  TetroT.setShape(Tetrominos::O);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());
  Game.drawTetromino(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(6, 22);
  TetroT.setShape(Tetrominos::I);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());
  Game.drawTetromino(TetroT.getPoints(), TetroT.getColor());

  TetroT.setPivot(11, 22);
  TetroT.setShape(Tetrominos::I);
  TetroT.rotate(true);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());
  Game.drawTetromino(TetroT.getPoints(), TetroT.getColor());

  int array16[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int array17[] = {2, 2, 0, 0, 0, 0, 0, 0, 0, 1};
  int array18[] = {2, 2, 1, 1, 1, 1, 0, 0, 0, 1};
  int array19[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1};

  // x + 2, y + 4

  for (int col = 0; col < 10; col++) {
    ASSERT_EQ(array16[col], tm.getColor(20, (col + 2)));
    ASSERT_EQ(array17[col], tm.getColor(21, (col + 2)));
    ASSERT_EQ(array18[col], tm.getColor(22, (col + 2)));
    ASSERT_EQ(array19[col], tm.getColor(23, (col + 2)));
  }

  // insert to fill rows
  TetroT.setPivot(9, 22);
  TetroT.setShape(Tetrominos::J);
  Game.insertTetro(TetroT.getPoints(), TetroT.getColor());

  // above two rows should be drawn on the bottom two rows
  for (int col = 0; col < 10; col++) {
    ASSERT_EQ(array16[col], tm.getColor(22, (col + 2)));
    ASSERT_EQ(array17[col], tm.getColor(23, (col + 2)));
  }
}
