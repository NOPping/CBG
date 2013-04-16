#ifndef REVERSI_H
#define REVERSI

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Game.h"
class Reversi:public Game{
	bool getMove();
	void drawScreen();
	bool isValidMove(int destinationX);	
	int   getPoint(string message, int range);
	bool  executeMove(Square* sourceSquare,Square* destinationSquare);
	bool  executeMove(Square* sourceSquare,Square* destinationSquare,Square* toJump);
	int   isOver();
	int   getOpposition();
	bool flanks(Coordinate* current);
bool isLegal(Coordinate* current,int iOffset,int jOffset);
	bool checkLine(Coordinate current,int rowOffset,int columnOffSet);
	public:
	Reversi();
	~Reversi();

  };


#endif
