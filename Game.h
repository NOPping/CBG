#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Square.h"
#include "Player.h"


class Game {
    protected:
      // Protected Data
      int       amountOfPlayers;
      int       columns;
      int       currentPlayer;
      int       rows;
      int       state;
      Player*   players;
      Square**  grid;
      
      // Protected function
      void      clearScreen();
      
      // Protected pure virtual functions
      virtual   bool  getMove() = 0;
      virtual   void  drawScreen() = 0;
    
    public:
      // Constructor and deconstructor
      Game();
      virtual ~Game();
      
      // Public Functions
      virtual   void  start();
};

#endif