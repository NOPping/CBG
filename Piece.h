#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Coordinate.h"

class Player;
class Piece {
    private:
      Player*       owner;
      Coordinate*   position;
      int           type;
      
    public:
      Piece();
      Piece(Coordinate* position,Player* owner);
      int getType();
      bool setType(int type);
      std::string putPiece();
      Coordinate getPosition();
      Player getOwner();
};

#endif
