#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Coordinate.h"

class Player;
class Piece {
    private:
      //Coordinate*   position;
      int           type;
      
    public:
      Piece();
      Piece(Player* owner);
      int getType();
      bool setType(int type);
      std::string putPiece();
      //Coordinate getPosition();
      Player* owner;
};

#endif
