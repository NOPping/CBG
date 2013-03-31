#include "Square.h"
#include <iostream>

Square::Square() {}

Square::Square(int identifier, std::string representation, int amountOfPlayers, Coordinate position) {
  this->identifier = identifier;
  this->representation = representation;
  this->amountOfPlayers = amountOfPlayers;
  this->position = position;
  this->pieces.resize(this->amountOfPlayers);
}

std::string Square::putSquare() {
  for(int i=0; i<amountOfPlayers; i++) {
    if(this->pieces[i] != 0) {
      return this->pieces[i]->putPiece();
    }
  }
  return this->representation;
}

bool Square::hasPieces() {
  return this->numberOfOccupants>0;
}

bool Square::addPiece(int player, Piece* piece) {
  this->pieces[player] = piece;
  this->numberOfOccupants++;
  return true;
  // TODO UNCOMPLETED.
  //if(player < this->amountOfPlayers &&
  // this->numberOfOccupants != this->amountOfPlayers) {
  //this->pieces[player] = piece;
  //this->numberOfOccupants++;
  //return true;
  //}
  //return false;
}

bool Square::removePiece() {
  // TODO fill out this method.
  return false;
}

Coordinate Square::getPosition() {
  return this->position;
}