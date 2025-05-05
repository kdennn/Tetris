// Copyright 2024, University of Freiburg
// Student, Computer Science
// Auther: Kaden Moeschlin <km329>

#include "./NcursesTerminalManager.h"
#include "./Tetris.h"
#include <iostream>
#include <utility>
#include <vector>

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

int main(int argc, char *argv[]) {

  // Initialize vector with 12 color pairs
  const std::vector<std::pair<Color, Color>> colors = {
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

  int level = 0;
  char rotateLeftKey = 'a';
  char rotateRightKey = 's';

  switch (argc) {
  case 2: // Only level specified
    level = std::atoi(argv[1]);
    if (level < 0) {
      std::cerr << "Invalid level: Level must be a positive integer.\n";
      return 1;
    }
    break;
  case 3: // Only rotation keys specified
    rotateLeftKey = argv[1][0];
    rotateRightKey = argv[2][0];
    if (argv[1][1] != '\0' || argv[2][1] != '\0') {
      std::cerr << "Rotation keys must be single characters.\n";
      return 1;
    }
    break;
  case 4: // Level and both rotation keys specified
    level = std::atoi(argv[1]);
    if (level <= 0) {
      std::cerr << "Invalid level: Level must be a positive integer.\n";
      return 1;
    }
    rotateLeftKey = argv[2][0];
    rotateRightKey = argv[3][0];
    if (argv[2][1] != '\0' || argv[3][1] != '\0') {
      std::cerr << "Rotation keys must be single characters.\n";
      return 1;
    }
    break;
  default: // Invalid number of arguments or no arguments
    if (argc != 1) {
      std::cerr << "Usage: " << argv[0]
                << " [<level>] [<rotateLeftKey> <rotateRightKey>]\n";
      return 1;
    }
  }

  NcursesTerminalManager tm(colors);
  Tetris game(&tm, level, rotateLeftKey, rotateRightKey);

  // Initialize and run the Tetris game with specified settings
  game.run();
}