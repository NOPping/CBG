/// Piece
/// @author Ian Duffy
/// @author Darren Brogan

#ifndef PIECE_H
#define PIECE_H

#include <iostream>

#include "Coordinate.h"

using std::ostream;

class Player;
class Piece {
    protected:
      /// The type of the piece.
      int type;

    public:
      /// Default constructor for a piece.
      Piece();
      
      /// Constructor with parameter to set an owner.
      Piece(Player* owner);
      
      /// Constructor with parameters to set an owner and type.
      Piece(Player* owner, int type);
      
      /// Deconstructor for a Piece.
      virtual ~Piece();
      
      /// Returns the type of piece.
      int getType();
      
      /// Sets the type of piece.
      bool setType(int type);
      
      /// Inserts the piece into the given ostream.
      virtual void print(ostream& os) const;
      
      /// Pointer to the pieces owner.
      Player* owner;
};

#endif
