#ifndef REVERSI_H
#define REVERSI

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Game.h"
class Reversi:public Game {

  bool getMove();
  void drawScreen() const;
  bool isValidMove(int destinationX) const;  
  int  getPoint(string message, int range) const;
  bool executeMove(Square& destinationSquare)const;
  //bool executeMove(Square* sourceSquare,Square* destinationSquare,Square* toJump) const;
  int  isOver() const;
  int  getOpposition() const;
  bool checkNext(Square &current,int yOffset,int xOffset,bool flip) const;
  bool flanks(Square current,bool flip) const;
  bool isLegal(Coordinate current,int iOffset,int jOffset) const;
  bool checkLine(Coordinate current,int rowOffset,int columnOffSet,bool flip) const;
public:
  Reversi();
};


#endif
