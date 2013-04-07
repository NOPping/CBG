#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Coordinate.h"

class Player;
class Piece {
    friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
    
    protected:
      int           type;
      
    public:
      Piece();
      Piece(Player* owner);
      int getType();
      bool setType(int type);
      Player* owner;
};

#endif
