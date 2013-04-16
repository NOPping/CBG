#include "Player.h"
#include "Piece.h"

Player::Player() {}

Player::Player(int amountOfTypes, vector<string> types, int maxPieces) {
  // Initialize member variables
  this->types = types;
  this->amountOfPieces = 0;
  this->amountOfTypes = amountOfTypes;
  this->maxPieces = maxPieces;
  this->pieces.resize(maxPieces);
  this->suspended=false;
}


std::string Player::getCharacter(int type) const {
  return types[type];
}

bool Player::hasType(int type) const {
  if(type<amountOfTypes) {
    return true;
  } else {
    return false;
  }
}

Piece* Player::addPiece() {
  Piece* piece = 0;
  if(amountOfPieces < maxPieces) {
    // Add new piece to vector, pass in this player.
    pieces[amountOfPieces] = new Piece(*this);
    piece = pieces[amountOfPieces];
    amountOfPieces++;
  }
  return piece;
}

// / Only used by snakes and ladders
Piece* Player::addPiece(Piece* insert) {
  Piece* piece = 0;
  if(amountOfPieces < maxPieces) {
    // Add insert to pieces vector
    pieces[amountOfPieces] = insert;
    piece = pieces[amountOfPieces];
    amountOfPieces++;
  }
  return piece;
}

bool Player::removePiece() {
  if(amountOfPieces > 0) {
    // Decrement amountOfPieces so the next piece added
    // will overwrite last piece
    amountOfPieces--;
    return true;
  } else {
    return false;
  }
}

int Player::getAmountOfPieces() const {
  return amountOfPieces;
}

Piece* Player::getPiece(int index) const {
  Piece* piece = 0;
  // If index is valid get the piece
  if(index >= 0 && index < maxPieces) {
    piece = pieces[index];
  }
  return piece;
}

Player::~Player() {
}
