#ifndef CONNCTFOUR_H
#define CONNCTFOUR

#include <string>
#include <iostream>
#include "Game.h"
#include "Square.h"
#include "Player.h"

class ConnectFour : public Game {
  private:

  	int *columnSpace;
  	bool topRowFull();
  	bool isGameOver(Square current);
  	bool fourInRow(Square current);
  	int checkNextSquare(Square next, int nextColumnOffset, int nextRowOffset);
  	bool isValidMove(int destinationX);
  public:
    ConnectFour();
};

#endif