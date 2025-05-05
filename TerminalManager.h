// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#pragma once
#include <stdexcept>
// #include "./ColorUserInput.h"

// Class to represent an RGB color.
class Color {

public:
  // Constructor. Each of the values `red`, `green`, `blue` must be >= 0 and
  // <= 1.
  Color(float red, float green, float blue)
      : red_{red}, green_{green}, blue_{blue} {
    auto isValid = [](float color) { return color >= 0.0 && color <= 1.0; };
    if (!isValid(red_) || !isValid(green_) || !isValid(blue_)) {
      throw std::runtime_error(
          "Invalid value for color component. Must be between 0 and 1");
    }
  }
  // Get the value of the red/green/blue component.
  float red() const { return red_; }
  float green() const { return green_; }
  float blue() const { return blue_; }

private:
  float red_;
  float green_;
  float blue_;
};

// Class to represent user input (key or mouse events).
class UserInput {
public:
  // Functions that check for particular keys.
  bool isEscape() const;
  bool isKeyLeft() const;
  bool isKeyRight() const;
  bool isKeyUp() const;
  bool isKeyDown() const;
  bool isMouseclick() const;
  // The code of the key that was pressed.
  int keycode_;
  int mouseRow_ = -1;
  int mouseCol_ = -1;
};

class TerminalManager {
public:
  // Virtual destructor.
  virtual ~TerminalManager() = default;

  // Draw a "pixel" at the given position with given color
  virtual void drawPixel(int row, int col, int color) = 0;

  // Refresh the screen.
  virtual void refresh() = 0;

  // drawa string at given position
  virtual void drawString(int row, int col, int color, const char *str) = 0;

  // get user input
  virtual UserInput getUserInput() = 0;

  // Get the dimensions of the screen.
  virtual int numRows() = 0;
  virtual int numCols() = 0;
};