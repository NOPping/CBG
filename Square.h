#ifndef SQUARE_H
#define SQUARE_H

class Square {
    private:
      string identifier;
      int numberOfOccupants;
      Piece *pieces;

    public:
      Square(int numberOfPlayers);
      bool hasPieces();
      bool addPiece();
      bool removePiece();
      Piece[] getPieces();
};

#endif