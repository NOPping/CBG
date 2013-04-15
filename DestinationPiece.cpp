/// A Piece with a destination.
/// @author Ian Duffy

#include "DestinationPiece.h"

DestinationPiece::DestinationPiece(Player* owner, Coordinate destination)
: Piece(owner) {
  this->destination = destination;
}

/// Returns the destination.
Coordinate DestinationPiece::getDestination() {
  return destination;
}

/// Sets the destination coordinate.
void DestinationPiece::setDestination(Coordinate destination) {
  this->destination = destination;
}