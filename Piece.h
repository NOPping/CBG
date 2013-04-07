#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Coordinate.h"

using std::string;

class Player;
class Piece {
    friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
    
    protected:
      int           type;
      string            identifier;
      Coordinate           source;
      Coordinate          destination;
      
    public:
      Piece();
      Piece(Player* owner);
      Piece(Player* owner, Coordinate position);
      Coordinate    position;
      int getType();
      bool setType(int type);
      Player* owner;
      
      Piece(Player* owner, string identifier, Coordinate source, Coordinate destination);
      std::string getIdentifier();
      Coordinate getSource();
      Coordinate getDestination();
};

#endif
