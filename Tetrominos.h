// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>
#pragma once
#include <random>
#include <vector>

// Type alias to simplify usage
using IntPair = std::pair<int, int>;
using IntPairVector = std::vector<IntPair>;

class Tetrominos {

public:
  enum TetrominoType { I = 1, O = 2, T = 3, S = 4, Z = 5, J = 6, L = 7 };

  Tetrominos();

  // destructor
  ~Tetrominos() = default;

  // set Pivot
  void setPivot(int x, int y);

  // set shape depending on type
  void setShape(TetrominoType t);

  // set to random shape
  void setRandShape();

  // calculate base on Shape
  void computeShape();

  // true is right, false is left
  void rotate(bool direction);

  // move down
  void moveDown();

  // move left
  void moveLeft();

  // move right
  void moveRight();

  // get color of Tetromino
  int getColor() const { return color_; }

  // get coordinates of Tetromino
  IntPairVector &getPoints() { return tetrominosVecs; }

  // revert so saved values
  void revert();

private:
  // Tetromino Shape
  TetrominoType type;

  // coordinates of Pivot point to rotate (-1 if Pivot not set)
  int xPivot_ = -1;
  int yPivot_ = -1;

  // vector of Tetromino
  IntPairVector tetrominosVecs;

  // color of Tetromino
  int color_ = 0;

  // Type I rotation bool
  bool rotatedI = false;
  // bool rotatedZ = false;

  // function to easily save current Vector and
  void quickSave();

  // privous values save
  IntPairVector tetrominosVecs_prev;
  int xPivot_prev = -1;
  int yPivot_prev = -1;
};
//_____________________________________________________________________________
