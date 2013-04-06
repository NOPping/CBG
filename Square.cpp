#include "Square.h"

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

bool Square::hasPiece() {
  return numberOfOccupants>0;
}

bool Square::addPiece(int player, Piece* piece) {
  if(player < amountOfPlayers
      && numberOfOccupants != amountOfPlayers
      && piece != 0
    ) {
    pieces[player] = piece;
    numberOfOccupants++;
    return true;
  }
  return false;
}

bool Square::removePiece(int player) {
  pieces[player] = 0;
  numberOfOccupants--;
  return true;
}

Coordinate Square::getPosition() {
  return position;
}

int Square::getIdentifier() {
  return identifier;
}

bool Square::hasPieceOwnedBy(int player) {
  if(pieces[player] != 0) {
    return true;
  }
  return false;
}

Piece* Square::getPiece(int player) {
  return pieces[player];
}