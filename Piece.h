#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:
      Player       owner;
      Coordinate   Position;
      int          type;

    public:
      Piece(Coordinate position, Player owner);
      int getType();
      bool setType(int type);
      Coordinate getPosition();
};

#endif
