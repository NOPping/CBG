#ifndef CONNCTFOUR_H
#define CONNCTFOUR

#include <string>
#include <iostream>
#include "Game.h"

class ConnectFour : public Game {
  protected:
  	int [] columnSpace;
  	bool isTopRowFull();
  	bool isGameOver();
  	bool isFourInRow();
  	int checkNextSquare();
  public:
    ConnctFour();
};

#endif