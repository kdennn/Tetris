// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#include "MockTerminalManager.h"

void MockTerminalManager::drawPixel(const int row, const int col,
                                    const int color) {
  const int idx = row * numCols_ + col;
  mock_grid[idx] = color;
}

// isPixelDrawn
bool MockTerminalManager::isPixelDrawn(const int row, const int col) const {
  const int idx = row * numCols_ + col;
  return mock_grid[idx] != 0;
  // return pixelDrawn[row][col] != 0;
}

int MockTerminalManager::getColor(const int row, const int col) const {
  const int idx = row * numCols_ + col;
  return mock_grid[idx];
}

void MockTerminalManager::drawString(int row, int col, int /* color */,
                                     const char * /* str */) {
  const int idx = row * numCols_ + col;
  mock_grid[idx] = -1;
}

UserInput MockTerminalManager::getUserInput() { return UserInput(); }