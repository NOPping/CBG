#ifndef CHECKERS_H
#define CHECKERS

#include <string>
#include <vector>
#include <iostream>
#include "Game.h"

class Checkers : public Game {
  private:
    bool  getMove();
    void  drawScreen();
    int   getOpposition();
    bool  executeMove(Square* sourceSquare,Square* destinationSquare);
    bool  executeMove(Square* sourceSquare,Square* destinationSquare,Square* toJump);
  
  public:
    Checkers();
    ~Checkers();
};

#endif