#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <vector>
#include "Piece.h"
#include "Player.h"
#include "Coordinate.h"

class Square {
    friend std::ostream& operator<<(std::ostream& out, const Square& square);
    
    private:
      int identifier;
      std::string start;
      std::string end;
      int amountOfPlayers;
      Coordinate position;
      int numberOfOccupants;
      std::vector <Piece *> pieces;

    public:
      Square();
      Square(int identifier, std::string start, std::string end, int amountOfPlayers, Coordinate position);
      bool hasPiece();
      bool addPiece(int Player, Piece* piece);
      bool removePiece(int player);
      bool hasPieceOwnedBy(int player);
      Piece* getPiece(int player);
      Coordinate getPosition();
      int getIdentifier();
};

#endif