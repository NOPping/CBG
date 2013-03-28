#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:
    Player       owner;
    Coordinate   Position;
    int          type;

    public:
    Player(Coordinate position, Player owner);
    int getType();
    bool setType(int type);
    Coordinate getPosition();
};

#endif
