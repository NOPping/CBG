#include "PositionPiece.h"

PositionPiece::PositionPiece(Player* owner, Coordinate Source) : Piece(owner) {
  this->source = source;
}