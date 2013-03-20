#ifndef PLAYER_H
#define PLAYER_H

class Game {
private:
  int             id;
  PlayerPieces    *pieces;
public:
  Player();
  Player(int id);
};
 
#endif