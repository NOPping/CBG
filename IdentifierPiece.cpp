#include "IdentifierPiece.h"

IdentifierPiece::IdentifierPiece(Player* owner, int identifier)
                : Piece(owner) {
    this->identifier = identifier;
}

IdentifierPiece::~IdentifierPiece() {}

string IdentifierPiece::print() {
  stringstream out;
  out << Piece::print() << identifier;
  return out.str();
}

int IdentifierPiece::getIdentifier() {
  return identifier;
}