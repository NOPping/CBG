#ifndef SNAKESANDLADDERS_H
#define SNAKESANDLADDERS_H

#include <string>
#include <vector>
#include <iostream>
#include "Game.h"
#include "SourcePiece.h"
#include "SystemPiece.h"

class SnakesAndLadders : public Game {
  private:
    bool isGameOver();
    void drawScreen();
    int rollDice();
    bool getMove();
    void resetPlayer(Coordinate current);
    bool executeMove(Coordinate current,int roll);
    Coordinate squareToCoordinate(int position);
    Square** squareRefs;
    Player* systemItems;
    bool printSnakeLadder(int x, int y); 
    
  public:
    SnakesAndLadders();
    ~SnakesAndLadders();
};

#endif
