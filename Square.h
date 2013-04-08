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
    
    protected:
      // Protected Data
      int             identifier;
      int             amountOfPlayers;
      int             numberOfOccupants;
      string          start;
      string          end;
      vector<Piece *> pieces;
      Coordinate      position;

    public:
      // Constructors
      Square();
      Square(int identifier, string start, string end, int amountOfPlayers, Coordinate position);
      
      // Public Functions
      int         getIdentifier();
      bool        hasPiece();
      bool        addPiece(int Player, Piece* piece);
      bool        removePiece(int player);
      bool        hasPieceOwnedBy(int player);
      string      getStart();
      string      getEnd();
      Piece*      getPiece(int player);
      Coordinate  getPosition();
};

#endif