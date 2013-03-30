#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Piece.h"
#include "Coordinate.h"

class Coordinate;
class Square {
    private:
      Coordinate position;
      int identifier;
      std::string representation;
      int numberOfOccupants;
      Piece* pieces;

    public:
      Square();
      Square(int identifier, std::string representation, Coordinate position);
      std::string putSquare();
      bool hasPieces();
      bool addPiece();
      bool removePiece();
      Piece* getPieces();
      Coodinate getPosition();
};

#endif
