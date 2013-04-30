#ifndef BASE_H
#define BASE

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Game.h"
class Base:public Game{
public: 

  /// Prints out the board and the players pieces.
  void drawScreen() const;
  
/// Prints out the board and the players pieces.
  /// Prompts with message to get a point between 0 and range.
  int  getPoint(string message, int range) const;

  /// Returns the opposition.
  int  getOpposition() const;
  
  ///Constructor for base class.
  Base();
};
#endif
