// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#pragma once
#include "./TerminalManager.h"

class MockTerminalManager : public TerminalManager {
public:
  // Construct with the given inumber of rows and cols.
  MockTerminalManager(int numRows, int numCols)
      : numRows_{numRows}, numCols_{numCols} {};

  ~MockTerminalManager() override = default;

  void drawPixel(int row, int col, int color) override;

  // Nothing to do for "refresh"
  void refresh() override{};

  // Get the dimensions of the screen.
  int numRows() override { return numRows_; }
  int numCols() override { return numCols_; }

  // Returns true iff there previously was a call to draw pixel
  bool isPixelDrawn(int row, int col) const;

  // Returns the "color" argument of the last call to
  int getColor(int row, int col) const;

  // set coordinate to -1 to symbolise there being a Strinf
  void drawString(int row, int col, int color, const char *str) override;

  // get user input
  UserInput getUserInput() override;

private:
  // variables for Rows and Cosl
  int numRows_;
  int numCols_;

  // max Grid size
  static const int MAX_NUM_CELLS = 1000000;

  // Mock terminal in form of Array Grid
  int mock_grid[MAX_NUM_CELLS] = {0};
};
