/// A Piece with a destination.
/// @author Ian Duffy

#ifndef DESTINATIONPIECE_H
#define DESTINATIONPIECE_H

#include "Piece.h"

class DestinationPiece : virtual public Piece {
  protected:
    /// Coordinate containing the destination.
    Coordinate destination;
    
  public:
    DestinationPiece(Player* owner, Coordinate destination);
    
    /// Returns the destination
    Coordinate getDestination();
    
    /// Sets the destination coordinate.
    void setDestination(Coordinate destination);
};

#endif
