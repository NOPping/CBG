#include "Piece.h"
#include "Player.h"


/**
 * Default constructor
 */
Piece::Piece() {
  this->type = 0;
}

/**
 * Constructor with paramaters for setting the position and owner.
 */
Piece::Piece(Coordinate* position,Player* owner) {
  this->position = position;
  this->owner = owner;
  this->type = 0;
}

/**
 * Returns the type of piece
 */
int Piece::getType() {
  return this->type;
}

/**
 * Allows for setting the piece type, returns true if setting was successful.
 * Otherwise false.
 */
bool Piece::setType(int type) {
  if((*this->owner).hasType(type)) {
    this->type = type;
    return true;
  } else {
    return false;
  }
}

/**
 * Returns the coordinates of the piece
 */
Coordinate Piece::getPosition() {
  return *position;
}

/**
 * Returns a character representation of the piece
 */
std::string Piece::putPiece() {
  return (*this->owner).getCharacter(this->type);
}