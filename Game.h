/// Base foundation for all of the games.
/// @author Ian Duffy
/// @author Darren Brogan

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "Square.h"
#include "Player.h"
#include "Colors.h"


class Game {
protected:
  /// Holds the position in the players array of the current player.
  int currentPlayer;
  
  /// Holds all of the games players.
  Player** players;
  
  /// Holds all of the squares that makes up the games grid.
  Square** grid;
  
  /// Holds the length of the players array
  const int amountOfPlayers;
  
  /// Holds the amount of columns within the grid.
  const int columns;
  
  /// Holds the amount of rows within the grid.
  const int rows;
  
  /// Clears the terminal window.
  void clearScreen() const;
  
  /// Gets input from the player detailing which move they wish to make
  virtual bool getMove() = 0;
  
  /// Draws out the board as required.
  virtual void drawScreen() const = 0;
  
  /// Defines whether or not the game is over.
  virtual int isOver() const =0;
public:
  Game(const int amountOfPlayers, const int columns, const int rows);      
  virtual ~Game();
  
  /// Controls the flow of the game, Continues to call getMove() until
  /// isOver() returns something other than 0.
  virtual void start();
};

#endif
