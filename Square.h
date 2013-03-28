#ifndef PIECE_H
#define PIECE_H
 
class Square {
private:
  string identifier;
  int numberOfOccupants;
  Piece *pieces[];

public:
  Square(int numberOfPlayers);
  bool hasPieces();
  bool addpiece();
  bool removePiece();
  Piece[] getPieces();
};
 
#endif