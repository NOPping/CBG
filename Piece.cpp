#include "Piece.h"
#include "Coordinate.h"

Piece(Coordinate position, Player owner) {
  this.position = position;
  this.owner = owner;
}

Coordinate getPosition() {
  return Position;
}

int getType() {
  return type;
}

void setType(int type) {
  this.type = type;
}