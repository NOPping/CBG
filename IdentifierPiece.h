/// A Piece with an identifier.
/// @author Ian Duffy.

#ifndef IDENTIFIERPIECE_H
#define IDENTIFIERPIECE_H

#include "Piece.h"

class IdentifierPiece : virtual public Piece {
  protected:
    /// The piece's identifier
    int identifier;
    
  public:
    IdentifierPiece(Player* owner, int identifier);
    
    /// Override the print function to include the identifier.
    virtual void print(ostream& os) const;
    
    /// Returns the identifier.
    int getIdentifier();
};

#endif
