#ifndef PIECE_H
#define PIECE_H

#include <iostream>

#include "Coordinate.h"

using std::ostream;

class Player;
class Piece {
      protected:
      // Protected Data
      int type;

    public:
      // Constructors
      Piece();
      Piece(Player* owner);
      Piece(Player* owner, int type);
      
      virtual ~Piece();
      
      // Public functions
      int getType();
      bool setType(int type);
      virtual void print(ostream& os) const;
      
      // Public Data
      Player* owner;
};

#endif
