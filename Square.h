#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Piece.h"

class Square {
    private:
      std::string identifier;
      int numberOfOccupants;
      Piece *pieces;

    public:
      Square(int numberOfPlayers);
      bool hasPieces();
      bool addPiece();
      bool removePiece();
      Piece* getPieces();
};

#endif