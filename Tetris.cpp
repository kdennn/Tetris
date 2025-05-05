// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>
#include "./Tetris.h"
#include "./Tetrominos.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>

using IntPair = std::pair<int, int>;
using IntPairVector = std::vector<IntPair>;

Tetris::Tetris(TerminalManager *terminalManager, int level, char leftKey,
               char rightKey)
    : terminalManager_(terminalManager) {
  if (terminalManager_ == nullptr) {
    return;
  }
  numRows_ = terminalManager_->numRows();
  numCols_ = terminalManager_->numCols();

  setLevel(level);
  setKeys(leftKey, rightKey);

  std::srand(static_cast<unsigned int>(std::time(0)));
}

void Tetris::initTerminal() {
  drawBorder();
  currentTetro->setPivot(xSpawn, ySpawn);
  currentTetro->setRandShape();
  nextTetro->setPivot(xnPoint_, ynPoint_);
  nextTetro->setRandShape();
  drawTetromino(nextTetro->getPoints(), nextTetro->getColor());
}

void Tetris::setKeys(const char left, const char right) {
  keyLeftRotation_ = left;
  keyRightRotation_ = right;
}

// run game under current logic
void Tetris::run() {
  initTerminal();
  highScore = loadHighScore();

  auto lastFallTime = std::chrono::steady_clock::now();

  while (processUserInput(terminalManager_->getUserInput())) {
    auto now = std::chrono::steady_clock::now();
    updateGame(lastFallTime, now);
    drawLevelAndFilledRows();
  }

  saveHighScore();
  drawPattern();
}

// Handle Key inputt from player
bool Tetris::processUserInput(UserInput userinput) {
  eraseTetromino(currentTetro->getPoints());

  switch (userinput.keycode_) {
  case 'q':
    // exit
    return false;
  case 258: // Key Down
    times_pressed += 1;
    pushedDown_ = true;
    currentTetro->moveDown();
    break;
  case 261: // Key Right
    currentTetro->moveRight();
    break;
  case 260: // Key Left
    currentTetro->moveLeft();
    break;
  default:
    // Handle rotation based on dynamic keys
    if (userinput.keycode_ == keyRightRotation_) {
      currentTetro->rotate(true);
    } else if (userinput.keycode_ == keyLeftRotation_) {
      currentTetro->rotate(false);
    }
    break;
  }
  validateMove(false);
  pushedDown_ = false;
  // drawTetromino();
  return !quit;
}

//____________Tetromino_related________________________________________________
bool Tetris::updateGame(std::chrono::steady_clock::time_point &lastFallTime,
                        std::chrono::steady_clock::time_point currentTime) {
  const auto frameDuration = std::chrono::milliseconds(1000 / 60);
  auto fallInterval = frameDuration * fallSpeed;

  if (currentTime - lastFallTime >= fallInterval) {
    eraseTetromino(currentTetro->getPoints());
    currentTetro->moveDown();
    validateMove(false);
    lastFallTime = currentTime;
    return true;
  }
  return false;
}

// validate if movement is legal
void Tetris::validateMove(const bool spawn) {
  for (const auto &vec : currentTetro->getPoints()) {
    // check that it cant go out of left/ right bounds
    // comparing Coordinates to field dimensions (Terminal Coordinates)
    if (x_min_game_ >= vec.first || vec.first >= x_max_game_) {
      currentTetro->revert();
      return;
    }

    // check it cant hit bottom bounds
    // comparing Coordinates to field dimensions (Terminal Coordinates)
    if (y_max_game_ <= vec.second) {
      currentTetro->revert();
      drawTetromino(currentTetro->getPoints(), currentTetro->getColor());
      insertTetro(currentTetro->getPoints(), currentTetro->getColor());
      // switch Tetromino Function
      switchTetromino();
      return;
    }

    // if called while Tetrominos are switched ignore out of bounds
    int col = vec.first - Xshift;
    int row = vec.second - Yshift;

    if (std::clamp(col, 0, 9) == col && std::clamp(row, 0, 19) == row) {
      if (grid[(row)][col] != 0) {
        // if new Tetromino spawn would touch previous Tetro at spawn then
        if (spawn) {
          quit = true;
          return;
        }
        currentTetro->revert();
        drawTetromino(currentTetro->getPoints(), currentTetro->getColor());
        // add all the Points to the bucket
        insertTetro(currentTetro->getPoints(), currentTetro->getColor());
        switchTetromino();
        return;
      }
    }
  }
  //  check if any row is full
  drawTetromino(currentTetro->getPoints(), currentTetro->getColor());
}

// Insert entire Tetromino coordinates
void Tetris::insertTetro(const IntPairVector &tetroVecs, const int color) {
  for (const auto &vec : tetroVecs) {
    const int x = vec.first - Xshift;
    const int y = vec.second - Yshift;

    grid[y][x] = color;
  }
  calcGamePoints(0);
  CheckHandleFullRows();
}

// check for full rows and move them down
void Tetris::CheckHandleFullRows() {
  int rowsCleared = 0;
  int temp_filled = 0;

  for (int row = maxRows_ - 1; row >= 0; row--) {
    bool rowFull = true;

    // Check if the current row is full
    for (int col = 0; col < maxCols_; col++) {
      if (grid[row][col] == 0) {
        rowFull = false;
        break;
      }
    }

    if (rowFull) {
      rowsCleared++;
      temp_filled++;

    } else if (rowsCleared > 0) {
      // Move the row down by the number of cleared rows
      for (int col = 0; col < maxCols_; col++) {
        grid[row + rowsCleared][col] = grid[row][col];
        grid[row][col] = 0;
      }
      // Draw the moved row
      drawRow(row + rowsCleared);
    }
  }

  // Clear and redraw the top rows
  for (int row = 0; row < rowsCleared; row++) {
    for (int col = 0; col < maxCols_; col++) {
      grid[row][col] = 0;
    }
    drawRow(row);
  }
  // add to filled rows, and determine nevel level
  if (temp_filled > 0) {
    calcGamePoints(temp_filled);
    rowsFilled_ += temp_filled;
  }
  speedAndLevel(true);
}

//_____________________________________________________________________________
void Tetris::switchTetromino() {
  // reset arrow down keypress
  times_pressed = 0;
  eraseTetromino(nextTetro->getPoints());
  std::swap(currentTetro, nextTetro);
  nextTetro->setPivot(xnPoint_, ynPoint_);
  // nextTetro->setShape(Tetrominos::T);
  nextTetro->setRandShape();
  //  function to draw next tetro
  drawTetromino(nextTetro->getPoints(), nextTetro->getColor());
  // draw and compute current (new) Tetromino
  currentTetro->setPivot(xSpawn, ySpawn);
  currentTetro->computeShape();
  validateMove(true);
  drawTetromino(currentTetro->getPoints(), currentTetro->getColor());
}

//_____GAME_LOGIC__________________________________________________________

// function to set fall speed of tetromino, determined by the current level
// adds one to the rows filled and level up every 10
void Tetris::speedAndLevel(const bool verbose) {
  rowsFilled_ =
      (verbose) ? rowsFilled_ : rowsFilled_ + 1; // why did I add this? fudge
  if (rowsFilled_ == 10) {
    level_ += 1;
    rowsFilled_ = 0;
  }
  static const int fallSpeeds[] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
                                   5,  5,  5,  4,  4,  4,  3,  3,  3, 2,
                                   2,  2,  2,  2,  2,  2,  2,  2,  2, 1};

  if (level_ < 0) {
    fallSpeed = 48; // Default for invalid negative levels, if necessary
  } else if (level_ < 30) {
    fallSpeed = fallSpeeds[level_];
  } else {
    fallSpeed = 1; // For level 29 and above
  }
}

void Tetris::calcGamePoints(const int rows) {
  if (pushedDown_) {
    gamePoints_ += times_pressed;
  }
  if (rows == 0) {
    return;
  }
  if (rows < 1 || rows > 4) {
    std::cerr << rows << " is not a valid argument (1-4)" << std::endl;
    return;
  }

  static const int points[] = {40, 100, 300, 1200};
  gamePoints_ += points[rows - 1] * (level_ + 1);
}

// draw Tetromino
void Tetris::drawTetromino(const IntPairVector &points, const int color) const {
  for (const auto &vec : points) {
    terminalManager_->drawPixel(vec.second, vec.first, color);
  }
}

// erase Tetromino
void Tetris::eraseTetromino(const IntPairVector &points) const {
  for (const auto &vec : points) {
    terminalManager_->drawPixel(vec.second, vec.first, 0);
  }
}

// draw all dropped Tetromionos
void Tetris::drawRow(const int row) const {
  for (int x = 0; x < maxCols_; x++) {
    // int c = grid[row][x];
    terminalManager_->drawPixel(row + Yshift, x + Xshift, grid[row][x]);
  }
}

// draw border of game
void Tetris::drawBorder() const {
  // draw left and right
  for (int i = y_min_game_; i < y_max_game_; i++) {
    // draw left and right border
    terminalManager_->drawPixel(i, x_min_game_, 9);
    terminalManager_->drawPixel(i, x_max_game_, 9);
  }
  for (int i = x_min_game_; i <= (x_max_game_); i++) {
    // draw bottom border
    terminalManager_->drawPixel(y_max_game_, i, 9);
  }
  // draw next Tetromino !!!
  terminalManager_->drawString(3, (x_max_game_ + 5), 1, "Next");

  terminalManager_->refresh();
}

// draw level and Points indicator
void Tetris::drawLevelAndFilledRows() const {
  // Convert integer to std::string
  const std::string lvl = std::to_string(level_);
  // Get the C-string representation
  const char *level = lvl.c_str();

  const std::string fill = std::to_string(rowsFilled_);
  const char *filled = fill.c_str();

  const std::string poi = std::to_string(gamePoints_);
  const char *points = poi.c_str();

  terminalManager_->drawString(1, (5), 1, "Level:");
  terminalManager_->drawString(1, 9, 1, level);

  terminalManager_->drawString(12, (x_max_game_ + 5), 1, "Points:");
  terminalManager_->drawString(12, (x_max_game_ + 11), 1, points);

  terminalManager_->drawString(14, (x_max_game_ + 5), 1, "Rows filled:");
  terminalManager_->drawString(14, (x_max_game_ + 12), 1, filled);
}

void Tetris::drawPattern() {
  for (int rows = 0; rows < numCols_; rows++) {
    for (int cols = 0; cols < numCols_; cols++) {
      terminalManager_->drawPixel(rows, cols, 0);
      usleep(300);
      terminalManager_->drawPixel(rows, cols, 9);
      terminalManager_->refresh();
    }
    usleep(500);
  }

  for (int rows = 0; rows < numCols_; rows++) {
    for (int cols = 0; cols < numCols_; cols++) {
      terminalManager_->drawPixel(rows, cols, 0);
      terminalManager_->refresh();
      usleep(400);
    }
    usleep(900);
  }

  const std::string poi = std::to_string(gamePoints_);
  const char *points = poi.c_str();
  const std::string Hpoi = std::to_string(highScore);
  const char *Hpoints = Hpoi.c_str();

  const int y = numRows_ / 2;
  const int x = numCols_ / 2;

  terminalManager_->drawString(y, x, 5, "YOU LOST! GAME OVER!");
  terminalManager_->drawString(y + 2, x, 5, "Highscore: ");
  terminalManager_->drawString(y + 2, x + 6, 5, points);
  terminalManager_->drawString(y + 4, x, 5, "Your score: ");
  terminalManager_->drawString(y + 4, x + 7, 5, Hpoints);
  terminalManager_->refresh();

  usleep(10000000);
}

void Tetris::saveHighScore() {
  if (gamePoints_ > highScore) {
    std::ofstream file(highScoreFile);
    if (file.is_open()) {
      file << gamePoints_;
      file.close();
      highScore = gamePoints_;
    }
  }
}

int Tetris::loadHighScore() {
  std::ifstream file(highScoreFile);
  if (file.is_open()) {
    file >> highScore;
    file.close();
  }
  return highScore;
}