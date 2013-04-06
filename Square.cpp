#include "Square.h"
#include <iostream>

Square::Square() {}

Square::Square(int identifier, std::string start, std::string end, int amountOfPlayers, Coordinate position) {
  this->identifier = identifier;
  this->start = start;
  this->end = end;
  this->amountOfPlayers = amountOfPlayers;
  this->numberOfOccupants = 0;
  this->position = position;
  this->pieces.resize(this->amountOfPlayers);
}

std::string Square::putSquare() {
  for(int i=0; i<amountOfPlayers; i++) {
    if(this->pieces[i] != 0) {
      return (this->start + this->pieces[i]->putPiece() + this->end);
    }
  }
  return (this->start + " " + this->end);
}

bool Square::hasPiece() {
  return this->numberOfOccupants>0;
}

bool Square::addPiece(int player, Piece* piece) {
  if(player < this->amountOfPlayers
      && this->numberOfOccupants != this->amountOfPlayers
      && piece != 0
    ) {
    this->pieces[player] = piece;
    this->numberOfOccupants++;
    return true;
  }
  return false;
}

bool Square::removePiece(int player) {
  this->pieces[player] = 0;
  this->numberOfOccupants--;
  return true;
}

Coordinate Square::getPosition() {
  return this->position;
}

int Square::getIdentifier() {
  return this->identifier;
}

bool Square::hasPieceOwnedBy(int player) {
  if(this->pieces[player] != 0) {
    return true;
  }
  return false;
}

Piece* Square::getPiece(int player) {
  return this->pieces[player];
}