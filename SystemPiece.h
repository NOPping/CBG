#ifndef SYSTEMPIECE_H
#define SYSTEMPIECE_H

#include "Piece.h"
#include "SourcePiece.h"
#include "DestinationPiece.h"
#include "IdentifierPiece.h"

class SystemPiece : public SourcePiece, public DestinationPiece, public IdentifierPiece {    
  public:
    SystemPiece(Player* owner, Coordinate source, Coordinate destination, int identifier);
    ~SystemPiece();
};

#endif
