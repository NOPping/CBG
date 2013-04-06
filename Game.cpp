#include "Game.h"

void Game::start() {
  this->drawScreen();
}

void Game::clearScreen() {
  cout << "\033[2J\033[;H";
}