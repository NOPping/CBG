#include "Piece.h"
#include "Player.h"


Piece::Piece() {
  this->type = 0;
}

Piece::Piece(Player* owner) {
  this->owner = owner;
  this->type = 0;
}

int Piece::getType() {
  return type;
}

bool Piece::setType(int type) {
  if((*owner).hasType(type)) {
    this->type = type;
    return true;
  } else {
    return false;
  }
}

void Piece::print() {
  std::cout << owner->getCharacter(type);
}