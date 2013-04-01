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

      bool      getMove();
      void      drawScreen();
      bool      executeMove(Square* sourceSquare, Square* destinationSquare);
    
    public:
      virtual void start();
};

#endif