#ifndef IDENTIFIERPIECE_H
#define IDENTIFIERPIECE_H

#include "Piece.h"

class IdentifierPiece : virtual public Piece {
  protected:
    int identifier;
    
  public:
    IdentifierPiece(Player* owner, int identifier);
    ~IdentifierPiece();
    virtual void print(ostream& os) const;
    int getIdentifier();
};

#endif
