#include "SourcePiece.h"

SourcePiece::SourcePiece(Player* owner, Coordinate source) 
                         : Piece(owner) {
    this->source = source;
}

SourcePiece::~SourcePiece() {}