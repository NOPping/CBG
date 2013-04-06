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
Piece::Piece(Player* owner) {
  //this->position = position;
  this->owner = owner;
  this->type = 0;
}

/**
 * Returns the type of piece
 */
int Piece::getType() {
  return type;
}

/**
 * Allows for setting the piece type, returns true if setting was successful.
 * Otherwise false.
 */
bool Piece::setType(int type) {
  if((*owner).hasType(type)) {
    this->type = type;
    return true;
  } else {
    return false;
  }
}