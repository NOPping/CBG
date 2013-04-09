#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <string>
#include <iostream>
#include "Game.h"
#include "Square.h"
#include "Player.h"

class ConnectFour : public Game {
  private:
    bool getMove();
    void drawScreen();

  	bool  topRowFull();
  	bool  isGameOver(Square current);
  	bool  fourInRow(Square current);
    bool  isValidMove(int destinationX);
    bool  executeMove(int destinationX);
    
    int   *columnSpace;
  	int   checkNextSquare(Square next, int nextColumnOffset, int nextRowOffset);
  public:
    ConnectFour();
};

#endif