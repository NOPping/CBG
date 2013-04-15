/// Player for snakes and ladders. Adds a suspended boolean.
/// @author Ian Duffy

#ifndef SNAKESANDLADDERSPLAYER_H
#define SNAKESANDLADDERSPLAYER_H

#include "Player.h"

class SnakesAndLaddersPlayer : public Player {    
  public:
    SnakesAndLaddersPlayer();
    SnakesAndLaddersPlayer(int amountOfTypes, vector<string> types,
                           int maxPieces);
    
    bool suspended;
};

#endif