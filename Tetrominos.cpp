// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#include "./Tetrominos.h"
#include <cstdlib>

Tetrominos::Tetrominos() {}

// set Pivot
void Tetrominos::setPivot(int x, int y) {
  xPivot_ = x;
  yPivot_ = y;
}

// true is right, false is left
void Tetrominos::rotate(bool direction) {
  if (type == O) {
    return;
  }
  // if I has been rotated to the left must it must rotate right next
  if ((type == I || type == S || type == Z) && rotatedI && direction) {
    rotatedI = false;
    direction = false;
  }
  quickSave();
  for (auto &vec : tetrominosVecs) {
    // Skip rotation if the point is exactly at the pivot
    if (vec.first == xPivot_ && vec.second == yPivot_) {
      continue;
    }
    // true = right, false = left
    if (!direction) {
      const int temp_first = vec.first;
      vec.first = xPivot_ + (vec.second - yPivot_);
      vec.second = yPivot_ - (temp_first - xPivot_);
    } else {
      const int temp_first = vec.first;
      vec.first = xPivot_ - (vec.second - yPivot_);
      vec.second = yPivot_ + (temp_first - xPivot_);

      if (type == I || type == Z || type == S) {
        rotatedI = true;
      }
    }
  }
}

//______________MOVE___________________________________________________________

// move down
void Tetrominos::moveDown() {
  quickSave();
  // loop through vec adding 1 to y value
  setPivot(xPivot_, yPivot_ + 1);
  for (auto &vec : tetrominosVecs) {
    vec.second += 1;
  }
}
// move Left
void Tetrominos::moveLeft() {
  quickSave();
  setPivot(xPivot_ - 1, yPivot_);
  for (auto &vec : tetrominosVecs) {
    vec.first -= 1;
  }
}
// move right
void Tetrominos::moveRight() {
  quickSave();
  setPivot(xPivot_ + 1, yPivot_);
  for (auto &vec : tetrominosVecs) {
    vec.first += 1;
  }
}

//_____________________________________________________________________________
// sets Shape and calculates the current coordinates of Tetro
void Tetrominos::setShape(TetrominoType t) {
  // set type
  type = t;
  color_ = static_cast<int>(t);

  // if Pivot has been set calculate coodinates
  if (xPivot_ != -1 && yPivot_ != -1) {
    computeShape();
  }
}
void Tetrominos::setRandShape() {
  int rand = (std::rand() % 7) + 1;
  if (rand == color_) {
    rand = (std::rand() % 7) + 1;
  }

  //  Cast the integer to TetrominoType
  auto tempType = static_cast<TetrominoType>(rand);
  color_ = rand;
  setShape(tempType);
  rotatedI = false;
}

//_____________________________________________________________________________
void Tetrominos::computeShape() {
  quickSave();
  // clear previous vec
  tetrominosVecs.clear();
  tetrominosVecs.emplace_back(xPivot_, yPivot_);

  // calculate new vec
  switch (type) {
  case T:
    tetrominosVecs.emplace_back((xPivot_ - 1), yPivot_);
    tetrominosVecs.emplace_back((xPivot_ + 1), yPivot_);
    tetrominosVecs.emplace_back(xPivot_, yPivot_ + 1);
    // add color
    //    color_ = 0;

    break;
  case Z:
    tetrominosVecs.emplace_back((xPivot_ - 1), yPivot_);
    tetrominosVecs.emplace_back(xPivot_, (yPivot_ + 1));
    tetrominosVecs.emplace_back((xPivot_ + 1), yPivot_ + 1);
    // add color
    // color_ = 1;
    break;
  case S:
    tetrominosVecs.emplace_back((xPivot_ + 1), yPivot_);
    tetrominosVecs.emplace_back(xPivot_, (yPivot_ + 1));
    tetrominosVecs.emplace_back((xPivot_ - 1), yPivot_ + 1);
    // add color
    // color_ = 2;
    break;
  case J:
    tetrominosVecs.emplace_back(xPivot_ + 1, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ + 1, yPivot_ + 1);
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_);
    // add color
    // color_ = 3
    break;
  case L:
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ + 1, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_ + 1);
    // add color

    break;
  case I:
    tetrominosVecs.emplace_back(xPivot_ + 1, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ - 2, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_);
    // add color
    break;
  case O:
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_);
    tetrominosVecs.emplace_back(xPivot_ - 1, yPivot_ + 1);
    tetrominosVecs.emplace_back(xPivot_, yPivot_ + 1);
    // add color
    break;
  }
}

//_____________________________________________________________________________
void Tetrominos::quickSave() {
  tetrominosVecs_prev = tetrominosVecs;
  xPivot_prev = xPivot_;
  yPivot_prev = yPivot_;
}
// revert to save
void Tetrominos::revert() {
  if (xPivot_prev != -1 && yPivot_prev != -1) {
    tetrominosVecs = tetrominosVecs_prev;
    xPivot_ = xPivot_prev;
    yPivot_ = yPivot_prev;
  }
}