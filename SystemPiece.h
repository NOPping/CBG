#ifndef SYSTEMPIECE_H
#define SYSTEMPIECE_H

#include "PositionPiece.h"

class SystemPiece : public PositionPiece {
  protected:
    int identifier;
    Coordinate destination;
    
  public:
    SystemPiece(Player* owner, Coordinate source, Coordinate destination, int identifer);
    ~SystemPiece();
};

#endif
