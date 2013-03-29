#include "Square.h"

Square::Square() {}

Square::Square(int identifier, std::string representation) {
  this->identifier = identifier;
  this->representation = representation;
}

std::string Square::putSquare() {
  return this->representation;
}

bool Square::hasPieces() {
  return this->numberOfOccupants>0;
}

bool Square::addPiece() {
  // Fuck if i know.
}

bool Square::removePiece() {
  // Same as above
}