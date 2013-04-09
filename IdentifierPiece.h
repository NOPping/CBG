#ifndef IDENTIFIERPIECE_H
#define IDENTIFIERPIECE_H

#include "Piece.h"

class IdentifierPiece : virtual public Piece {
  protected:
    int identifier;
    
  public:
    IdentifierPiece(Player* owner, int identifier);
    ~IdentifierPiece();
    string print();
    int getIdentifier();
};

#endif
