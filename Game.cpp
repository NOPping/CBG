#include "Game.h"

void Game::start() {
  //std::cout << "Hello World";
  this->drawScreen();
}

void Game::clearScreen() {
  std::cout << "\033[2J\033[;H";
}