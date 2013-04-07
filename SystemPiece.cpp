#include "SystemPiece.h"

SystemPiece::SystemPiece(Player* owner, string identifier, Square* source, Square* destination) {
  this->position = position;
  this->owner = owner;
  this->type = 0;
  this->identifier = identifier;
  this->source = source;
  this->destination = destination;
}

Square* SystemPiece::getSource() {
  return source;
}

Square* SystemPiece::getDestination() {
  return destination;
}

std::string SystemPiece::getIdentifier() {
  return identifier;
}