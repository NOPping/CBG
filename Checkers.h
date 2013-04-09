#ifndef CHECKERS_H
#define CHECKERS_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Game.h"

class Checkers : public Game {
  private:
    int   getOpposition();
    int   getPoint(string message, int range);
    bool  getMove();
    bool  executeMove(Square* sourceSquare,Square* destinationSquare);
    bool  executeMove(Square* sourceSquare,Square* destinationSquare,Square* toJump);
    void  drawScreen();
    
  public:
    Checkers();
    ~Checkers();
};

#endif