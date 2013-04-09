#include "IdentifierPiece.h"

IdentifierPiece::IdentifierPiece(Player* owner, int identifier)
                : Piece(owner) {
    this->identifier = identifier;
}

IdentifierPiece::~IdentifierPiece() {}

void IdentifierPiece::print() {
  Piece::print();
  std::cout << identifier;
}

int IdentifierPiece::getIdentifier() {
  return identifier;
}