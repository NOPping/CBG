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
//	int isGameOver();
	bool isValidMove(int destinationX);	
	void changeType();
	//added for compilation taken form checkers
	int   getPoint(string message, int range);
	bool  executeMove(Square* sourceSquare,Square* destinationSquare);
	bool  executeMove(Square* sourceSquare,Square* destinationSquare,Square* toJump);
	 int   isOver();
	 int   getOpposition();
	bool flanks(Coordinate* current);
bool isLegal(Coordinate* current,int iOffset,int jOffset);
	bool checkLine(Coordinate current,int rowOffset,int columnOffSet);
	//Square  checkNextSquare(Square* next, int nextColumnOffset, int nextRowOffset);
	// Constructor/Deconstructo
	public:
	Reversi();
	~Reversi();
  //players = new Player[this->amountOfPlayers];
  //this->grid = new Square*[rows];
  //for(int i=0; i<rows; i++) {
  //	this->grid[i] = new Square[columns];
  };


#endif
