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
    bool  executeMove(Square* sourceSquare,Square* destinationSquare);
  
  public:
    Checkers();
    ~Checkers();
};

#endif