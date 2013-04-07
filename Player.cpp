#include "Player.h"
#include "Piece.h"

/**
 * Default constructor
 */
Player::Player() {}

/**
 * Constructor with paramaters for setting the amount of different piece types,
 * the character representation for each type and the max amount of pieces the
 * player may have.
 */
Player::Player(int amountOfTypes, std::vector<std::string> types, int maxPieces) {
  this->consecutiveSixes = 0;
  this->types = types;
  this->amountOfPieces = 0;
  this->amountOfTypes = amountOfTypes;
  this->maxPieces = maxPieces;
  this->pieces.resize(maxPieces);
  this->canMove = true;
  this->sixes = 0;
}

/**
 * Returns the string stored in the types array at index location type.
 * Otherwise it returns NULL.
 */
std::string Player::getCharacter(int type) {
  return types[type];
}

bool Player::hasType(int type) {
  if(type<amountOfTypes) {
    return true;
  } else {
    return false;
  }
}

/**
 * Creates a piece for the player and returns a reference to the piece.
 */
Piece* Player::addPiece() {
  Piece* piece = 0;
  if(amountOfPieces < maxPieces) {
    pieces[amountOfPieces] = Piece(this);
    piece = &pieces[amountOfPieces];
    amountOfPieces++;
  }
  return piece;
}

/**
 * Creates a piece for the player and returns a reference to the piece.
 */
Piece* Player::addPiece(Coordinate position) {
  Piece* piece = 0;
  if(amountOfPieces < maxPieces) {
    pieces[amountOfPieces] = Piece(this,position);
    piece = &pieces[amountOfPieces];
    amountOfPieces++;
  }
  return piece;
}

/**
 * Decrements the amountOfPieces count
 */
bool Player::removePiece() {
  if(amountOfPieces > 0) {
    amountOfPieces--;
    return true;
  } else {
    return false;
  }
}

int Player::getAmountOfPieces() {
  return amountOfPieces;
}

Piece* Player::getPiece(int index) {
  Piece* piece = 0;
  if(index >= 0 && index < maxPieces) {
    piece = &pieces[index];
  }
  return piece;
}