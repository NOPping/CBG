#include "SourcePiece.h"

SourcePiece::SourcePiece(Player* owner, Coordinate source)
: Piece(owner) {
  this->source = source;
}

Coordinate SourcePiece::getSource() {
  return source;
}

void SourcePiece::setSource(Coordinate source) {
  this->source = source;
}

SourcePiece::~SourcePiece() {}