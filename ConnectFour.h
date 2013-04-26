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
  /// Function to test if the next square is legal.
  bool isLegal(const Square& current,int yOffset,int xOffset) const;

  /// Int to storee the current state of the game.
  int  state;

  /// Function to request a move from the user and read it in
  /// Pass move to executeMove().
  bool getMove();
  
  /// Prompts with message to get a point between 0 and range.
  int getPoint(const string message, const int range) const;

  /// Prints out the board and all the players pieces.
  void  drawScreen() const;

  /// Function to return weather or not the game is over or not.
  int  isOver() const;

  /// Overloaded function to to return weather or not the game 
  /// is over or not.
  int  isOver(const Square& current) const;

  /// Function to test the top row of the board and see if every
  /// square has a piece on it.
  bool isDraw() const;

  /// Function to test if four player pieces lie in a row.
  bool fourInRow(const Square& current) const;

  /// Function to take a column and move a piece to the next 
  /// available slot in that column.
  bool executeMove(int x);

  /// Vector to hold how much pieces lie in each column.
  vector<int> columnHeight;

  /// recursive function to check the next square to see if it has a piece 
  /// to see if it's owned by current player.
  int  checkNext(const Square& next,int yOffset,int xOffset) const;
public:
  ConnectFour();
  ~ConnectFour();
};

#endif
