#include "DestinationPiece.h"

DestinationPiece::DestinationPiece(Player* owner, Coordinate destination) 
                         : Piece(owner) {
    this->destination = destination;
}

DestinationPiece::~DestinationPiece() {}