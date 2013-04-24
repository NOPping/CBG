/// Player
/// @author Ian Duffy
/// @author Darren Brogan

#include "Player.h"
#include "Piece.h"

#include <iostream>

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

/// Returns a string from pieces vector at index type.
std::string Player::getCharacter(int type) const {
  return types[type];
}

/// Check if pieces vector at index type is empty
bool Player::hasType(int type) const {
  if(type<amountOfTypes) {
    return true;
  } else {
    return false;
  }
}

bool Player::hasRoomForPiece() const {
  return(amountOfPieces < maxPieces);
}

/// Add pieces to the pieces vector.
Piece& Player::addPiece() {
  pieces[amountOfPieces] = new Piece(*this);
  Piece& piece = *pieces[amountOfPieces];
  amountOfPieces++;
  return piece;
}

/// Add pieces to the pieces vector at index.
/// Only used by snakes and ladders
Piece& Player::addPiece(Piece* insert) {
  // Add insert to pieces vector
  pieces[amountOfPieces] = insert;
  Piece& piece = *pieces[amountOfPieces];
  amountOfPieces++;
  return piece;
}

/// Remove Piece from the player and return a bollean to identify
/// if it succeded or failed.
bool Player::removePiece(Piece *toBeRemoved) {
  if(amountOfPieces > 0) {
    // replace the piece to be removed with the piece at the end of the
    // vector and decrememnt 
    int index=-1;

    // Find our piece
    for(int i=0;i<amountOfPieces;i++) {
      if(toBeRemoved == pieces[i]) {
        delete pieces[i];
        index=i;
        break;
      }
    }
    
    if(index=-1) return false;
    
    // Decrease amount of pieces by one.
    amountOfPieces--;

    // Move all pieces back.
    for(int i=index;i<amountOfPieces;i++) {
      pieces[i] = pieces[i+1]; 
    }
    
    // Delete the last index
    pieces[amountOfPieces] = NULL;
    
    return true;
  } else {
    return false;
  }
}

/// Returns the amount of pieces
int Player::getAmountOfPieces() const {
  return amountOfPieces;
}

/// Returns a reference to the piece in the pieces vector at index.
Piece& Player::getPiece(int index) const {
  Piece& piece = *pieces[index];
  return piece;
}

Player::~Player() {
  for(int i = 0; i<maxPieces; i++) {
    delete pieces[i];
  }
}
