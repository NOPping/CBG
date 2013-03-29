#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Coordinate.h"

class Piece;
class Player {
    private:
      int             amountOfPieces;
      int             maxPieces;
      int*            amountOfTypes;
      std::string*    types;
      Piece*          pieces;

    public:
      Player();
      Player(int* amountOfTypes, std::string* types, int maxPieces);
      Piece* addPiece(Coordinate position);
      bool removePiece();
      bool hasType(int type);
      std::string getCharacter(int type);
      int getAmountOfPieces();
};

#endif