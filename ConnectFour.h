#ifndef CONNCTFOUR_H
#define CONNCTFOUR

#include <string>
#include <iostream>
#include "Game.h"
#include "Square.h"
#include "Player.h"

using std::vector;

class ConnectFour : public Game {

private:
  bool         isLegal(Square* current,int nextRowOffset,int nextColumnOffset);
  int 	       state;
  bool         getMove();
  void         drawScreen();
  int          isOver();
  int          isOver(Square* current);
  bool         topRowFull();
  bool         fourInRow(Square * current);
  bool         executeMove(int destinationX);
  vector<int>  columnSpace;
  int          checkNext(Square* next,int nextRowOffset,int nextColumnOffset);
public:
  ConnectFour();
};

#endif
