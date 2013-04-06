#include "Player.h"
#include "Piece.h"

#include <iostream>

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
  if(this->amountOfPieces < this->maxPieces) {
    this->pieces[this->amountOfPieces] = Piece(this);
    piece = &pieces[this->amountOfPieces];
    this->amountOfPieces++;
  }
  return piece;
}

/**
 * Decrements the amountOfPieces count
 */
bool Player::removePiece() {
  if(this->amountOfPieces > 0) {
    this->amountOfPieces--;
    return true;
  } else {
    return false;
  }
}

int Player::getAmountOfPieces() {
  return this->amountOfPieces;
}
