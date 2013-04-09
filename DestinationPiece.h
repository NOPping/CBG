#ifndef DESTINATIONPIECE_H
#define DESTINATIONPIECE_H

#include "Piece.h"

class DestinationPiece : virtual public Piece {
  protected:
    Coordinate destination;
    
  public:
    DestinationPiece(Player* owner, Coordinate destination);
    Coordinate getDestination();
    void setDestination(Coordinate destination);
    ~DestinationPiece();
};

#endif
