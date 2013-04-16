/// A square makes up the grid/board for each game.
/// @author Ian Duffy
/// @author Darren Brogan

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
      /// Identifier for the square.
      int identifier;
      
      /// The length of the pieces vector.
      int amountOfPlayers;
      
      /// The number of people currently on the square.
      int numberOfOccupants;
      
      /// The starting string of the square.
      string start;
      
      /// The closing string of the square.
      string end;
      
      /// Pointers to all the pieces on the square.
      vector<Piece *> pieces;
      
      /// The coordinate of the square.
      Coordinate position;

    public:
      Square();
      Square(int identifier, string start, string end, int amountOfPlayers, Coordinate position);
      
      /// Returns the square's identifier.
      int getIdentifier();
      
      /// Returns whether or not the square has a piece on it.
      bool hasPiece();
      
      /// Adds a piece to the square.
      bool addPiece(int Player, Piece* piece);
      
      /// Removes a piece from the square.
      bool removePiece(int player);
      
      /// Returns whether or not the square has a piece owned by player on it.
      bool hasPieceOwnedBy(int player) const;
      
      /// Returns the start string of a square.
      string getStart();
      
      /// Returns the closing string of a square.
      string getEnd();
      
      /// Returns the piece on the square owned by player.
      Piece* getPiece(int player);
      
      /// Returns the position of the square.
      Coordinate getPosition() const;
};

#endif
