#include "Square.h"

Square::Square() {}

  
Square::Square(int* identifier, std::string* representation, int* amountOfPlayers, Coordinate* position) {
  this->identifier = identifier;
  this->representation = representation;
  this->amountOfPlayers = amountOfPlayers;
  this->position = position;
  
  // Current Doesn't work. Suggest using a vector.
  this->pieces = new Piece[*this->amountOfPlayers];
}

std::string* Square::putSquare() {
  return this->representation;
}

bool Square::hasPieces() {
  return this->numberOfOccupants>0;
}

bool Square::addPiece(int player, Piece* piece) {
  // TODO UNCOMPLETED.
  //if(player < *this->amountOfPlayers && 
    // this->numberOfOccupants != *this->amountOfPlayers) {
      //this->pieces[player] = piece;
      //this->numberOfOccupants++;
      //return true;
  //}
  return false;
}

bool Square::removePiece() {
  // TODO fill out this method.
  return false;
}

Coordinate* Square::getPosition() {
	return this->position;
}