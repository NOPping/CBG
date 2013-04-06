#ifndef SYSTEMPIECE_H
#define SYSTEMPIECE_H

#include <string>
#include "Coordinate.h"
#include "Piece.h"

class SystemPiece : public Piece {
    private:
      Coordinate*   position;
      Coordinate*   destination;
      
    public:
      Coordinate* getPosition();
      Coordinate* getDestination();
};

#endif
