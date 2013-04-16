/// Checkers Game.
/// @author Ian Duffy

#ifndef CHECKERS_H
#define CHECKERS_H

#include "Game.h"

class Checkers : public Game {
  private:
    
    /// Returns the opposition.
    int   getOpposition() const;
    
    /// Prompts with message to get a point between 0 and range.
    int   getPoint(string message, int range) const;
    
    /// Calls getPoint twice to get a source square and destination square
    /// Validates the move and passes the source square and destination square
    /// onto executeMove().
    bool  getMove();
    
    /// Moves the piece on source square to destination square.
    bool  executeMove(Square* sourceSquare,Square* destinationSquare);
    
    /// Moves the piece on source square to destination square and deletes
    /// the piece on the to jump square.
    bool  executeMove(Square* sourceSquare,Square* destinationSquare,
                      Square* toJump);
    
    /// Prints out the board and all the players pieces.
    void  drawScreen() const;
    
    /// Checks if either of the players no longer have pieces.
    int   isOver() const;
    
  public:
    Checkers();
};

#endif
