#ifndef GAME_H
#define GAME_H

class Game {
    private:
      const int amountOfPlayers;
      const int rows;
      const int columns;
      Square *grid;
      Player *players;
      int currentPlayer;
      int state;

      bool      getMove();
      void      drawScreen();
    
    public:
      virtual void start();
};

#endif