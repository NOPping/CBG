#ifndef SOURCEPIECE_H
#define SOURCEPIECE_H

#include "Piece.h"

class SourcePiece : virtual public Piece {
  protected:
    Coordinate source;
    
  public:
    SourcePiece(Player* owner, Coordinate source);
    Coordinate getSource();
    void setSource(Coordinate source);
    virtual ~SourcePiece();
};

#endif
