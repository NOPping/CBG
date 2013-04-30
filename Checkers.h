/// Checkers Game.
/// @author Ian Duffy

#ifndef CHECKERS_H
#define CHECKERS_H

#include "GameWithXYSelector.h"

class Checkers : public GameWithXYSelector {
private:
  /// Calls getPoint twice to get a source square and destination square
  /// Validates the move and passes the source square and destination square
  /// onto executeMove().
  bool  getMove();
  
  /// Validates Moves.
  int validMove(Coordinate srcCoordinate, Coordinate destCoordinate) const;
  
  /// Moves the piece on source square to destination square.
  bool  executeMove(Square& srcSquare,Square& destSquare);
  
  /// Moves the piece on source square to destination square and deletes
  /// the piece on the to jump square.
  bool  executeMove(Square& srcSquare,Square& destSquare,
                    Square& toJump);
  
  /// Checks if either of the players no longer have pieces.
  int   isOver() const;
  
public:
  Checkers();
};

#endif
