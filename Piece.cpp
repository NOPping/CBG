/// Piece
/// @author Ian Duffy
/// @author Darren Brogan


#include "Piece.h"
#include "Player.h"

Piece::Piece() {
  this->type = 0;
}

Piece::Piece(Player& owner) {
  this->owner = &owner;
  this->type = 0;
}

int Piece::getType() const {
  return type;
}

/// Sets the type of piece.
bool Piece::setType(int type) {
  if(owner->hasType(type)) {
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

Piece::~Piece() {

}
