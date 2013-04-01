#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Coordinate.h"

class Piece;
class Player {
    private:
      int                         amountOfPieces;
      int                         maxPieces;
      int                         amountOfTypes;
      std::vector<std::string>    types;
      std::vector<Piece>          pieces;

    public:
      Player();
      Player(int amountOfTypes, std::vector<std::string> types, int maxPieces);
      Piece* addPiece();
      bool removePiece();
      bool hasType(int type);
      std::string getCharacter(int type);
      int getAmountOfPieces();
};

#endif