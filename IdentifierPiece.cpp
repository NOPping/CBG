/// A Piece with an identifier.
/// @author Ian Duffy.

#include "IdentifierPiece.h"

IdentifierPiece::IdentifierPiece(Player& owner, int identifier)
: Piece(owner) {
  this->identifier = identifier;
}

/// Override the print function to include the identifier.
void IdentifierPiece::print(ostream& os) const {
  Piece::print(os);
  os << identifier;
}

/// Returns the identifier.
int IdentifierPiece::getIdentifier() {
  return identifier;
}
