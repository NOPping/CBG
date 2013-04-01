#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <vector>
#include "Piece.h"
#include "Player.h"
#include "Coordinate.h"

class Square {
    private:
      int identifier;
      std::string representation;
      int amountOfPlayers;
      Coordinate position;
      int numberOfOccupants;
      std::vector <Piece *> pieces;

    public:
      Square();
      Square(int identifier, std::string representation, int amountOfPlayers, Coordinate position);
      std::string putSquare();
      bool hasPiece();
      bool addPiece(int Player, Piece* piece);
      bool removePiece(int player);
      bool hasPieceOwnedBy(int player);
      Piece* getPiece(int player);
      Coordinate getPosition();
      int getIdentifier();
};

#endif