#include "SnakesAndLaddersPlayer.h"

SnakesAndLaddersPlayer::SnakesAndLaddersPlayer(int amountOfTypes,
    vector<string> types,
    int maxPieces) : Player(amountOfTypes, types, maxPieces) {
  this->suspended = false;
}

SnakesAndLaddersPlayer::~SnakesAndLaddersPlayer() {}