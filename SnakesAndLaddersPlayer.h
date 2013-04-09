#ifndef SNAKESANDLADDERSPLAYER_H
#define SNAKESANDLADDERSPLAYER_H

#include "Player.h"

class SnakesAndLaddersPlayer : public Player {    
  public:
    SnakesAndLaddersPlayer();
    SnakesAndLaddersPlayer(int amountOfTypes, vector<string> types,
                           int maxPieces);
    ~SnakesAndLaddersPlayer();
    
    bool suspended;
};

#endif