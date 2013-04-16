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
  bool isLegal(const Square& current,int nextRowOffset,int nextColumnOffset) const;
  int  state;
  bool getMove();
  void drawScreen() const;
  int  isOver() const;
  int  isOver(const Square& current) const;
  bool topRowFull() const;
  bool fourInRow(const Square& current) const;
  bool executeMove(int destinationX);
  vector<int> columnSpace;
  int  checkNext(const Square& next,int nextRowOffset,int nextColumnOffset) const;
public:
  ConnectFour();
  ~ConnectFour();
};

#endif
