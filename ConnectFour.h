#ifndef CONNCTFOUR_H
#define CONNCTFOUR

#include <string>
#include <iostream>
#include "Game.h"

class ConnectFour : public Game {
  private:
  	int* columnSpace;
  	bool topRowFull();
  	bool isGameOver();
  	bool fourInRow();
  	int checkNextSquare(Square current, Square next, int nextColumnOffset, int nextRowOffset);
  public:
    ConnectFour();
};

#endif