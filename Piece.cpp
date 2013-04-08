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

Piece::Piece(Player* owner, Coordinate position) {
  this->position = position;
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

Piece::Piece(Player* owner, int identifier, Coordinate source, Coordinate destination) {
  this->position = position;
  this->owner = owner;
  this->type = 0;
  this->identifier = identifier;
  this->source = source;
  this->destination = destination;
}

Piece::Piece(Player* owner, int identifier, Coordinate source, Coordinate destination, int type) {
  this->position = position;
  this->owner = owner;
  this->type = type;
  this->identifier = identifier;
  this->source = source;
  this->destination = destination;
}

Piece::Piece(Player* owner, int identifier) {
  this->position = position;
  this->owner = owner;
  this->type = 0;
  this->identifier = identifier;
}

Piece::Piece(Player* owner, int identifier, int type) {
  this->position = position;
  this->owner = owner;
  this->type = type;
  this->identifier = identifier;
}

Coordinate Piece::getSource() {
  return source;
}

Coordinate Piece::getDestination() {
  return destination;
}

int Piece::getIdentifier() {
  return identifier;
}