#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Piece.h"
#include "Coordinate.h"

class Square {
    private:
      int identifier;
      std::string representation;
      int amountOfPlayers;
      Coordinate position;
      int numberOfOccupants;
      Piece* pieces;

    public:
      Square();
      Square(int identifier, std::string representation, int amountOfPlayers, Coordinate position);
      std::string putSquare();
      bool hasPieces();
      bool addPiece(int Player, Piece* piece);
      bool removePiece();
      Coordinate getPosition();
      Piece* getPieces();
};

#endif