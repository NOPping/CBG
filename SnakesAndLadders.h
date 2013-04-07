#ifndef SNAKESANDLADDERS_H
#define SNAKESANDLADDERS

#include <string>
#include <vector>
#include <iostream>
#include "Game.h"

class SnakesAndLadders : public Game {
  private:
    bool isGameOver();
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
