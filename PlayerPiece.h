#ifndef PLAYERPIECE_H
#define PLAYERPIECE_H

class PlayerPiece : public Piece {
private:
  Player *owner;
public:
  PlayerPiece();
  PlayerPiece(int id, Player* owner);
};
 
#endif