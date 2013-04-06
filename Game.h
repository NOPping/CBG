#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Square.h"
#include "Player.h"


class Game {
    protected:
      int amountOfPlayers;
      int rows;
      int columns;
      Square** grid;
      Player* players;
      int currentPlayer;
      int state;

      void      clearScreen();

      virtual   bool      getMove() = 0;
      virtual   void      drawScreen() = 0;
    
    public:
      virtual void start();
};

#endif