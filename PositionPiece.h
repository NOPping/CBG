#ifndef POSITIONPIECE_H
#define POSITIONPIECE_H

#include "Piece.h"

class PositionPiece : public Piece {
  protected:
    Coordinate source;
    
  public:
    PositionPiece(Player* owner, Coordinate Source);
    ~PositionPiece();
};

#endif
