/// A Piece with a source.
/// @author Ian Duffy

#include "SourcePiece.h"

SourcePiece::SourcePiece(Player& owner, Coordinate source)
: Piece(owner) {
  this->source = source;
}

/// Returns the source.
Coordinate SourcePiece::getSource() {
  return source;
}

/// Sets the source coordinate.
void SourcePiece::setSource(Coordinate source) {
  this->source = source;
}
