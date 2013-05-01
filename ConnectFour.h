/// ConnectFour Game.
/// @author Darren Brogan

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <algorithm>

#include "Game.h"
#include "Square.h"
#include "Player.h"

class ConnectFour : public Game {
  private:
  /// Function to test if the next square is legal.
  bool isLegal(const Square& current,int yOffset,int xOffset) const;

  /// Int to store the current state of the game.
  int  state;

  /// Function to request a move from the user and read it in
  /// Pass move to executeMove().
  bool getMove();

  /// Prompts with message to get a point between 0 and range.
  int getPoint(const string message, const int range) const;

  /// Prints out the board and all the players pieces.
  void  drawScreen() const;

  /// Overloaded function to to return weather or not the game is over.
  int  isOver();

  int  isOver(const Square& current) const;

  /// Functions to test if the game has ended in a draw
  bool isDraw() const;

  /// Function to get the max amount of pieces in a line around the piece added
  /// returns weather or not the number is greater than 3, signifying a win.
  bool fourInRow(const Square& current) const;

  /// Function to take an int representing a column and move a piece to the
  /// next available slot in that column.
  bool executeMove(int x);

  /// Vector to hold how much pieces lie in each column.
  vector<int> columnHeight;

  /// Recursive function to check the next square to see if it has a piece
  /// to see if it's owned by current player.
  int  checkNext(const Square& next,int yOffset,int xOffset) const;

  /// Returns the opposition.
  int getOpposition() const;

  public:
  ConnectFour();
  ~ConnectFour();
};

#endif
