#ifndef PIECE_H
#define PIECE_H

class Piece {
    private:
    Coordinate   Position;
    int 				type;

    public:
    int getType();
    bool setType(int type);
    Coordinate getPosition();
};

#endif