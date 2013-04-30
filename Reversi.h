/// Reversi Game.
/// @author Peter Morgan

#ifndef REVERSI_H
#define REVERSI_H

#include "GameWithXYSelector.h"

class Reversi:public GameWithXYSelector {
  private:
  /// Gets a move from the player
  bool getMove();

  ///Determins if a destination square is valid
  bool isValidMove(int destinationX) const;

  /// Call the flanks method to ensure the destination coordinate  flanks an opponents piece
  // If it does it adds the piece to the destination square
  bool executeMove(Square& destinationSquare)const;

  //Determines the winner of the game
  int  isOver() const;

  ///Checks a line of pieces to see if it ends with a piece that belong to the
  ///current player if it does, it flips the line of pieces to the current players colour
  bool checkNext(Square &current,int yOffset,int xOffset,bool flip) const;

  ///Checks if a coordinate flanks an opponents piece.
  ///Calls check next to see if the piece is inline with an existing piece owned
  ///by the same player.
  bool flanks(Square current,bool flip) const;

  //Checks if a move is  within the bounds of the board.
  bool isLegal(Coordinate current,int iOffset,int jOffset) const;

  public:
  Reversi();
};


#endif
