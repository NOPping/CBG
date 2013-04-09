#include "DestinationPiece.h"

DestinationPiece::DestinationPiece(Player* owner, Coordinate destination) 
                         : Piece(owner) {
    this->destination = destination;
}


Coordinate DestinationPiece::getDestination() {
  return destination;
}

void DestinationPiece::setDestination(Coordinate destination) {
  this->destination = destination;
}

DestinationPiece::~DestinationPiece() {}