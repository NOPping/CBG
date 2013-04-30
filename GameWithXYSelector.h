/// Common functions between games that use X, Y selectors.
/// @author Peter Morgan

#ifndef GAMEWITHXYSELECTOR_H
#define GAMEWITHXYSELECTOR_H

#include "Game.h"

class GameWithXYSelector:public Game {
  protected:
  /// Prints out the board and the players pieces.
  void drawScreen() const;

  /// Prints out the board and the players pieces.
  /// Prompts with message to get a point between 0 and range.
  int  getPoint(string message, int range) const;

  /// Returns the opposition.
  int  getOpposition() const;

  public:
  GameWithXYSelector(const int amountOfPlayers, const int columns,
                     const int rows);

};

#endif
