#include "IdentifierPiece.h"

IdentifierPiece::IdentifierPiece(Player* owner, int identifier)
                : Piece(owner) {
    this->identifier = identifier;
}

IdentifierPiece::~IdentifierPiece() {}

void IdentifierPiece::print(ostream& os) const{
  Piece::print(os);
  os << identifier;
}

int IdentifierPiece::getIdentifier() {
  return identifier;
}