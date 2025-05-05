// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#pragma once

#include "./TerminalManager.h"
#include <stdexcept>
#include <utility>
#include <vector>

// A class to draw pixels on or read input from the terminal, using ncurses.
class NcursesTerminalManager : public TerminalManager {
public:
  // Constructor: Set up the terminal for use with ncurses commands.
  // The argument specifies the colors that we want to use with this terminal
  // manager: Each pair consists of [foreground color, background color]. The
  // `i-th` color pair in the vector can then later be chosen if `i` is
  // specified as the color argument to `drawPixel` or `drawString`.
  explicit NcursesTerminalManager(
      const std::vector<std::pair<Color, Color>> &colors);

  // Destructor: Clean up the terminal after use.
  ~NcursesTerminalManager() override;

  // Draw a pixel at the given logical position in the given color.
  // Note: the pixel is drawn with the foreground color of the
  // color pair with the given index that was specified in the constructor.
  void drawPixel(int row, int col, int color) override;

  // Draw a string at the given logical position and color.
  void drawString(int row, int col, int color, const char *str) override;

  // Show the contents of the screen.
  void refresh() override;

  // Return the logical dimensions of the screen.
  int numRows() override { return numRows_; }
  int numCols() override { return numCols_; }

  // Get user input.
  UserInput getUserInput() override;

private:
  // The logical dimensions of the screen.
  int numRows_;
  int numCols_;
  int numColors_;
};