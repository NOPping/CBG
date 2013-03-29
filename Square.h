#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Piece.h"

class Square {
    private:
      int identifier;
      std::string representation;
      int numberOfOccupants;
      Piece* pieces;

    public:
      Square();
      Square(int identifier, std::string representation);
      std::string putSquare();
      bool hasPieces();
      bool addPiece();
      bool removePiece();
      Piece* getPieces();
};

#endif