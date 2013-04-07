#ifndef SYSTEMPIECE_H
#define SYSTEMPIECE_H

#include <string>
#include "Square.h"
#include "Piece.h"

using std::string;

class SystemPiece : public Piece {
    private:
      string            identifier;
      Square*           source;
      Square*           destination;
      
    public:
      SystemPiece(Player* owner, string identifier, Square* source, Square* destination);
      std::string getIdentifier();
      Square* getSource();
      Square* getDestination();
};

#endif
