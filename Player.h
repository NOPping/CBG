#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
  int  identifier;
  PlayerPieces    *pieces[];

public:
  Player();
  Player(int numberOfPieces, int identifier);
  int amountOfPieces();
  Piece addPiece(Coordinate position);
  bool removePiece();
};
 
#endif