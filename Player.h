#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Coordinate.h"

using std::string;
using std::vector;

class Piece;
class Player {
    protected:
      // Protected Data
      int             amountOfPieces;
      int             maxPieces;
      int             amountOfTypes;
      vector<string>  types;
      vector<Piece*>  pieces;

    public:
      // Constructor
      Player();
      Player(int amountOfTypes, vector<string> types, int maxPieces);
      
      // Public functions
      int     getAmountOfPieces();
      bool    removePiece();
      bool    hasType(int type);
      string  getCharacter(int type);
      Piece*  addPiece();
      Piece*  addPiece(Piece* insert);
      Piece*  getPiece(int index);
      bool suspended;
};

#endif