/// A Piece with a source.
/// @author Ian Duffy

#ifndef SOURCEPIECE_H
#define SOURCEPIECE_H

#include "Piece.h"

class SourcePiece : virtual public Piece {
  protected:
  /// Coordinate containing the source.
  Coordinate source;

  public:
  SourcePiece(Player& owner, Coordinate source);

  /// Returns the source.
  Coordinate getSource();

  /// Sets the source coordinate.
  void setSource(Coordinate source);
};

#endif
