#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <vector>
#include "Piece.h"
#include "Player.h"
#include "Coordinate.h"

using std::string;
using std::ostream;
using std::vector;

class Square {
    friend ostream& operator<<(ostream& out, const Square& square);
    
    private:
      int identifier;
      string start;
      string end;
      int amountOfPlayers;
      Coordinate position;
      int numberOfOccupants;
      vector <Piece *> pieces;

    public:
      Square();
      Square(int identifier, string start, string end, int amountOfPlayers, Coordinate position);
      bool hasPiece();
      bool addPiece(int Player, Piece* piece);
      bool removePiece(int player);
      bool hasPieceOwnedBy(int player);
      Piece* getPiece(int player);
      Coordinate getPosition();
      int getIdentifier();
};

#endif