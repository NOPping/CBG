#ifndef SNAKESANDLADDERS_H
#define SNAKESANDLADDERS

#include <string>
#include <vector>
#include <iostream>
#include "Game.h"
#include "SystemPiece.h"

class SnakesAndLadders : public Game {
  private:
    void drawScreen();
    int rollDice();
    bool getMove();
    void resetPlayer(Coordinate current);
    bool executeMove(Coordinate current,int roll);
    Coordinate squareToCoordinate(int position);
    
    
  public:
    SnakesAndLadders();
    ~SnakesAndLadders();
};

#endif
