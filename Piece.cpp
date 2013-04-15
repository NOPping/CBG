/// Piece
/// @author Ian Duffy
/// @author Darren Brogan


#include "Piece.h"
#include "Player.h"

/// Default constructor for a piece.
Piece::Piece() {
  this->type = 0;
}

/// Constructor with parameter to set an owner.
Piece::Piece(Player* owner) {
  this->owner = owner;
  this->type = 0;
}

/// Returns the type of piece.
int Piece::getType() {
  return type;
}

/// Sets the type of piece.
bool Piece::setType(int type) {
  if((*owner).hasType(type)) {
    this->type = type;
    return true;
  } else {
    return false;
  }
}

/// Inserts the piece into the given ostream.
void Piece::print(ostream& os) const {
  os << owner->getCharacter(type);
}

/// Deconstructor for a Piece.
Piece::~Piece() {
  delete owner;
}