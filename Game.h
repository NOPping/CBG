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
      // Protected Data
      int       currentPlayer;
      Player**  players;
      Square**  grid;
      
      const   int   amountOfPlayers;
      const   int   columns;
      const   int   rows;
      
      // Protected function
      void      clearScreen();
      
      // Protected pure virtual functions
      virtual   bool  getMove() = 0;
      virtual   void  drawScreen() = 0;
      virtual   int   isOver() = 0;

    public:
      // Constructor and deconstructor
      Game(const int amountOfPlayers, const int columns, const int rows);
      virtual ~Game();
      
      // Public Functions
      virtual   void  start();
};

#endif
