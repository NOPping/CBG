/// A square makes up the grid/board for each game.
/// @author Ian Duffy
/// @author Darren Brogan

#include "Square.h"

Square::Square() {}

Square::Square(int identifier, string start, string end, int amountOfPlayers,
               Coordinate position) {
  this->identifier = identifier;
  this->start = start;
  this->end = end;
  this->amountOfPlayers = amountOfPlayers;
  this->numberOfOccupants = 0;
  this->position = position;
  this->pieces.resize(this->amountOfPlayers);
}

/// Returns whether or not the square has a piece on it.
bool Square::hasPiece() {
  return numberOfOccupants>0;
}

/// Adds a piece to the square.
bool Square::addPiece(int player, Piece& piece) {
  if(player < amountOfPlayers
      && numberOfOccupants != amountOfPlayers
    ) {
    pieces[player] = &piece;
    numberOfOccupants++;
    return true;
  }
  return false;
}

/// Removes a piece from the square.
bool Square::removePiece(int player) {
  pieces[player]->owner->removePiece(pieces[player]);
  pieces[player] = 0;
  numberOfOccupants--;
  return true;
}

/// Returns the piece on the square owned by player.
Coordinate& Square::getPosition() const {
  return (Coordinate&)position;
}

/// Returns the square's identifier.
int Square::getIdentifier() const {
  return identifier;
}

/// Returns whether or not the square has a piece owned by player on it.
bool Square::hasPieceOwnedBy(int player) const {
  if(pieces[player] != 0) {
    return true;
  }
  return false;
}


Piece& Square::getPiece(int player) {
  return *(pieces[player]);
}

/// Returns the start string of a square.
string Square::getStart() {
  return start;
}

/// Returns the closing string of a square.
string Square::getEnd() {
  return end;
}
