/// A piece with made up of a SourcePiece, DestinationPiece and IdentifierPiece.
/// @author Ian Duffy
/// @author Darren Brogan

#ifndef SYSTEMPIECE_H
#define SYSTEMPIECE_H

#include "Piece.h"
#include "SourcePiece.h"
#include "DestinationPiece.h"
#include "IdentifierPiece.h"

class SystemPiece : public SourcePiece, public DestinationPiece, public IdentifierPiece {    
  public:
    SystemPiece(Player* owner, Coordinate source, Coordinate destination,
                int identifier);
};

#endif
